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
 int errno ; 
 int write (int,void*,int) ; 

int os_write_file(int fd, const void *buf, int len)
{
	int n = write(fd, (void *) buf, len);

	if (n < 0)
		return -errno;
	return n;
}