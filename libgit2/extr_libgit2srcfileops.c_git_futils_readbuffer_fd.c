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
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  git_file ;
struct TYPE_6__ {char* ptr; size_t size; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC_ADD (size_t*,size_t,int) ; 
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 int /*<<< orphan*/  GIT_ERROR_OS ; 
 int /*<<< orphan*/  git__is_ssizet (size_t) ; 
 int /*<<< orphan*/  git_buf_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 scalar_t__ git_buf_grow (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 size_t p_read (int /*<<< orphan*/ ,char*,size_t) ; 

int git_futils_readbuffer_fd(git_buf *buf, git_file fd, size_t len)
{
	ssize_t read_size = 0;
	size_t alloc_len;

	git_buf_clear(buf);

	if (!git__is_ssizet(len)) {
		git_error_set(GIT_ERROR_INVALID, "read too large");
		return -1;
	}

	GIT_ERROR_CHECK_ALLOC_ADD(&alloc_len, len, 1);
	if (git_buf_grow(buf, alloc_len) < 0)
		return -1;

	/* p_read loops internally to read len bytes */
	read_size = p_read(fd, buf->ptr, len);

	if (read_size != (ssize_t)len) {
		git_error_set(GIT_ERROR_OS, "failed to read descriptor");
		git_buf_dispose(buf);
		return -1;
	}

	buf->ptr[read_size] = '\0';
	buf->size = read_size;

	return 0;
}