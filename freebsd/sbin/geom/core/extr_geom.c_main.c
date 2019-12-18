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
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_class (int*,char***) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  getprogname () ; 
 int /*<<< orphan*/  list_one_geom_by_provider (char*) ; 
 int /*<<< orphan*/  optarg ; 
 int /*<<< orphan*/  run_command (int,char**) ; 
 int /*<<< orphan*/  show_tree () ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 char* strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	char *provider_name;
	bool tflag;
	int ch;

	provider_name = NULL;
	tflag = false;

	if (strcmp(getprogname(), "geom") == 0) {
		while ((ch = getopt(argc, argv, "hp:t")) != -1) {
			switch (ch) {
			case 'p':
				provider_name = strdup(optarg);
				if (provider_name == NULL)
					err(1, "strdup");
				break;
			case 't':
				tflag = true;
				break;
			case 'h':
			default:
				usage();
			}
		}

		/*
		 * Don't adjust argc and argv, it would break get_class().
		 */
	}

	if (tflag && provider_name != NULL) {
		errx(EXIT_FAILURE,
		    "At most one of -P and -t may be specified.");
	}

	if (provider_name != NULL) {
		list_one_geom_by_provider(provider_name);
		return (0);
	}

	if (tflag) {
		show_tree();
		return (0);
	}

	get_class(&argc, &argv);
	run_command(argc, argv);
	/* NOTREACHED */

	exit(EXIT_FAILURE);
}