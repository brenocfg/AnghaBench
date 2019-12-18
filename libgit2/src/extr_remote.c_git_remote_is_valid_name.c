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
typedef  int /*<<< orphan*/  git_refspec ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_printf (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 int /*<<< orphan*/  git_refspec__dispose (int /*<<< orphan*/ *) ; 
 int git_refspec__parse (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int git_remote_is_valid_name(
	const char *remote_name)
{
	git_buf buf = GIT_BUF_INIT;
	git_refspec refspec;
	int error = -1;

	if (!remote_name || *remote_name == '\0')
		return 0;

	git_buf_printf(&buf, "refs/heads/test:refs/remotes/%s/test", remote_name);
	error = git_refspec__parse(&refspec, git_buf_cstr(&buf), true);

	git_buf_dispose(&buf);
	git_refspec__dispose(&refspec);

	git_error_clear();
	return error == 0;
}