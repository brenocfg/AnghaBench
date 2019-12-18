#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_FETCH_HEAD_FILE ; 
 int /*<<< orphan*/  GIT_REFS_FILE_MODE ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int git_buf_joinpath (TYPE_1__*,char const*,int /*<<< orphan*/ ) ; 
 int git_futils_truncate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int truncate_fetch_head(const char *gitdir)
{
	git_buf path = GIT_BUF_INIT;
	int error;

	if ((error = git_buf_joinpath(&path, gitdir, GIT_FETCH_HEAD_FILE)) < 0)
		return error;

	error = git_futils_truncate(path.ptr, GIT_REFS_FILE_MODE);
	git_buf_dispose(&path);

	return error;
}