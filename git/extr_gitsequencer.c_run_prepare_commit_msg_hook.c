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
struct strbuf {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct repository {int /*<<< orphan*/  index_file; } ;
struct argv_array {int /*<<< orphan*/  argv; } ;

/* Variables and functions */
 struct argv_array ARGV_ARRAY_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  argv_array_clear (struct argv_array*) ; 
 int /*<<< orphan*/  argv_array_push (struct argv_array*,char*) ; 
 int /*<<< orphan*/  argv_array_pushf (struct argv_array*,char*,int /*<<< orphan*/ ) ; 
 int error (int /*<<< orphan*/ ) ; 
 char* git_path_commit_editmsg () ; 
 int run_hook_le (int /*<<< orphan*/ ,char*,char const*,char*,char const*,...) ; 
 scalar_t__ write_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int run_prepare_commit_msg_hook(struct repository *r,
				       struct strbuf *msg,
				       const char *commit)
{
	struct argv_array hook_env = ARGV_ARRAY_INIT;
	int ret;
	const char *name;

	name = git_path_commit_editmsg();
	if (write_message(msg->buf, msg->len, name, 0))
		return -1;

	argv_array_pushf(&hook_env, "GIT_INDEX_FILE=%s", r->index_file);
	argv_array_push(&hook_env, "GIT_EDITOR=:");
	if (commit)
		ret = run_hook_le(hook_env.argv, "prepare-commit-msg", name,
				  "commit", commit, NULL);
	else
		ret = run_hook_le(hook_env.argv, "prepare-commit-msg", name,
				  "message", NULL);
	if (ret)
		ret = error(_("'prepare-commit-msg' hook failed"));
	argv_array_clear(&hook_env);

	return ret;
}