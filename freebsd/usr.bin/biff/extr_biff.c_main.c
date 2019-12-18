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
 int S_IXGRP ; 
 int S_IXUSR ; 
 int /*<<< orphan*/  chmod (char*,int) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 char* ttyname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	struct stat sb;
	int ch;
	char *name;


	while ((ch = getopt(argc, argv, "")) != -1)
		switch(ch) {
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	if ((name = ttyname(STDIN_FILENO)) == NULL &&
	    (name = ttyname(STDOUT_FILENO)) == NULL &&
	    (name = ttyname(STDERR_FILENO)) == NULL)
		err(2, "unknown tty");

	if (stat(name, &sb))
		err(2, "stat");

	if (*argv == NULL) {
		(void)printf("is %s\n",
		    sb.st_mode & S_IXUSR ? "y" :
		    sb.st_mode & S_IXGRP ? "b" : "n");
		return (sb.st_mode & (S_IXUSR | S_IXGRP) ? 0 : 1);

	}

	switch (argv[0][0]) {
	case 'n':
		if (chmod(name, sb.st_mode & ~(S_IXUSR | S_IXGRP)) < 0)
			err(2, "%s", name);
		break;
	case 'y':
		if (chmod(name, (sb.st_mode & ~(S_IXUSR | S_IXGRP)) | S_IXUSR)
		    < 0)
			err(2, "%s", name);
		break;
	case 'b':
		if (chmod(name, (sb.st_mode & ~(S_IXUSR | S_IXGRP)) | S_IXGRP)
		    < 0)
			err(2, "%s", name);
		break;
	default:
		usage();
	}
	return (sb.st_mode & (S_IXUSR | S_IXGRP) ? 0 : 1);
}