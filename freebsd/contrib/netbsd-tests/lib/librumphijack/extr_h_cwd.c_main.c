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
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  dochdir ; 
 int /*<<< orphan*/  dofchdir ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 char* prefix ; 
 int /*<<< orphan*/  prefixlen ; 
 int /*<<< orphan*/  simple () ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  symlinktest () ; 
 int /*<<< orphan*/  thechdir ; 

int
main(int argc, char *argv[])
{

	if (argc != 4)
		errx(1, "usage");

	prefix = argv[1];
	prefixlen = strlen(argv[1]);

	if (strcmp(argv[3], "chdir") == 0)
		thechdir = dochdir;
	else if (strcmp(argv[3], "fchdir") == 0)
		thechdir = dofchdir;
	else
		errx(EXIT_FAILURE, "invalid chdir type");

	if (strcmp(argv[2], "simple") == 0)
		simple();
	if (strcmp(argv[2], "symlink") == 0)
		symlinktest();

	return EXIT_SUCCESS;
}