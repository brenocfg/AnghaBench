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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int AUTOFEED ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  PPB_COMPATIBLE ; 
 int /*<<< orphan*/  PPB_FORWARD_IDLE ; 
 int /*<<< orphan*/  PPB_TERMINATION ; 
 int /*<<< orphan*/  PPB_TIMEOUT ; 
 int SELECTIN ; 
 int STROBE ; 
 scalar_t__ do_1284_wait (int /*<<< orphan*/ ,int,int) ; 
 int nACK ; 
 int nBUSY ; 
 int nFAULT ; 
 int nINIT ; 
 int /*<<< orphan*/  ppb_1284_set_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ppb_1284_set_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_set_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_wctr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

int
ppb_1284_terminate(device_t bus)
{

#ifdef DEBUG_1284
	printf("T");
#endif

	/* do not reset error here to keep the error that
	 * may occurred before the ppb_1284_terminate() call */
	ppb_1284_set_state(bus, PPB_TERMINATION);

#ifdef PERIPH_1284
	/* request remote host attention */
	ppb_wctr(bus, (nINIT | STROBE | SELECTIN) & ~(AUTOFEED));
	DELAY(1);
#endif /* PERIPH_1284 */

	/* Event 22 - set nSelectin low and nAutoFeed high */
	ppb_wctr(bus, (nINIT | SELECTIN) & ~(STROBE | AUTOFEED));

	/* Event 24 - waiting for peripheral, Xflag ignored */
	if (do_1284_wait(bus, nACK | nBUSY | nFAULT, nFAULT)) {
		ppb_1284_set_error(bus, PPB_TIMEOUT, 24);
		goto error;
	}

	/* Event 25 - set nAutoFd low */
	ppb_wctr(bus, (nINIT | SELECTIN | AUTOFEED) & ~STROBE);

	/* Event 26 - compatible mode status is set */

	/* Event 27 - peripheral set nAck high */
	if (do_1284_wait(bus, nACK, nACK)) {
		ppb_1284_set_error(bus, PPB_TIMEOUT, 27);
	}

	/* Event 28 - end termination, return to idle phase */
	ppb_wctr(bus, (nINIT | SELECTIN) & ~(STROBE | AUTOFEED));

error:
	/* return to compatible mode */
	ppb_set_mode(bus, PPB_COMPATIBLE);
	ppb_1284_set_state(bus, PPB_FORWARD_IDLE);

	return (0);
}