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
 int apply_delta (int,char const**) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  svndump_deinit () ; 
 scalar_t__ svndump_init (char const*) ; 
 int /*<<< orphan*/  svndump_read (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  svndump_reset () ; 
 int /*<<< orphan*/  test_svnfe_usage ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ) ; 

int cmd_main(int argc, const char **argv)
{
	if (argc == 2) {
		if (svndump_init(argv[1]))
			return 1;
		svndump_read(NULL, "refs/heads/master", "refs/notes/svn/revs");
		svndump_deinit();
		svndump_reset();
		return 0;
	}

	if (argc >= 2 && !strcmp(argv[1], "-d"))
		return apply_delta(argc, argv);
	usage(test_svnfe_usage);
}