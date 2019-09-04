#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ssize_t ;
struct TYPE_16__ {scalar_t__ size; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_COMMONDIR_FILE ; 
 int /*<<< orphan*/  GIT_HEAD_FILE ; 
 int /*<<< orphan*/  GIT_OBJECTS_DIR ; 
 int /*<<< orphan*/  GIT_REFS_DIR ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_joinpath (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_putc (TYPE_1__*,char) ; 
 scalar_t__ git_buf_rfind (TYPE_1__*,char) ; 
 int /*<<< orphan*/  git_buf_rtrim (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_set (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  git_buf_swap (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  git_futils_readbuffer (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int git_path_contains_dir (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int git_path_contains_file (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ git_path_is_relative (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool valid_repository_path(git_buf *repository_path, git_buf *common_path)
{
	/* Check if we have a separate commondir (e.g. we have a
	 * worktree) */
	if (git_path_contains_file(repository_path, GIT_COMMONDIR_FILE)) {
		git_buf common_link  = GIT_BUF_INIT;
		git_buf_joinpath(&common_link, repository_path->ptr, GIT_COMMONDIR_FILE);

		git_futils_readbuffer(&common_link, common_link.ptr);
		git_buf_rtrim(&common_link);

		if (git_path_is_relative(common_link.ptr)) {
			git_buf_joinpath(common_path, repository_path->ptr, common_link.ptr);
		} else {
			git_buf_swap(common_path, &common_link);
		}

		git_buf_dispose(&common_link);
	}
	else {
		git_buf_set(common_path, repository_path->ptr, repository_path->size);
	}

	/* Make sure the commondir path always has a trailing * slash */
	if (git_buf_rfind(common_path, '/') != (ssize_t)common_path->size - 1)
		git_buf_putc(common_path, '/');

	/* Ensure HEAD file exists */
	if (git_path_contains_file(repository_path, GIT_HEAD_FILE) == false)
		return false;

	/* Check files in common dir */
	if (git_path_contains_dir(common_path, GIT_OBJECTS_DIR) == false)
		return false;
	if (git_path_contains_dir(common_path, GIT_REFS_DIR) == false)
		return false;

	return true;
}