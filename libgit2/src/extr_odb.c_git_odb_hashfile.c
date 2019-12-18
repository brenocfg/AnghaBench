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
typedef  int /*<<< orphan*/  git_oid ;
typedef  scalar_t__ git_off_t ;
typedef  int /*<<< orphan*/  git_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_OS ; 
 int /*<<< orphan*/  git__is_sizet (scalar_t__) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ git_futils_filesize (int) ; 
 int git_futils_open_ro (char const*) ; 
 int git_odb__hashfd (int /*<<< orphan*/ *,int,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_close (int) ; 

int git_odb_hashfile(git_oid *out, const char *path, git_object_t type)
{
	git_off_t size;
	int result, fd = git_futils_open_ro(path);
	if (fd < 0)
		return fd;

	if ((size = git_futils_filesize(fd)) < 0 || !git__is_sizet(size)) {
		git_error_set(GIT_ERROR_OS, "file size overflow for 32-bit systems");
		p_close(fd);
		return -1;
	}

	result = git_odb__hashfd(out, fd, (size_t)size, type);
	p_close(fd);
	return result;
}