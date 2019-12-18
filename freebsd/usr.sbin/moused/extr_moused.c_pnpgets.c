#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct timeval {int tv_usec; scalar_t__ tv_sec; } ;
typedef  int /*<<< orphan*/  fd_set ;
struct TYPE_2__ {int /*<<< orphan*/  mfd; } ;

/* Variables and functions */
 int /*<<< orphan*/  FD_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SETSIZE ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int MAX (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIOCMBIS ; 
 int TIOCM_DTR ; 
 int TIOCM_RTS ; 
 int /*<<< orphan*/  bcopy (char*,char*,int) ; 
 int /*<<< orphan*/  debug (char*,int,...) ; 
 int /*<<< orphan*/  ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pnpwakeup1 () ; 
 int /*<<< orphan*/  pnpwakeup2 () ; 
 int read (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_1__ rodent ; 
 scalar_t__ select (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  usleep (int) ; 

__attribute__((used)) static int
pnpgets(char *buf)
{
    struct timeval timeout;
    fd_set fds;
    int begin;
    int i;
    char c;

    if (!pnpwakeup1() && !pnpwakeup2()) {
	/*
	 * According to PnP spec, we should set DTR = 1 and RTS = 0 while
	 * in idle state.  But, `moused' shall set DTR = RTS = 1 and proceed,
	 * assuming there is something at the port even if it didn't
	 * respond to the PnP enumeration procedure.
	 */
	i = TIOCM_DTR | TIOCM_RTS;		/* DTR = 1, RTS = 1 */
	ioctl(rodent.mfd, TIOCMBIS, &i);
	return (0);
    }

    /* collect PnP COM device ID (2.1.7) */
    begin = -1;
    i = 0;
    usleep(240000);	/* the mouse must send `Begin ID' within 200msec */
    while (read(rodent.mfd, &c, 1) == 1) {
	/* we may see "M", or "M3..." before `Begin ID' */
	buf[i++] = c;
	if ((c == 0x08) || (c == 0x28)) {	/* Begin ID */
	    debug("begin-id %02x", c);
	    begin = i - 1;
	    break;
	}
	debug("%c %02x", c, c);
	if (i >= 256)
	    break;
    }
    if (begin < 0) {
	/* we haven't seen `Begin ID' in time... */
	goto connect_idle;
    }

    ++c;			/* make it `End ID' */
    for (;;) {
	FD_ZERO(&fds);
	FD_SET(rodent.mfd, &fds);
	timeout.tv_sec = 0;
	timeout.tv_usec = 240000;
	if (select(FD_SETSIZE, &fds, NULL, NULL, &timeout) <= 0)
	    break;

	read(rodent.mfd, &buf[i], 1);
	if (buf[i++] == c)	/* End ID */
	    break;
	if (i >= 256)
	    break;
    }
    if (begin > 0) {
	i -= begin;
	bcopy(&buf[begin], &buf[0], i);
    }
    /* string may not be human readable... */
    debug("len:%d, '%-*.*s'", i, i, i, buf);

    if (buf[i - 1] == c)
	return (i);		/* a valid PnP string */

    /*
     * According to PnP spec, we should set DTR = 1 and RTS = 0 while
     * in idle state.  But, `moused' shall leave the modem control lines
     * as they are. See above.
     */
connect_idle:

    /* we may still have something in the buffer */
    return (MAX(i, 0));
}