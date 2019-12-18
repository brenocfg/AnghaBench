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
 int /*<<< orphan*/  addarg (char*) ; 
 int /*<<< orphan*/  addlib (char*) ; 
 int /*<<< orphan*/ * args ; 
 scalar_t__ cargs ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  execv (char*,int /*<<< orphan*/ *) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ nargs ; 
 int optind ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	int ch, i;

	args = NULL;
	cargs = nargs = 0;

	while ((ch = getopt(argc, argv, "cD:EgI:L:o:O:sU:l:")) != -1) {
		if (ch == 'l') {
			/* Gone too far. Back up and get out. */
			if (argv[optind - 1][0] == '-')
				optind -= 1;
			else
				optind -= 2;
			break;
		} else if (ch == '?')
			usage();
	}

	addarg("/usr/bin/cc");
	addarg("-std=iso9899:1999");
	addarg("-pedantic");
	for (i = 1; i < optind; i++)
		addarg(argv[i]);
	while (i < argc) {
		if (strncmp(argv[i], "-l", 2) == 0) {
			if (argv[i][2] != '\0')
				addlib(argv[i++] + 2);
			else {
				if (argv[++i] == NULL)
					usage();
				addlib(argv[i++]);
			}
		} else
			addarg(argv[i++]);
	}
	execv("/usr/bin/cc", args);
	err(1, "/usr/bin/cc");
}