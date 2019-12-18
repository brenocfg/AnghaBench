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
struct stat {int st_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  STDERR_FILENO ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int S_IWGRP ; 
 int /*<<< orphan*/  chmod (char*,int) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  exit (int) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  puts (char*) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 char* ttyname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	struct stat sb;
	char *tty;
	int ch;

	while ((ch = getopt(argc, argv, "")) != -1)
		switch (ch) {
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	if ((tty = ttyname(STDIN_FILENO)) == NULL &&
	    (tty = ttyname(STDOUT_FILENO)) == NULL &&
	    (tty = ttyname(STDERR_FILENO)) == NULL)
		err(2, "ttyname");
	if (stat(tty, &sb) < 0)
		err(2, "%s", tty);

	if (*argv == NULL) {
		if (sb.st_mode & S_IWGRP) {
			(void)puts("is y");
			exit(0);
		}
		(void)puts("is n");
		exit(1);
	}

	switch (*argv[0]) {
	case 'y':
		if (chmod(tty, sb.st_mode | S_IWGRP) < 0)
			err(2, "%s", tty);
		exit(0);
	case 'n':
		if (chmod(tty, sb.st_mode & ~S_IWGRP) < 0)
			err(2, "%s", tty);
		exit(1);
	}

	usage();
	return(0);
}