#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct dirent {char* d_name; } ;
struct TYPE_9__ {char* ptr; } ;
struct TYPE_8__ {int flags; int parent_len; TYPE_3__ path; int /*<<< orphan*/  ic; int /*<<< orphan*/  dir; } ;
typedef  TYPE_1__ git_path_diriter ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_OS ; 
 int GIT_ITEROVER ; 
 int GIT_PATH_DIR_INCLUDE_DOT_AND_DOTDOT ; 
 int GIT_PATH_DIR_PRECOMPOSE_UNICODE ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 scalar_t__ errno ; 
 scalar_t__ git_buf_oom (TYPE_3__*) ; 
 int /*<<< orphan*/  git_buf_put (TYPE_3__*,char const*,size_t) ; 
 int /*<<< orphan*/  git_buf_putc (TYPE_3__*,char) ; 
 int /*<<< orphan*/  git_buf_truncate (TYPE_3__*,int) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,char*) ; 
 int git_path_iconv (int /*<<< orphan*/ *,char const**,size_t*) ; 
 scalar_t__ git_path_is_dot_or_dotdot (char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ ) ; 
 size_t strlen (char const*) ; 

int git_path_diriter_next(git_path_diriter *diriter)
{
	struct dirent *de;
	const char *filename;
	size_t filename_len;
	bool skip_dot = !(diriter->flags & GIT_PATH_DIR_INCLUDE_DOT_AND_DOTDOT);
	int error = 0;

	assert(diriter);

	errno = 0;

	do {
		if ((de = readdir(diriter->dir)) == NULL) {
			if (!errno)
				return GIT_ITEROVER;

			git_error_set(GIT_ERROR_OS,
				"could not read directory '%s'", diriter->path.ptr);
			return -1;
		}
	} while (skip_dot && git_path_is_dot_or_dotdot(de->d_name));

	filename = de->d_name;
	filename_len = strlen(filename);

#ifdef GIT_USE_ICONV
	if ((diriter->flags & GIT_PATH_DIR_PRECOMPOSE_UNICODE) != 0 &&
		(error = git_path_iconv(&diriter->ic, &filename, &filename_len)) < 0)
		return error;
#endif

	git_buf_truncate(&diriter->path, diriter->parent_len);

	if (diriter->parent_len > 0 &&
		diriter->path.ptr[diriter->parent_len-1] != '/')
		git_buf_putc(&diriter->path, '/');

	git_buf_put(&diriter->path, filename, filename_len);

	if (git_buf_oom(&diriter->path))
		return -1;

	return error;
}