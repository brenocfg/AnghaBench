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
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 scalar_t__ errno ; 
 scalar_t__ read (int,void*,size_t) ; 

__attribute__((used)) static ssize_t read_safe(int fd, void *buf, size_t count)
{
	ssize_t total = 0;
	ssize_t r;

	while(count > 0) {
		r = read(fd, buf, count);
		if (r == 0)
			/* EOF */
			break;
		if (r < 0) {
			if (errno == EINTR)
				/* interrupted by a signal, restart */
				continue;
			/* error */
			total = -1;
			break;
		}

		/* ok */
		total += r;
		count -= r;
		buf += r;
	}

	return total;
}