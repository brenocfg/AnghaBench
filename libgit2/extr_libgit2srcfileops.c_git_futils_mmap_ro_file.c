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
typedef  scalar_t__ git_off_t ;
typedef  int /*<<< orphan*/  git_map ;
typedef  scalar_t__ git_file ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_OS ; 
 int /*<<< orphan*/  git__is_sizet (scalar_t__) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ git_futils_filesize (scalar_t__) ; 
 int git_futils_mmap_ro (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ git_futils_open_ro (char const*) ; 
 int /*<<< orphan*/  p_close (scalar_t__) ; 

int git_futils_mmap_ro_file(git_map *out, const char *path)
{
	git_file fd = git_futils_open_ro(path);
	git_off_t len;
	int result;

	if (fd < 0)
		return fd;

	if ((len = git_futils_filesize(fd)) < 0) {
		result = -1;
		goto out;
	}

	if (!git__is_sizet(len)) {
		git_error_set(GIT_ERROR_OS, "file `%s` too large to mmap", path);
		result = -1;
		goto out;
	}

	result = git_futils_mmap_ro(out, fd, 0, (size_t)len);
out:
	p_close(fd);
	return result;
}