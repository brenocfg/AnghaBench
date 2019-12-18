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

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int error (int /*<<< orphan*/ ) ; 
 char* git_path_commit_editmsg () ; 
 scalar_t__ run_commit_hook (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*,char const*,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ write_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int run_prepare_commit_msg_hook(struct repository *r,
				       struct strbuf *msg,
				       const char *commit)
{
	int ret = 0;
	const char *name, *arg1 = NULL, *arg2 = NULL;

	name = git_path_commit_editmsg();
	if (write_message(msg->buf, msg->len, name, 0))
		return -1;

	if (commit) {
		arg1 = "commit";
		arg2 = commit;
	} else {
		arg1 = "message";
	}
	if (run_commit_hook(0, r->index_file, "prepare-commit-msg", name,
			    arg1, arg2, NULL))
		ret = error(_("'prepare-commit-msg' hook failed"));

	return ret;
}