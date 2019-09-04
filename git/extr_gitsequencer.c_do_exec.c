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
struct repository {int /*<<< orphan*/  index; } ;
struct argv_array {int /*<<< orphan*/  argv; } ;

/* Variables and functions */
 struct argv_array ARGV_ARRAY_INIT ; 
 char* N_ (char*) ; 
 int /*<<< orphan*/  RUN_USING_SHELL ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  absolute_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  argv_array_clear (struct argv_array*) ; 
 int /*<<< orphan*/  argv_array_pushf (struct argv_array*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ discard_index (int /*<<< orphan*/ ) ; 
 int error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  get_git_dir () ; 
 int /*<<< orphan*/  get_git_work_tree () ; 
 scalar_t__ repo_read_index (struct repository*) ; 
 int require_clean_work_tree (struct repository*,char*,int /*<<< orphan*/ *,int,int) ; 
 int run_command_v_opt_cd_env (char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char const*,...) ; 

__attribute__((used)) static int do_exec(struct repository *r, const char *command_line)
{
	struct argv_array child_env = ARGV_ARRAY_INIT;
	const char *child_argv[] = { NULL, NULL };
	int dirty, status;

	fprintf(stderr, "Executing: %s\n", command_line);
	child_argv[0] = command_line;
	argv_array_pushf(&child_env, "GIT_DIR=%s", absolute_path(get_git_dir()));
	argv_array_pushf(&child_env, "GIT_WORK_TREE=%s",
			 absolute_path(get_git_work_tree()));
	status = run_command_v_opt_cd_env(child_argv, RUN_USING_SHELL, NULL,
					  child_env.argv);

	/* force re-reading of the cache */
	if (discard_index(r->index) < 0 || repo_read_index(r) < 0)
		return error(_("could not read index"));

	dirty = require_clean_work_tree(r, "rebase", NULL, 1, 1);

	if (status) {
		warning(_("execution failed: %s\n%s"
			  "You can fix the problem, and then run\n"
			  "\n"
			  "  git rebase --continue\n"
			  "\n"),
			command_line,
			dirty ? N_("and made changes to the index and/or the "
				"working tree\n") : "");
		if (status == 127)
			/* command not found */
			status = 1;
	} else if (dirty) {
		warning(_("execution succeeded: %s\nbut "
			  "left changes to the index and/or the working tree\n"
			  "Commit or stash your changes, and then run\n"
			  "\n"
			  "  git rebase --continue\n"
			  "\n"), command_line);
		status = 1;
	}

	argv_array_clear(&child_env);

	return status;
}