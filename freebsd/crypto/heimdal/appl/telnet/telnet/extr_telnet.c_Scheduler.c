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

/* Variables and functions */
 int /*<<< orphan*/  ISend ; 
 int /*<<< orphan*/  SYNCHing ; 
 int /*<<< orphan*/  TELOPT_BINARY ; 
 int /*<<< orphan*/  TELOPT_LINEMODE ; 
 int /*<<< orphan*/  TELOPT_SGA ; 
 scalar_t__ flushline ; 
 int /*<<< orphan*/  kludgelinemode ; 
 scalar_t__ my_want_state_is_do (int /*<<< orphan*/ ) ; 
 scalar_t__ my_want_state_is_will (int /*<<< orphan*/ ) ; 
 scalar_t__ my_want_state_is_wont (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netiring ; 
 int /*<<< orphan*/  netoring ; 
 int process_rings (int,int,int,int,int,int) ; 
 int ring_empty_count (int /*<<< orphan*/ *) ; 
 int ring_full_count (int /*<<< orphan*/ *) ; 
 scalar_t__ scheduler_lockout_tty ; 
 int telrcv () ; 
 int telsnd () ; 
 int /*<<< orphan*/  ttyiring ; 
 int /*<<< orphan*/  ttyoring ; 

int
Scheduler(int block) /* should we block in the select ? */
{
		/* One wants to be a bit careful about setting returnValue
		 * to one, since a one implies we did some useful work,
		 * and therefore probably won't be called to block next
		 * time (TN3270 mode only).
		 */
    int returnValue;
    int netin, netout, netex, ttyin, ttyout;

    /* Decide which rings should be processed */

    netout = ring_full_count(&netoring) &&
	    (flushline ||
		(my_want_state_is_wont(TELOPT_LINEMODE)
#ifdef	KLUDGELINEMODE
			&& (!kludgelinemode || my_want_state_is_do(TELOPT_SGA))
#endif
		) ||
			my_want_state_is_will(TELOPT_BINARY));
    ttyout = ring_full_count(&ttyoring);

    ttyin = ring_empty_count(&ttyiring);

    netin = !ISend && ring_empty_count(&netiring);

    netex = !SYNCHing;

    /* If we have seen a signal recently, reset things */

    if (scheduler_lockout_tty) {
        ttyin = ttyout = 0;
    }

    /* Call to system code to process rings */

    returnValue = process_rings(netin, netout, netex, ttyin, ttyout, !block);

    /* Now, look at the input rings, looking for work to do. */

    if (ring_full_count(&ttyiring)) {
	    returnValue |= telsnd();
    }

    if (ring_full_count(&netiring)) {
	returnValue |= telrcv();
    }
    return returnValue;
}