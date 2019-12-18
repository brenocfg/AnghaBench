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
typedef  scalar_t__ time_t ;
struct iodesc {int dummy; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ ETIMEDOUT ; 
 scalar_t__ errno ; 
 scalar_t__ getsecs () ; 
 scalar_t__ readipv4 (struct iodesc*,void**,void**,scalar_t__,int /*<<< orphan*/ ) ; 

ssize_t
readip(struct iodesc *d, void **pkt, void **payload, time_t tleft,
    uint8_t proto)
{
	time_t t;
	ssize_t ret = -1;

	t = getsecs();
	while ((getsecs() - t) < tleft) {
		errno = 0;
		ret = readipv4(d, pkt, payload, tleft, proto);
		if (ret >= 0)
			return (ret);
		/* Bubble up the error if it wasn't successful */
		if (errno != EAGAIN)
			return (-1);
	}
	/* We've exhausted tleft; timeout */
	errno = ETIMEDOUT;
	return (-1);
}