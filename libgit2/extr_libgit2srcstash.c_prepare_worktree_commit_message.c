#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  git_buf_clear (TYPE_1__*) ; 
 char const* git_buf_cstr (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_len (TYPE_1__*) ; 
 scalar_t__ git_buf_oom (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_printf (TYPE_1__*,char*,char const*) ; 
 int /*<<< orphan*/  git_buf_put (TYPE_1__*,char const*,char const*) ; 
 int /*<<< orphan*/  git_buf_puts (TYPE_1__*,char*) ; 
 int git_buf_set (TYPE_1__*,char const*,int /*<<< orphan*/ ) ; 
 char* strchr (char const*,char) ; 

__attribute__((used)) static int prepare_worktree_commit_message(
	git_buf* msg,
	const char *user_message)
{
	git_buf buf = GIT_BUF_INIT;
	int error;

	if ((error = git_buf_set(&buf, git_buf_cstr(msg), git_buf_len(msg))) < 0)
		return error;

	git_buf_clear(msg);

	if (!user_message)
		git_buf_printf(msg, "WIP on %s", git_buf_cstr(&buf));
	else {
		const char *colon;

		if ((colon = strchr(git_buf_cstr(&buf), ':')) == NULL)
			goto cleanup;

		git_buf_puts(msg, "On ");
		git_buf_put(msg, git_buf_cstr(&buf), colon - buf.ptr);
		git_buf_printf(msg, ": %s\n", user_message);
	}

	error = (git_buf_oom(msg) || git_buf_oom(&buf)) ? -1 : 0;

cleanup:
	git_buf_dispose(&buf);

	return error;
}