#include <stdio.h>
#include <stdlib.h>

#include "mpc.h"

// for Windows
#ifdef _WIN32
#include <string.h>

static char buffer[2048];

// fake readline function
char* readline(char *prompt) {
    fputs(prompt, stdout);
    fgets(buffer, 2048, stdin);
    char *cpy = malloc(strlen(buffer) + 1);
    strcpy(cpy, buffer);
    cpy[strlen(cpy) - 1] = '\0';
    return cpy;
}

// fake add_history function
void add_history(char *unused) {}

#else
#include <editline/readline.h>
#include <editline/history.h>
#endif

int main(int argc, char** argv) {
    // define polish notation jim-lisp language
    // create parsers
    mpc_parser_t *Number = mpc_new("number");
    mpc_parser_t *Operator = mpc_new("operator");
    mpc_parser_t *Expr = mpc_new("expr");
    mpc_parser_t *JimLisp = mpc_new("jim-lisp");

    // define the language
    mpca_lang(MPCA_LANG_DEFAULT,
        "                                                         \
            number      : /-?[0-9]+/ ;                            \
            operator    : '+' | '-' | '*' | '/' ;                 \
            expr        : <number> | '(' <operator> <expr>+ ')' ; \
            jim-lisp    : /^/ <operator> <expr>+ /$/ ;            \
        ",
        Number, Operator, Expr, JimLisp);

    puts("\nJim-Lisp Version 0.0.1");
    puts("Press Ctrl+c to Exit\n");

    while(1) {
        char *input = readline("jim-lisp> ");
        add_history(input);

        mpc_result_t r;

        free(input);
    }

    mpc_cleanup(4, Number, Operator, Expr, JimLisp);

    return 0;
}