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
struct stash_info {scalar_t__ is_stash_ref; int /*<<< orphan*/  b_commit; } ;
struct option {int dummy; } ;
struct child_process {int git_cmd; int /*<<< orphan*/  args; } ;

/* Variables and functions */
 struct child_process CHILD_PROCESS_INIT ; 
 struct option OPT_END () ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  argv_array_push (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  argv_array_pushl (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *) ; 
 int do_apply_stash (char const*,struct stash_info*,int,int /*<<< orphan*/ ) ; 
 int do_drop_stash (struct stash_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf_ln (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_stash_info (struct stash_info*) ; 
 scalar_t__ get_stash_info (struct stash_info*,int,char const**) ; 
 int /*<<< orphan*/  git_stash_branch_usage ; 
 char const* oid_to_hex (int /*<<< orphan*/ *) ; 
 int parse_options (int,char const**,char const*,struct option*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int run_command (struct child_process*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int branch_stash(int argc, const char **argv, const char *prefix)
{
	int ret;
	const char *branch = NULL;
	struct stash_info info;
	struct child_process cp = CHILD_PROCESS_INIT;
	struct option options[] = {
		OPT_END()
	};

	argc = parse_options(argc, argv, prefix, options,
			     git_stash_branch_usage, 0);

	if (!argc) {
		fprintf_ln(stderr, _("No branch name specified"));
		return -1;
	}

	branch = argv[0];

	if (get_stash_info(&info, argc - 1, argv + 1))
		return -1;

	cp.git_cmd = 1;
	argv_array_pushl(&cp.args, "checkout", "-b", NULL);
	argv_array_push(&cp.args, branch);
	argv_array_push(&cp.args, oid_to_hex(&info.b_commit));
	ret = run_command(&cp);
	if (!ret)
		ret = do_apply_stash(prefix, &info, 1, 0);
	if (!ret && info.is_stash_ref)
		ret = do_drop_stash(&info, 0);

	free_stash_info(&info);

	return ret;
}