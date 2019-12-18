#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  gitdir; } ;
typedef  TYPE_1__ git_repository ;
typedef  int /*<<< orphan*/  git_filebuf ;
struct TYPE_8__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_2__ git_buf ;

/* Variables and functions */
 TYPE_2__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_CHERRYPICK_FILE_MODE ; 
 int /*<<< orphan*/  GIT_CHERRYPICK_HEAD_FILE ; 
 int /*<<< orphan*/  GIT_FILEBUF_CREATE_LEADING_DIRS ; 
 int /*<<< orphan*/  GIT_FILEBUF_INIT ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_2__*) ; 
 int git_buf_joinpath (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_filebuf_cleanup (int /*<<< orphan*/ *) ; 
 int git_filebuf_commit (int /*<<< orphan*/ *) ; 
 int git_filebuf_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int git_filebuf_printf (int /*<<< orphan*/ *,char*,char const*) ; 

__attribute__((used)) static int write_cherrypick_head(
	git_repository *repo,
	const char *commit_oidstr)
{
	git_filebuf file = GIT_FILEBUF_INIT;
	git_buf file_path = GIT_BUF_INIT;
	int error = 0;

	if ((error = git_buf_joinpath(&file_path, repo->gitdir, GIT_CHERRYPICK_HEAD_FILE)) >= 0 &&
		(error = git_filebuf_open(&file, file_path.ptr, GIT_FILEBUF_CREATE_LEADING_DIRS, GIT_CHERRYPICK_FILE_MODE)) >= 0 &&
		(error = git_filebuf_printf(&file, "%s\n", commit_oidstr)) >= 0)
		error = git_filebuf_commit(&file);

	if (error < 0)
		git_filebuf_cleanup(&file);

	git_buf_dispose(&file_path);

	return error;
}