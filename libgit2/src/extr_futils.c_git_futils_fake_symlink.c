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
 int GIT_ERROR ; 
 int git_futils_creat_withpath (char const*,int,int) ; 
 int /*<<< orphan*/  p_close (int) ; 
 int p_write (int,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

int git_futils_fake_symlink(const char *old, const char *new)
{
	int retcode = GIT_ERROR;
	int fd = git_futils_creat_withpath(new, 0755, 0644);
	if (fd >= 0) {
		retcode = p_write(fd, old, strlen(old));
		p_close(fd);
	}
	return retcode;
}