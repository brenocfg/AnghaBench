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
 int O_DIRECTORY ; 
 int O_RDONLY ; 
 scalar_t__ chmod (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ fsync (int) ; 
 int /*<<< orphan*/  group_dir ; 
 int /*<<< orphan*/  group_file ; 
 int open (int /*<<< orphan*/ ,int) ; 
 scalar_t__ rename (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tempname ; 

int
gr_mkdb(void)
{
	int fd;

	if (chmod(tempname, 0644) != 0)
		return (-1);

	if (rename(tempname, group_file) != 0)
		return (-1);

	/*
	 * Make sure new group file is safe on disk. To improve performance we
	 * will call fsync() to the directory where file lies
	 */
	if ((fd = open(group_dir, O_RDONLY|O_DIRECTORY)) == -1)
		return (-1);

	if (fsync(fd) != 0) {
		close(fd);
		return (-1);
	}

	close(fd);
	return(0);
}