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
typedef  int ssize_t ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  memmove (unsigned char*,unsigned char*,int) ; 
 int write (int,unsigned char*,size_t) ; 

ssize_t
drainbuf(int fd, unsigned char *buf, size_t *bufpos)
{
	ssize_t n;
	ssize_t adjust;

	n = write(fd, buf, *bufpos);
	/* don't treat EAGAIN, EINTR as error */
	if (n == -1 && (errno == EAGAIN || errno == EINTR))
		n = -2;
	if (n <= 0)
		return n;
	/* adjust buffer */
	adjust = *bufpos - n;
	if (adjust > 0)
		memmove(buf, buf + n, adjust);
	*bufpos -= n;
	return n;
}