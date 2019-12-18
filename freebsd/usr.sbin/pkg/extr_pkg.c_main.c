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
 int /*<<< orphan*/  ASSUME_ALWAYS_YES ; 
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  R_OK ; 
 int /*<<< orphan*/  X_OK ; 
 char* _LOCALBASE ; 
 int access (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ bootstrap_pkg (int) ; 
 scalar_t__ bootstrap_pkg_local (char const*,int) ; 
 int /*<<< orphan*/  config_bool (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  config_finish () ; 
 int /*<<< orphan*/  config_init () ; 
 char* confirmation_message ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  execv (char*,char**) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  isatty (int /*<<< orphan*/ ) ; 
 char* non_interactive_message ; 
 scalar_t__ pkg_query_yes_no () ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin ; 
 scalar_t__ strcmp (char*,char*) ; 

int
main(int argc, char *argv[])
{
	char pkgpath[MAXPATHLEN];
	const char *pkgarg;
	int i;
	bool bootstrap_only, force, yes;

	bootstrap_only = false;
	force = false;
	pkgarg = NULL;
	yes = false;

	snprintf(pkgpath, MAXPATHLEN, "%s/sbin/pkg",
	    getenv("LOCALBASE") ? getenv("LOCALBASE") : _LOCALBASE);

	if (argc > 1 && strcmp(argv[1], "bootstrap") == 0) {
		bootstrap_only = true;
		if (argc == 3 && strcmp(argv[2], "-f") == 0)
			force = true;
	}

	if ((bootstrap_only && force) || access(pkgpath, X_OK) == -1) {
		/* 
		 * To allow 'pkg -N' to be used as a reliable test for whether
		 * a system is configured to use pkg, don't bootstrap pkg
		 * when that argument is given as argv[1].
		 */
		if (argv[1] != NULL && strcmp(argv[1], "-N") == 0)
			errx(EXIT_FAILURE, "pkg is not installed");

		config_init();

		if (argc > 1 && strcmp(argv[1], "add") == 0) {
			if (argc > 2 && strcmp(argv[2], "-f") == 0) {
				force = true;
				pkgarg = argv[3];
			} else
				pkgarg = argv[2];
			if (pkgarg == NULL) {
				fprintf(stderr, "Path to pkg.txz required\n");
				exit(EXIT_FAILURE);
			}
			if (access(pkgarg, R_OK) == -1) {
				fprintf(stderr, "No such file: %s\n", pkgarg);
				exit(EXIT_FAILURE);
			}
			if (bootstrap_pkg_local(pkgarg, force) != 0)
				exit(EXIT_FAILURE);
			exit(EXIT_SUCCESS);
		}
		/*
		 * Do not ask for confirmation if either of stdin or stdout is
		 * not tty. Check the environment to see if user has answer
		 * tucked in there already.
		 */
		config_bool(ASSUME_ALWAYS_YES, &yes);
		if (!yes) {
			for (i = 1; i < argc; i++) {
				if (strcmp(argv[i], "-y") == 0 ||
				    strcmp(argv[i], "--yes") == 0) {
					yes = true;
					break;
				}
			}
		}
		if (!yes) {
			if (!isatty(fileno(stdin))) {
				fprintf(stderr, non_interactive_message);
				exit(EXIT_FAILURE);
			}

			printf("%s", confirmation_message);
			if (pkg_query_yes_no() == 0)
				exit(EXIT_FAILURE);
		}
		if (bootstrap_pkg(force) != 0)
			exit(EXIT_FAILURE);
		config_finish();

		if (bootstrap_only)
			exit(EXIT_SUCCESS);
	} else if (bootstrap_only) {
		printf("pkg already bootstrapped at %s\n", pkgpath);
		exit(EXIT_SUCCESS);
	}

	execv(pkgpath, argv);

	/* NOT REACHED */
	return (EXIT_FAILURE);
}