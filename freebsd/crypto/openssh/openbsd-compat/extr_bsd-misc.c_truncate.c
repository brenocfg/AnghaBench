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
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int /*<<< orphan*/  O_WRONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int ftruncate (int,int /*<<< orphan*/ ) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 

int truncate(const char *path, off_t length)
{
	int fd, ret, saverrno;

	fd = open(path, O_WRONLY);
	if (fd < 0)
		return (-1);

	ret = ftruncate(fd, length);
	saverrno = errno;
	close(fd);
	if (ret == -1)
		errno = saverrno;

	return(ret);
}