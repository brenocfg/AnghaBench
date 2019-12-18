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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 scalar_t__ errno ; 
 scalar_t__ read (int,int /*<<< orphan*/ *,scalar_t__) ; 

ssize_t
stream_read(int fd, void *buf, ssize_t nbytes)
{
	uint8_t *p;
	ssize_t len = 0;
	ssize_t n;

	p = buf;

	while (len < nbytes) {
		n = read(fd, p + len, nbytes - len);
		if (n == 0)
			break;

		if (n < 0) {
			if (errno == EINTR || errno == EAGAIN)
				continue;
			return (n);
		}
		len += n;
	}
	return (len);
}