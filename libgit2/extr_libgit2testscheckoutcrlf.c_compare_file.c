#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct compare_data {int /*<<< orphan*/  attrs; int /*<<< orphan*/  autocrlf; int /*<<< orphan*/  dirname; } ;
struct TYPE_8__ {scalar_t__ size; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clar__fail (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git__free (char*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_joinpath (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_buf_printf (TYPE_1__*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ git_futils_readbuffer (TYPE_1__*,int /*<<< orphan*/ ) ; 
 char* git_path_basename (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_path_isfile (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int strcmp (char*,char*) ; 
 int /*<<< orphan*/  systype ; 

__attribute__((used)) static int compare_file(void *payload, git_buf *actual_path)
{
	git_buf expected_path = GIT_BUF_INIT;
	git_buf actual_contents = GIT_BUF_INIT;
	git_buf expected_contents = GIT_BUF_INIT;
	struct compare_data *cd = payload;
	bool failed = true;
	int cmp_git, cmp_gitattributes;
	char *basename;

	basename = git_path_basename(actual_path->ptr);
	cmp_git = strcmp(basename, ".git");
	cmp_gitattributes = strcmp(basename, ".gitattributes");

	if (cmp_git == 0 || cmp_gitattributes == 0) {
		failed = false;
		goto done;
	}

	cl_git_pass(git_buf_joinpath(&expected_path, cd->dirname, basename));

	if (!git_path_isfile(expected_path.ptr) ||
		!git_path_isfile(actual_path->ptr))
		goto done;

	if (git_futils_readbuffer(&actual_contents, actual_path->ptr) < 0 ||
		git_futils_readbuffer(&expected_contents, expected_path.ptr) < 0)
		goto done;

	if (actual_contents.size != expected_contents.size)
		goto done;

	if (memcmp(actual_contents.ptr, expected_contents.ptr, expected_contents.size) != 0)
		goto done;

	failed = false;

done:
	if (failed) {
		git_buf details = GIT_BUF_INIT;
		git_buf_printf(&details, "filename=%s, system=%s, autocrlf=%s, attrs={%s}",
			git_path_basename(actual_path->ptr), systype, cd->autocrlf, cd->attrs);
		clar__fail(__FILE__, __LINE__,
			"checked out contents did not match expected", details.ptr, 0);
		git_buf_dispose(&details);
	}

	git__free(basename);
	git_buf_dispose(&expected_contents);
	git_buf_dispose(&actual_contents);
	git_buf_dispose(&expected_path);

	return 0;
}