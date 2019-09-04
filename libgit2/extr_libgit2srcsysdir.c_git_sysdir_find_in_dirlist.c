#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_sysdir_t ;
struct TYPE_9__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GIT_ERROR_OS ; 
 char const GIT_PATH_LIST_SEPARATOR ; 
 char* git_buf_cstr (TYPE_1__ const*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_joinpath (TYPE_1__*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_buf_len (TYPE_1__ const*) ; 
 int /*<<< orphan*/  git_buf_set (TYPE_1__*,char const*,size_t) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,char const*,char const*) ; 
 scalar_t__ git_path_exists (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_sysdir_get (TYPE_1__ const**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int git_sysdir_find_in_dirlist(
	git_buf *path,
	const char *name,
	git_sysdir_t which,
	const char *label)
{
	size_t len;
	const char *scan, *next = NULL;
	const git_buf *syspath;

	GIT_ERROR_CHECK_ERROR(git_sysdir_get(&syspath, which));
	if (!syspath || !git_buf_len(syspath))
		goto done;

	for (scan = git_buf_cstr(syspath); scan; scan = next) {
		/* find unescaped separator or end of string */
		for (next = scan; *next; ++next) {
			if (*next == GIT_PATH_LIST_SEPARATOR &&
				(next <= scan || next[-1] != '\\'))
				break;
		}

		len = (size_t)(next - scan);
		next = (*next ? next + 1 : NULL);
		if (!len)
			continue;

		GIT_ERROR_CHECK_ERROR(git_buf_set(path, scan, len));
		if (name)
			GIT_ERROR_CHECK_ERROR(git_buf_joinpath(path, path->ptr, name));

		if (git_path_exists(path->ptr))
			return 0;
	}

done:
	git_buf_dispose(path);
	git_error_set(GIT_ERROR_OS, "the %s file '%s' doesn't exist", label, name);
	return GIT_ENOTFOUND;
}