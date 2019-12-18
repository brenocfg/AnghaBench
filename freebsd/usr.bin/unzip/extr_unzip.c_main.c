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
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  Z1_opt ; 
 int /*<<< orphan*/  add_pattern (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  debug (char*,char*,char) ; 
 int /*<<< orphan*/  errorx (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/ * getenv (char*) ; 
 int getopts (int,char**) ; 
 int /*<<< orphan*/  include ; 
 scalar_t__ isatty (int /*<<< orphan*/ ) ; 
 int n_opt ; 
 int o_opt ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int tty ; 
 int u_opt ; 
 int /*<<< orphan*/  unzip (char const*) ; 
 int unzip_debug ; 
 int /*<<< orphan*/  usage () ; 
 scalar_t__ zipinfo_mode ; 

int
main(int argc, char *argv[])
{
	const char *zipfile;
	int nopts;

	if (isatty(STDOUT_FILENO))
		tty = 1;

	if (getenv("UNZIP_DEBUG") != NULL)
		unzip_debug = 1;
	for (int i = 0; i < argc; ++i)
		debug("%s%c", argv[i], (i < argc - 1) ? ' ' : '\n');

	/*
	 * Info-ZIP's unzip(1) expects certain options to come before the
	 * zipfile name, and others to come after - though it does not
	 * enforce this.  For simplicity, we accept *all* options both
	 * before and after the zipfile name.
	 */
	nopts = getopts(argc, argv);

	/*
	 * When more of the zipinfo mode options are implemented, this
	 * will need to change.
	 */
	if (zipinfo_mode && !Z1_opt) {
		printf("Zipinfo mode needs additional options\n");
		exit(1);
	}

	if (argc <= nopts)
		usage();
	zipfile = argv[nopts++];

	if (strcmp(zipfile, "-") == 0)
		zipfile = NULL; /* STDIN */

	while (nopts < argc && *argv[nopts] != '-')
		add_pattern(&include, argv[nopts++]);

	nopts--; /* fake argv[0] */
	nopts += getopts(argc - nopts, argv + nopts);

	if (n_opt + o_opt + u_opt > 1)
		errorx("-n, -o and -u are contradictory");

	unzip(zipfile);

	exit(0);
}