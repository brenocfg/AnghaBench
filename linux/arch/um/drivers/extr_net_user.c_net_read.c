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
 scalar_t__ EAGAIN ; 
 int ENOTCONN ; 
 scalar_t__ errno ; 
 int read (int,void*,int) ; 

int net_read(int fd, void *buf, int len)
{
	int n;

	n = read(fd,  buf,  len);

	if ((n < 0) && (errno == EAGAIN))
		return 0;
	else if (n == 0)
		return -ENOTCONN;
	return n;
}