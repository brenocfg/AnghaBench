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
 int /*<<< orphan*/  EINVAL ; 
 char chip_id ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 char const* nexus ; 
 char const* progname ; 
 int run_cmd (int,char const**) ; 
 int run_cmd_loop () ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ) ; 

int
main(int argc, const char *argv[])
{
	int rc = -1;

	progname = argv[0];

	if (argc == 2) {
		if (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")) {
			usage(stdout);
			exit(0);
		}
	}

	if (argc < 3) {
		usage(stderr);
		exit(EINVAL);
	}

	nexus = argv[1];
	chip_id = nexus[1] - '0';

	/* progname and nexus */
	argc -= 2;
	argv += 2;

	if (argc == 1 && !strcmp(argv[0], "stdio"))
		rc = run_cmd_loop();
	else
		rc = run_cmd(argc, argv);

	return (rc);
}