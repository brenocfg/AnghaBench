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
typedef  int /*<<< orphan*/  mode_t ;

/* Variables and functions */
 int O_CREAT ; 
 int O_EXCL ; 
 int O_WRONLY ; 
 int cp_by_fd (int,int,int) ; 
 int /*<<< orphan*/  errno ; 
 int git_futils_open_ro (char const*) ; 
 int git_path_set_error (int /*<<< orphan*/ ,char const*,char*) ; 
 int /*<<< orphan*/  p_close (int) ; 
 int p_open (char const*,int,int /*<<< orphan*/ ) ; 

int git_futils_cp(const char *from, const char *to, mode_t filemode)
{
	int ifd, ofd;

	if ((ifd = git_futils_open_ro(from)) < 0)
		return ifd;

	if ((ofd = p_open(to, O_WRONLY | O_CREAT | O_EXCL, filemode)) < 0) {
		p_close(ifd);
		return git_path_set_error(errno, to, "open for writing");
	}

	return cp_by_fd(ifd, ofd, true);
}