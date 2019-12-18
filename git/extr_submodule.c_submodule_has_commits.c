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
struct strbuf {scalar_t__ len; } ;
struct repository {int dummy; } ;
struct oid_array {int dummy; } ;
struct has_commit_data {int member_1; char const* member_2; int result; struct repository* member_0; } ;
struct child_process {int git_cmd; int no_stdin; char const* dir; int /*<<< orphan*/  env_array; struct has_commit_data args; } ;

/* Variables and functions */
 struct child_process CHILD_PROCESS_INIT ; 
 scalar_t__ GIT_MAX_HEXSZ ; 
 struct strbuf STRBUF_INIT ; 
 scalar_t__ add_submodule_odb (char const*) ; 
 int /*<<< orphan*/  append_oid_to_argv ; 
 int /*<<< orphan*/  argv_array_pushl (struct has_commit_data*,char*,char*,char*,...) ; 
 scalar_t__ capture_command (struct child_process*,struct strbuf*,scalar_t__) ; 
 int /*<<< orphan*/  check_has_commit ; 
 int /*<<< orphan*/  oid_array_for_each_unique (struct oid_array*,int /*<<< orphan*/ ,struct has_commit_data*) ; 
 int /*<<< orphan*/  prepare_submodule_repo_env (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static int submodule_has_commits(struct repository *r,
				 const char *path,
				 struct oid_array *commits)
{
	struct has_commit_data has_commit = { r, 1, path };

	/*
	 * Perform a cheap, but incorrect check for the existence of 'commits'.
	 * This is done by adding the submodule's object store to the in-core
	 * object store, and then querying for each commit's existence.  If we
	 * do not have the commit object anywhere, there is no chance we have
	 * it in the object store of the correct submodule and have it
	 * reachable from a ref, so we can fail early without spawning rev-list
	 * which is expensive.
	 */
	if (add_submodule_odb(path))
		return 0;

	oid_array_for_each_unique(commits, check_has_commit, &has_commit);

	if (has_commit.result) {
		/*
		 * Even if the submodule is checked out and the commit is
		 * present, make sure it exists in the submodule's object store
		 * and that it is reachable from a ref.
		 */
		struct child_process cp = CHILD_PROCESS_INIT;
		struct strbuf out = STRBUF_INIT;

		argv_array_pushl(&cp.args, "rev-list", "-n", "1", NULL);
		oid_array_for_each_unique(commits, append_oid_to_argv, &cp.args);
		argv_array_pushl(&cp.args, "--not", "--all", NULL);

		prepare_submodule_repo_env(&cp.env_array);
		cp.git_cmd = 1;
		cp.no_stdin = 1;
		cp.dir = path;

		if (capture_command(&cp, &out, GIT_MAX_HEXSZ + 1) || out.len)
			has_commit.result = 0;

		strbuf_release(&out);
	}

	return has_commit.result;
}