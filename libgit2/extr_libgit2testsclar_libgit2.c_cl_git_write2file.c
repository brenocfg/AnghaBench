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

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_close (int) ; 
 int p_open (char const*,int,unsigned int) ; 
 int /*<<< orphan*/  p_write (int,char const*,size_t) ; 
 size_t strlen (char const*) ; 

void cl_git_write2file(
	const char *path, const char *content, size_t content_len,
	int flags, unsigned int mode)
{
	int fd;
	cl_assert(path && content);
	cl_assert((fd = p_open(path, flags, mode)) >= 0);
	if (!content_len)
		content_len = strlen(content);
	cl_must_pass(p_write(fd, content, content_len));
	cl_must_pass(p_close(fd));
}