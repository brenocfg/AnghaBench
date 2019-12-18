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
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int git_path_isfile (int /*<<< orphan*/ ) ; 
 scalar_t__ retrieve_reflog_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int has_reflog(git_repository *repo, const char *name)
{
	int ret = 0;
	git_buf path = GIT_BUF_INIT;

	if (retrieve_reflog_path(&path, repo, name) < 0)
		goto cleanup;

	ret = git_path_isfile(git_buf_cstr(&path));

cleanup:
	git_buf_dispose(&path);
	return ret;
}