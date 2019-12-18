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
 int MAX_ARG_COUNT ; 
 size_t MAX_ARG_LEN ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int /*<<< orphan*/  memset (char**,int /*<<< orphan*/ ,int) ; 
 size_t strlen (char*) ; 
 char* strsep (char**,char*) ; 

int
parse_arg(char *arg, char *buf, char *argv[])
{
	int res = 0;
	size_t argl;
	char *tok;
	char **ap = &buf;
	int i;

	if ((arg == NULL)) {
		/* invalid argument string */
		return -1;
	}

	argl = strlen(arg);
	if (argl == 0) {
		/* no arguments */
		return res;
	}

	if (argl >= MAX_ARG_LEN) {
		/* argument is too long */
		argl = MAX_ARG_LEN-1;
	}

	memset(argv, 0, MAX_ARG_COUNT * sizeof(void *));
	memcpy(buf, arg, argl);
	buf[argl] = '\0';

	for (i = 0; i < MAX_ARG_COUNT; i++) {
		tok = strsep(ap, ":");
		if (tok == NULL) {
			break;
		}
#if 0
		else if (tok[0] == '\0') {
			break;
		}
#endif
		argv[i] = tok;
		res++;
	}

	return res;
}