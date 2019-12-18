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
 int /*<<< orphan*/  PPB_PERIPHERAL_TERMINATION ; 
 int /*<<< orphan*/  PPB_TIMEOUT ; 
 int SELECT ; 
 int SELECTIN ; 
 int STROBE ; 
 int do_peripheral_wait (int /*<<< orphan*/ ,int,int) ; 
 int nBUSY ; 
 int nINIT ; 
 int /*<<< orphan*/  ppb_1284_set_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ppb_1284_set_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_set_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_wctr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

int
ppb_peripheral_terminate(device_t bus, int how)
{
	int error = 0;

#ifdef DEBUG_1284
	printf("t");
#endif

	ppb_1284_set_state(bus, PPB_PERIPHERAL_TERMINATION);

	/* Event 22 - wait up to host response time (1s) */
	if ((error = do_peripheral_wait(bus, SELECT | nBUSY, 0))) {
		ppb_1284_set_error(bus, PPB_TIMEOUT, 22);
		goto error;
	}

	/* Event 24 */
	ppb_wctr(bus, (nINIT | STROBE) & ~(AUTOFEED | SELECTIN));

	/* Event 25 - wait up to host response time (1s) */
	if ((error = do_peripheral_wait(bus, nBUSY, nBUSY))) {
		ppb_1284_set_error(bus, PPB_TIMEOUT, 25);
		goto error;
	}

	/* Event 26 */
	ppb_wctr(bus, (SELECTIN | nINIT | STROBE) & ~(AUTOFEED));
	DELAY(1);
	/* Event 27 */
	ppb_wctr(bus, (SELECTIN | nINIT) & ~(STROBE | AUTOFEED));

	/* Event 28 - wait up to host response time (1s) */
	if ((error = do_peripheral_wait(bus, nBUSY, 0))) {
		ppb_1284_set_error(bus, PPB_TIMEOUT, 28);
		goto error;
	}

error:
	ppb_set_mode(bus, PPB_COMPATIBLE);
	ppb_1284_set_state(bus, PPB_FORWARD_IDLE);

	return (0);
}