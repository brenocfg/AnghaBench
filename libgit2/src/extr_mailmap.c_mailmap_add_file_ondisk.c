#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_mailmap ;
struct TYPE_6__ {int /*<<< orphan*/  size; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int git_futils_readbuffer (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int git_path_join_unrooted (TYPE_1__*,char const*,char const*,int /*<<< orphan*/ *) ; 
 char* git_repository_workdir (int /*<<< orphan*/ *) ; 
 int mailmap_add_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mailmap_add_file_ondisk(
	git_mailmap *mm, const char *path, git_repository *repo)
{
	const char *base = repo ? git_repository_workdir(repo) : NULL;
	git_buf fullpath = GIT_BUF_INIT;
	git_buf content = GIT_BUF_INIT;
	int error;

	error = git_path_join_unrooted(&fullpath, path, base, NULL);
	if (error < 0)
		goto cleanup;

	error = git_futils_readbuffer(&content, fullpath.ptr);
	if (error < 0)
		goto cleanup;

	error = mailmap_add_buffer(mm, content.ptr, content.size);
	if (error < 0)
		goto cleanup;

cleanup:
	git_buf_dispose(&fullpath);
	git_buf_dispose(&content);
	return error;
}