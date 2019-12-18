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
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 scalar_t__ FILENAME_MAX ; 
 int allpaths ; 
 int /*<<< orphan*/  err (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int) ; 
 char* getenv (char*) ; 
 int getopt (int,char**,char*) ; 
 char* malloc (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (char*,char*,scalar_t__) ; 
 scalar_t__ optind ; 
 int print_matches (char*,char*) ; 
 int silent ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char **argv)
{
	char *p, *path;
	ssize_t pathlen;
	int opt, status;

	status = EXIT_SUCCESS;

	while ((opt = getopt(argc, argv, "as")) != -1) {
		switch (opt) {
		case 'a':
			allpaths = 1;
			break;
		case 's':
			silent = 1;
			break;
		default:
			usage();
			break;
		}
	}

	argv += optind;
	argc -= optind;

	if (argc == 0)
		usage();

	if ((p = getenv("PATH")) == NULL)
		exit(EXIT_FAILURE);
	pathlen = strlen(p) + 1;
	path = malloc(pathlen);
	if (path == NULL)
		err(EXIT_FAILURE, NULL);

	while (argc > 0) {
		memcpy(path, p, pathlen);

		if (strlen(*argv) >= FILENAME_MAX ||
		    print_matches(path, *argv) == -1)
			status = EXIT_FAILURE;

		argv++;
		argc--;
	}

	exit(status);
}