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
 int EAGAIN ; 
 int EIO ; 
 int errno ; 
 int write (int,char const*,int) ; 

int generic_write(int fd, const char *buf, int n, void *unused)
{
	int err;

	err = write(fd, buf, n);
	if (err > 0)
		return err;
	else if (errno == EAGAIN)
		return 0;
	else if (err == 0)
		return -EIO;
	return -errno;
}