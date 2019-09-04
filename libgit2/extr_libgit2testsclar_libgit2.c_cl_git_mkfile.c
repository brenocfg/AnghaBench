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
 int p_creat (char const*,int) ; 
 int /*<<< orphan*/  p_write (int,char const*,int) ; 
 int strlen (char const*) ; 

void cl_git_mkfile(const char *filename, const char *content)
{
	int fd;

	fd = p_creat(filename, 0666);
	cl_assert(fd != -1);

	if (content) {
		cl_must_pass(p_write(fd, content, strlen(content)));
	} else {
		cl_must_pass(p_write(fd, filename, strlen(filename)));
		cl_must_pass(p_write(fd, "\n", 1));
	}

	cl_must_pass(p_close(fd));
}