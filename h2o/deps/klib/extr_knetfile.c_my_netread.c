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
typedef  int off_t ;

/* Variables and functions */
 int netread (int,void*,int) ; 
 scalar_t__ socket_wait (int,int) ; 

__attribute__((used)) static off_t my_netread(int fd, void *buf, off_t len)
{
	off_t rest = len, curr, l = 0;
	/* recv() and read() may not read the required length of data with
	 * one call. They have to be called repeatedly. */
	while (rest) {
		if (socket_wait(fd, 1) <= 0) break; // socket is not ready for reading
		curr = netread(fd, buf + l, rest);
		/* According to the glibc manual, section 13.2, a zero returned
		 * value indicates end-of-file (EOF), which should mean that
		 * read() will not return zero if EOF has not been met but data
		 * are not immediately available. */
		if (curr == 0) break;
		l += curr; rest -= curr;
	}
	return l;
}