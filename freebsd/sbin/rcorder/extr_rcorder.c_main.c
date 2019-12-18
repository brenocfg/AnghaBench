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
 int /*<<< orphan*/  DPRINTF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crunch_all_files () ; 
 int debug ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit_code ; 
 int file_count ; 
 char** file_list ; 
 int /*<<< orphan*/  generate_ordering () ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  initialize () ; 
 int /*<<< orphan*/  keep_list ; 
 int /*<<< orphan*/  optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  skip_list ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strnode_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*) ; 

int
main(int argc, char *argv[])
{
	int ch;

	while ((ch = getopt(argc, argv, "dk:s:")) != -1)
		switch (ch) {
		case 'd':
#ifdef DEBUG
			debug = 1;
#else
			warnx("debugging not compiled in, -d ignored");
#endif
			break;
		case 'k':
			strnode_add(&keep_list, optarg, 0);
			break;
		case 's':
			strnode_add(&skip_list, optarg, 0);
			break;
		default:
			/* XXX should crunch it? */
			break;
		}
	argc -= optind;
	argv += optind;

	file_count = argc;
	file_list = argv;

	DPRINTF((stderr, "parse_args\n"));
	initialize();
	DPRINTF((stderr, "initialize\n"));
	crunch_all_files();
	DPRINTF((stderr, "crunch_all_files\n"));
	generate_ordering();
	DPRINTF((stderr, "generate_ordering\n"));

	exit(exit_code);
}