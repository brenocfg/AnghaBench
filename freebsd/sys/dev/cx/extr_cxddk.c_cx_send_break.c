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
typedef  int /*<<< orphan*/  cx_chan_t ;

/* Variables and functions */
 int /*<<< orphan*/  cx_send (int /*<<< orphan*/ *,unsigned char*,int,int /*<<< orphan*/ ) ; 

void cx_send_break (cx_chan_t *c, int msec)
{
	static unsigned char buf [128];
	unsigned char *p;

	p = buf;
	*p++ = 0;		/* extended transmit command */
	*p++ = 0x81;		/* send break */

	if (msec > 10000)	/* max 10 seconds */
		msec = 10000;
	if (msec < 10)		/* min 10 msec */
		msec = 10;
	while (msec > 0) {
		int ms = 250;	/* 250 msec */
		if (ms > msec)
			ms = msec;
		msec -= ms;
		*p++ = 0;	/* extended transmit command */
		*p++ = 0x82;	/* insert delay */
		*p++ = ms;
	}
	*p++ = 0;		/* extended transmit command */
	*p++ = 0x83;		/* stop break */

	cx_send (c, buf, p-buf, 0);
}