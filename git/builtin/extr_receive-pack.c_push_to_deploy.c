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
struct child_process {char const** argv; char const* dir; int no_stdin; int stdout_to_stderr; int git_cmd; int no_stdout; int /*<<< orphan*/  env; } ;
struct argv_array {int /*<<< orphan*/  argv; } ;

/* Variables and functions */
 struct child_process CHILD_PROCESS_INIT ; 
 int /*<<< orphan*/  child_process_init (struct child_process*) ; 
 char* empty_tree_oid_hex () ; 
 char* hash_to_hex (unsigned char*) ; 
 scalar_t__ head_has_history () ; 
 scalar_t__ run_command (struct child_process*) ; 

__attribute__((used)) static const char *push_to_deploy(unsigned char *sha1,
				  struct argv_array *env,
				  const char *work_tree)
{
	const char *update_refresh[] = {
		"update-index", "-q", "--ignore-submodules", "--refresh", NULL
	};
	const char *diff_files[] = {
		"diff-files", "--quiet", "--ignore-submodules", "--", NULL
	};
	const char *diff_index[] = {
		"diff-index", "--quiet", "--cached", "--ignore-submodules",
		NULL, "--", NULL
	};
	const char *read_tree[] = {
		"read-tree", "-u", "-m", NULL, NULL
	};
	struct child_process child = CHILD_PROCESS_INIT;

	child.argv = update_refresh;
	child.env = env->argv;
	child.dir = work_tree;
	child.no_stdin = 1;
	child.stdout_to_stderr = 1;
	child.git_cmd = 1;
	if (run_command(&child))
		return "Up-to-date check failed";

	/* run_command() does not clean up completely; reinitialize */
	child_process_init(&child);
	child.argv = diff_files;
	child.env = env->argv;
	child.dir = work_tree;
	child.no_stdin = 1;
	child.stdout_to_stderr = 1;
	child.git_cmd = 1;
	if (run_command(&child))
		return "Working directory has unstaged changes";

	/* diff-index with either HEAD or an empty tree */
	diff_index[4] = head_has_history() ? "HEAD" : empty_tree_oid_hex();

	child_process_init(&child);
	child.argv = diff_index;
	child.env = env->argv;
	child.no_stdin = 1;
	child.no_stdout = 1;
	child.stdout_to_stderr = 0;
	child.git_cmd = 1;
	if (run_command(&child))
		return "Working directory has staged changes";

	read_tree[3] = hash_to_hex(sha1);
	child_process_init(&child);
	child.argv = read_tree;
	child.env = env->argv;
	child.dir = work_tree;
	child.no_stdin = 1;
	child.no_stdout = 1;
	child.stdout_to_stderr = 0;
	child.git_cmd = 1;
	if (run_command(&child))
		return "Could not update working tree to new HEAD";

	return NULL;
}