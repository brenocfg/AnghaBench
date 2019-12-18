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
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 char* fgetln (int /*<<< orphan*/ ,size_t*) ; 
 int getopt (int,char**,char*) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  printf (char*) ; 
 int pw_edit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pw_fini () ; 
 int pw_init (char const*,int /*<<< orphan*/ *) ; 
 int pw_lock () ; 
 scalar_t__ pw_mkdb (int /*<<< orphan*/ *) ; 
 int pw_tmp (int) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  umask (int) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	const char *passwd_dir = NULL;
	int ch, pfd, tfd;
	char *line;
	size_t len;

	while ((ch = getopt(argc, argv, "d:")) != -1)
		switch (ch) {
		case 'd':
			passwd_dir = optarg;
			break;
		case '?':
		default:
			usage();
		}

	argc -= optind;
	argv += optind;

	if (argc != 0)
		usage();

	if (pw_init(passwd_dir, NULL) == -1)
		err(1, "pw_init()");
	if ((pfd = pw_lock()) == -1) {
		pw_fini();
		err(1, "pw_lock()");
	}
	if ((tfd = pw_tmp(pfd)) == -1) {
		pw_fini();
		err(1, "pw_tmp()");
	}
	(void)close(tfd);
	/* Force umask for partial writes made in the edit phase */
	(void)umask(077);

	for (;;) {
		switch (pw_edit(0)) {
		case -1:
			pw_fini();
			err(1, "pw_edit()");
		case 0:
			pw_fini();
			errx(0, "no changes made");
		default:
			break;
		}
		if (pw_mkdb(NULL) == 0) {
			pw_fini();
			errx(0, "password list updated");
		}
		printf("re-edit the password file? ");
		fflush(stdout);
		if ((line = fgetln(stdin, &len)) == NULL) {
			pw_fini();
			err(1, "fgetln()");
		}
		if (len > 0 && (*line == 'N' || *line == 'n'))
			break;
	}
	pw_fini();
	exit(0);
}