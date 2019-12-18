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
 int /*<<< orphan*/  fatal (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  net ; 
 scalar_t__ realloc (char**,int) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 

__attribute__((used)) static char **
addarg(char **argv, const char *val)
{
	char **cpp;

	if (argv == NULL) {
		/*
		 * 10 entries, a leading length, and a null
		 */
		argv = (char **)malloc(sizeof(*argv) * 12);
		if (argv == NULL)
			fatal(net, "failure allocating argument space");
		*argv++ = (char *)10;
		*argv = (char *)0;
	}
	for (cpp = argv; *cpp; cpp++)
		;
	if (cpp == &argv[(long)argv[-1]]) {
		--argv;
		*argv = (char *)((long)(*argv) + 10);
		argv = (char **)realloc(argv, sizeof(*argv)*((long)(*argv) + 2));
		if (argv == NULL)
			fatal(net, "failure allocating argument space");
		argv++;
		cpp = &argv[(long)argv[-1] - 10];
	}
	if ((*cpp++ = strdup(val)) == NULL)
		fatal(net, "failure allocating argument space");
	*cpp = 0;
	return(argv);
}