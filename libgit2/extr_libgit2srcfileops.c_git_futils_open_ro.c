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
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  errno ; 
 int git_path_set_error (int /*<<< orphan*/ ,char const*,char*) ; 
 int p_open (char const*,int /*<<< orphan*/ ) ; 

int git_futils_open_ro(const char *path)
{
	int fd = p_open(path, O_RDONLY);
	if (fd < 0)
		return git_path_set_error(errno, path, "open");
	return fd;
}