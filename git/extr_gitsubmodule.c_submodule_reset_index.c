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
struct child_process {int git_cmd; int no_stdin; char const* dir; int /*<<< orphan*/  args; int /*<<< orphan*/  env_array; } ;

/* Variables and functions */
 struct child_process CHILD_PROCESS_INIT ; 
 int /*<<< orphan*/  argv_array_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  argv_array_pushf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  argv_array_pushl (int /*<<< orphan*/ *,char*,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  empty_tree_oid_hex () ; 
 int /*<<< orphan*/  get_super_prefix_or_empty () ; 
 int /*<<< orphan*/  prepare_submodule_repo_env (int /*<<< orphan*/ *) ; 
 scalar_t__ run_command (struct child_process*) ; 

__attribute__((used)) static void submodule_reset_index(const char *path)
{
	struct child_process cp = CHILD_PROCESS_INIT;
	prepare_submodule_repo_env(&cp.env_array);

	cp.git_cmd = 1;
	cp.no_stdin = 1;
	cp.dir = path;

	argv_array_pushf(&cp.args, "--super-prefix=%s%s/",
				   get_super_prefix_or_empty(), path);
	argv_array_pushl(&cp.args, "read-tree", "-u", "--reset", NULL);

	argv_array_push(&cp.args, empty_tree_oid_hex());

	if (run_command(&cp))
		die("could not reset submodule index");
}