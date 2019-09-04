#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_MKDIR_PATH ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 TYPE_1__ destpath ; 
 int /*<<< orphan*/  file ; 
 TYPE_1__ filepath ; 
 int /*<<< orphan*/  git_buf_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_cstr (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_joinpath (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_filebuf_commit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_filebuf_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  git_filebuf_printf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_futils_mkdir (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_path_prettify (TYPE_1__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_init (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  git_repository_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  repo ; 

__attribute__((used)) static void init_linked_repo(const char *path, const char *alternate)
{
	git_buf_clear(&destpath);
	git_buf_clear(&filepath);

	cl_git_pass(git_repository_init(&repo, path, 1));
	cl_git_pass(git_path_prettify(&destpath, alternate, NULL));
	cl_git_pass(git_buf_joinpath(&destpath, destpath.ptr, "objects"));
	cl_git_pass(git_buf_joinpath(&filepath, git_repository_path(repo), "objects/info"));
	cl_git_pass(git_futils_mkdir(filepath.ptr, 0755, GIT_MKDIR_PATH));
	cl_git_pass(git_buf_joinpath(&filepath, filepath.ptr , "alternates"));

	cl_git_pass(git_filebuf_open(&file, git_buf_cstr(&filepath), 0, 0666));
	git_filebuf_printf(&file, "%s\n", git_buf_cstr(&destpath));
	cl_git_pass(git_filebuf_commit(&file));

	git_repository_free(repo);
}