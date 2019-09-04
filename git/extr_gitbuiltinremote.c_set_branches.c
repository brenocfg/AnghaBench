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
struct option {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  N_ (char*) ; 
 struct option OPT_BOOL (char,char*,int*,int /*<<< orphan*/ ) ; 
 struct option OPT_END () ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  builtin_remote_setbranches_usage ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ) ; 
 int parse_options (int,char const**,int /*<<< orphan*/ *,struct option*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int set_remote_branches (char const*,char const**,int) ; 
 int /*<<< orphan*/  usage_with_options (int /*<<< orphan*/ ,struct option*) ; 

__attribute__((used)) static int set_branches(int argc, const char **argv)
{
	int add_mode = 0;
	struct option options[] = {
		OPT_BOOL('\0', "add", &add_mode, N_("add branch")),
		OPT_END()
	};

	argc = parse_options(argc, argv, NULL, options,
			     builtin_remote_setbranches_usage, 0);
	if (argc == 0) {
		error(_("no remote specified"));
		usage_with_options(builtin_remote_setbranches_usage, options);
	}
	argv[argc] = NULL;

	return set_remote_branches(argv[0], argv + 1, add_mode);
}