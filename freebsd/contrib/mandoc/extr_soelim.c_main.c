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
 int C_OPTION ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/ * includes ; 
 int /*<<< orphan*/  optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  sl_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sl_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sl_init () ; 
 int soelim_file (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  soelim_fopen (char*) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char **argv)
{
	int ch, i;
	int ret = 0;
	int flags = 0;

	includes = sl_init();
	if (includes == NULL)
		err(EXIT_FAILURE, "sl_init()");

	while ((ch = getopt(argc, argv, "CrtvI:")) != -1) {
		switch (ch) {
		case 'C':
			flags |= C_OPTION;
			break;
		case 'r':
		case 'v':
		case 't':
			/* stub compatibility with groff's soelim */
			break;
		case 'I':
			sl_add(includes, optarg);
			break;
		default:
			sl_free(includes, 0);
			usage();
		}
	}

	argc -= optind;
	argv += optind;

	if (argc == 0)
		ret = soelim_file(stdin, flags);

	for (i = 0; i < argc; i++)
		ret = soelim_file(soelim_fopen(argv[i]), flags);

	sl_free(includes, 0);

	return (ret);
}