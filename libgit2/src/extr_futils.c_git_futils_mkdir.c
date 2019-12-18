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
typedef  int uint32_t ;
struct stat {int dummy; } ;
struct git_futils_mkdir_options {int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  mode_t ;
struct TYPE_7__ {char const* ptr; scalar_t__ size; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_ERROR_OS ; 
 int GIT_MKDIR_PATH ; 
 int GIT_MKDIR_SKIP_LAST ; 
 int GIT_MKDIR_SKIP_LAST2 ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int git_buf_puts (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,char*) ; 
 int git_futils_mkdir_relative (char const*,char*,int /*<<< orphan*/ ,int,struct git_futils_mkdir_options*) ; 
 int git_path_dirname_r (TYPE_1__*,char*) ; 
 int git_path_root (char const*) ; 
 int mkdir_canonicalize (TYPE_1__*,int) ; 
 int mkdir_validate_dir (char*,struct stat*,int /*<<< orphan*/ ,int,struct git_futils_mkdir_options*) ; 
 int mkdir_validate_mode (char*,struct stat*,int,int /*<<< orphan*/ ,int,struct git_futils_mkdir_options*) ; 
 int p_lstat (char*,struct stat*) ; 

int git_futils_mkdir(
	const char *path,
	mode_t mode,
	uint32_t flags)
{
	git_buf make_path = GIT_BUF_INIT, parent_path = GIT_BUF_INIT;
	const char *relative;
	struct git_futils_mkdir_options opts = { 0 };
	struct stat st;
	size_t depth = 0;
	int len = 0, root_len, error;

	if ((error = git_buf_puts(&make_path, path)) < 0 ||
		(error = mkdir_canonicalize(&make_path, flags)) < 0 ||
		(error = git_buf_puts(&parent_path, make_path.ptr)) < 0 ||
		make_path.size == 0)
		goto done;

	root_len = git_path_root(make_path.ptr);

	/* find the first parent directory that exists.  this will be used
	 * as the base to dirname_relative.
	 */
	for (relative = make_path.ptr; parent_path.size; ) {
		error = p_lstat(parent_path.ptr, &st);

		if (error == 0) {
			break;
		} else if (errno != ENOENT) {
			git_error_set(GIT_ERROR_OS, "failed to stat '%s'", parent_path.ptr);
			error = -1;
			goto done;
		}

		depth++;

		/* examine the parent of the current path */
		if ((len = git_path_dirname_r(&parent_path, parent_path.ptr)) < 0) {
			error = len;
			goto done;
		}

		assert(len);

		/*
		 * We've walked all the given path's parents and it's either relative
		 * (the parent is simply '.') or rooted (the length is less than or
		 * equal to length of the root path).  The path may be less than the
		 * root path length on Windows, where `C:` == `C:/`.
		 */
		if ((len == 1 && parent_path.ptr[0] == '.') ||
		    (len == 1 && parent_path.ptr[0] == '/') ||
		    len <= root_len) {
			relative = make_path.ptr;
			break;
		}

		relative = make_path.ptr + len + 1;

		/* not recursive? just make this directory relative to its parent. */
		if ((flags & GIT_MKDIR_PATH) == 0)
			break;
	}

	/* we found an item at the location we're trying to create,
	 * validate it.
	 */
	if (depth == 0) {
		error = mkdir_validate_dir(make_path.ptr, &st, mode, flags, &opts);

		if (!error)
			error = mkdir_validate_mode(
				make_path.ptr, &st, true, mode, flags, &opts);

		goto done;
	}

	/* we already took `SKIP_LAST` and `SKIP_LAST2` into account when
	 * canonicalizing `make_path`.
	 */
	flags &= ~(GIT_MKDIR_SKIP_LAST2 | GIT_MKDIR_SKIP_LAST);

	error = git_futils_mkdir_relative(relative,
		parent_path.size ? parent_path.ptr : NULL, mode, flags, &opts);

done:
	git_buf_dispose(&make_path);
	git_buf_dispose(&parent_path);
	return error;
}