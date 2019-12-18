#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int ENOMEM ; 
 int ERANGE ; 
 int /*<<< orphan*/  free (char**) ; 
 scalar_t__ isspace (unsigned char) ; 
 char** malloc (int) ; 
 int /*<<< orphan*/  memmove (char*,char*,scalar_t__) ; 
 char** realloc (char**,int) ; 
 scalar_t__ strlen (char*) ; 

int
sl_make_argv(char *line, int *ret_argc, char ***ret_argv)
{
    char *p, *begining;
    int argc, nargv;
    char **argv;
    int quote = 0;

    nargv = 10;
    argv = malloc(nargv * sizeof(*argv));
    if(argv == NULL)
	return ENOMEM;
    argc = 0;

    p = line;

    while(isspace((unsigned char)*p))
	p++;
    begining = p;

    while (1) {
	if (*p == '\0') {
	    ;
	} else if (*p == '"') {
	    quote = !quote;
	    memmove(&p[0], &p[1], strlen(&p[1]) + 1);
	    continue;
	} else if (*p == '\\') {
	    if (p[1] == '\0')
		goto failed;
	    memmove(&p[0], &p[1], strlen(&p[1]) + 1);
	    p += 2;
	    continue;
	} else if (quote || !isspace((unsigned char)*p)) {
	    p++;
	    continue;
	} else
	    *p++ = '\0';
	if (quote)
	    goto failed;
	if(argc == nargv - 1) {
	    char **tmp;
	    nargv *= 2;
	    tmp = realloc (argv, nargv * sizeof(*argv));
	    if (tmp == NULL) {
		free(argv);
		return ENOMEM;
	    }
	    argv = tmp;
	}
	argv[argc++] = begining;
	while(isspace((unsigned char)*p))
	    p++;
	if (*p == '\0')
	    break;
	begining = p;
    }
    argv[argc] = NULL;
    *ret_argc = argc;
    *ret_argv = argv;
    return 0;
failed:
    free(argv);
    return ERANGE;
}