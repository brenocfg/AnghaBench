#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  assert (int) ; 
 char* git_buf_detach (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 scalar_t__ git_buf_joinpath (TYPE_1__*,char const*,char const*) ; 
 int /*<<< orphan*/  git_buf_rtrim (TYPE_1__*) ; 
 scalar_t__ git_buf_sets (TYPE_1__*,char const*) ; 
 scalar_t__ git_futils_readbuffer (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ git_path_apply_relative (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_path_is_relative (int /*<<< orphan*/ ) ; 

char *git_worktree__read_link(const char *base, const char *file)
{
	git_buf path = GIT_BUF_INIT, buf = GIT_BUF_INIT;

	assert(base && file);

	if (git_buf_joinpath(&path, base, file) < 0)
		goto err;
	if (git_futils_readbuffer(&buf, path.ptr) < 0)
		goto err;
	git_buf_dispose(&path);

	git_buf_rtrim(&buf);

	if (!git_path_is_relative(buf.ptr))
		return git_buf_detach(&buf);

	if (git_buf_sets(&path, base) < 0)
		goto err;
	if (git_path_apply_relative(&path, buf.ptr) < 0)
		goto err;
	git_buf_dispose(&buf);

	return git_buf_detach(&path);

err:
	git_buf_dispose(&buf);
	git_buf_dispose(&path);

	return NULL;
}