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
typedef  int /*<<< orphan*/  u_char ;
struct ber {int fd; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 scalar_t__ ber_readbuf (struct ber*,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ errno ; 
 scalar_t__ read (int,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static ssize_t
ber_read(struct ber *ber, void *buf, size_t len)
{
	u_char *b = buf;
	ssize_t	r, remain = len;

	/*
	 * XXX calling read here is wrong in many ways. The most obvious one
	 * being that we will block till data arrives.
	 * But for now it is _good enough_ *gulp*
	 */

	while (remain > 0) {
		if (ber->fd == -1)
			r = ber_readbuf(ber, b, remain);
		else
			r = read(ber->fd, b, remain);
		if (r == -1) {
			if (errno == EINTR || errno == EAGAIN)
				continue;
			return -1;
		}
		if (r == 0)
			return (b - (u_char *)buf);
		b += r;
		remain -= r;
	}
	return (b - (u_char *)buf);
}