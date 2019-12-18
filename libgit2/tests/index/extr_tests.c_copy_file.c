#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ git_file ;
struct TYPE_5__ {int /*<<< orphan*/  size; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 scalar_t__ git_futils_creat_withpath (char const*,int,int) ; 
 int /*<<< orphan*/  git_futils_readbuffer (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  p_close (scalar_t__) ; 
 int /*<<< orphan*/  p_write (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void copy_file(const char *src, const char *dst)
{
	git_buf source_buf = GIT_BUF_INIT;
	git_file dst_fd;

	cl_git_pass(git_futils_readbuffer(&source_buf, src));

	dst_fd = git_futils_creat_withpath(dst, 0777, 0666); /* -V536 */
	if (dst_fd < 0)
		goto cleanup;

	cl_git_pass(p_write(dst_fd, source_buf.ptr, source_buf.size));

cleanup:
	git_buf_dispose(&source_buf);
	p_close(dst_fd);
}