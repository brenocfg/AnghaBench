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
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  git__prefixcmp (char const*,char const*) ; 
 int git_blob__create_from_paths (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ ,int) ; 
 char* git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int git_path_prettify (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 char* git_repository_workdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

int git_blob_create_from_disk(
	git_oid *id, git_repository *repo, const char *path)
{
	int error;
	git_buf full_path = GIT_BUF_INIT;
	const char *workdir, *hintpath;

	if ((error = git_path_prettify(&full_path, path, NULL)) < 0) {
		git_buf_dispose(&full_path);
		return error;
	}

	hintpath = git_buf_cstr(&full_path);
	workdir  = git_repository_workdir(repo);

	if (workdir && !git__prefixcmp(hintpath, workdir))
		hintpath += strlen(workdir);

	error = git_blob__create_from_paths(
		id, NULL, repo, git_buf_cstr(&full_path), hintpath, 0, true);

	git_buf_dispose(&full_path);
	return error;
}