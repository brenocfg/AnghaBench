#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int n; TYPE_2__* array; } ;
typedef  TYPE_1__ cmdp_token_ptr ;
struct TYPE_6__ {char* name; int /*<<< orphan*/ * identifier; } ;
typedef  TYPE_2__ cmdp_token ;

/* Variables and functions */
 scalar_t__ ERANGE ; 
 size_t INITIAL ; 
 long LONG_MAX ; 
 long LONG_MIN ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (char*) ; 
 char* next_state (TYPE_2__ const*) ; 
 int /*<<< orphan*/  push_long (int /*<<< orphan*/ *,long) ; 
 int /*<<< orphan*/  push_string (int /*<<< orphan*/ *,char*) ; 
 char* scalloc (int,int) ; 
 size_t state ; 
 int statelist_idx ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int strlen (char const*) ; 
 scalar_t__ strncasecmp (char const*,char*,int) ; 
 long strtol (char const*,char**,int) ; 
 TYPE_1__* tokens ; 

__attribute__((used)) static char *rewrite_binding(const char *input) {
    state = INITIAL;
    statelist_idx = 1;

    const char *walk = input;
    const size_t len = strlen(input);
    int c;
    const cmdp_token *token;
    char *result = NULL;

    /* The "<=" operator is intentional: We also handle the terminating 0-byte
     * explicitly by looking for an 'end' token. */
    while ((size_t)(walk - input) <= len) {
        /* Skip whitespace before every token, newlines are relevant since they
         * separate configuration directives. */
        while ((*walk == ' ' || *walk == '\t') && *walk != '\0')
            walk++;

        //printf("remaining input: %s\n", walk);

        cmdp_token_ptr *ptr = &(tokens[state]);
        for (c = 0; c < ptr->n; c++) {
            token = &(ptr->array[c]);

            /* A literal. */
            if (token->name[0] == '\'') {
                if (strncasecmp(walk, token->name + 1, strlen(token->name) - 1) == 0) {
                    if (token->identifier != NULL)
                        push_string(token->identifier, token->name + 1);
                    walk += strlen(token->name) - 1;
                    if ((result = next_state(token)) != NULL)
                        return result;
                    break;
                }
                continue;
            }

            if (strcmp(token->name, "number") == 0) {
                /* Handle numbers. We only accept decimal numbers for now. */
                char *end = NULL;
                errno = 0;
                long int num = strtol(walk, &end, 10);
                if ((errno == ERANGE && (num == LONG_MIN || num == LONG_MAX)) ||
                    (errno != 0 && num == 0))
                    continue;

                /* No valid numbers found */
                if (end == walk)
                    continue;

                if (token->identifier != NULL)
                    push_long(token->identifier, num);

                /* Set walk to the first non-number character */
                walk = end;
                if ((result = next_state(token)) != NULL)
                    return result;
                break;
            }

            if (strcmp(token->name, "string") == 0 ||
                strcmp(token->name, "word") == 0) {
                const char *beginning = walk;
                /* Handle quoted strings (or words). */
                if (*walk == '"') {
                    beginning++;
                    walk++;
                    while (*walk != '\0' && (*walk != '"' || *(walk - 1) == '\\'))
                        walk++;
                } else {
                    if (token->name[0] == 's') {
                        while (*walk != '\0' && *walk != '\r' && *walk != '\n')
                            walk++;
                    } else {
                        /* For a word, the delimiters are white space (' ' or
                         * '\t'), closing square bracket (]), comma (,) and
                         * semicolon (;). */
                        while (*walk != ' ' && *walk != '\t' &&
                               *walk != ']' && *walk != ',' &&
                               *walk != ';' && *walk != '\r' &&
                               *walk != '\n' && *walk != '\0')
                            walk++;
                    }
                }
                if (walk != beginning) {
                    char *str = scalloc(walk - beginning + 1, 1);
                    /* We copy manually to handle escaping of characters. */
                    int inpos, outpos;
                    for (inpos = 0, outpos = 0;
                         inpos < (walk - beginning);
                         inpos++, outpos++) {
                        /* We only handle escaped double quotes to not break
                         * backwards compatibility with people using \w in
                         * regular expressions etc. */
                        if (beginning[inpos] == '\\' && beginning[inpos + 1] == '"')
                            inpos++;
                        str[outpos] = beginning[inpos];
                    }
                    if (token->identifier)
                        push_string(token->identifier, str);
                    free(str);
                    /* If we are at the end of a quoted string, skip the ending
                     * double quote. */
                    if (*walk == '"')
                        walk++;
                    if ((result = next_state(token)) != NULL)
                        return result;
                    break;
                }
            }

            if (strcmp(token->name, "end") == 0) {
                //printf("checking for end: *%s*\n", walk);
                if (*walk == '\0' || *walk == '\n' || *walk == '\r') {
                    if ((result = next_state(token)) != NULL)
                        return result;
                    /* To make sure we start with an appropriate matching
                     * datastructure for commands which do *not* specify any
                     * criteria, we re-initialize the criteria system after
                     * every command. */
                    // TODO: make this testable
                    walk++;
                    break;
                }
            }
        }
    }

    return NULL;
}