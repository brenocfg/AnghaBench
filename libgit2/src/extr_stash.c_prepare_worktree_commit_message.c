#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 char const* git_buf_cstr (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 scalar_t__ git_buf_oom (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_printf (TYPE_1__*,char*,char const*) ; 
 int /*<<< orphan*/  git_buf_put (TYPE_1__*,char const*,char const*) ; 
 int /*<<< orphan*/  git_buf_puts (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  git_buf_swap (TYPE_1__*,TYPE_1__*) ; 
 char* strchr (char const*,char) ; 

__attribute__((used)) static int prepare_worktree_commit_message(git_buf *out, const char *user_message)
{
	git_buf buf = GIT_BUF_INIT;
	int error = 0;

	if (!user_message) {
		git_buf_printf(&buf, "WIP on %s", git_buf_cstr(out));
	} else {
		const char *colon;

		if ((colon = strchr(git_buf_cstr(out), ':')) == NULL)
			goto cleanup;

		git_buf_puts(&buf, "On ");
		git_buf_put(&buf, git_buf_cstr(out), colon - out->ptr);
		git_buf_printf(&buf, ": %s\n", user_message);
	}

	if (git_buf_oom(&buf)) {
		error = -1;
		goto cleanup;
	}

	git_buf_swap(out, &buf);

cleanup:
	git_buf_dispose(&buf);
	return error;
}