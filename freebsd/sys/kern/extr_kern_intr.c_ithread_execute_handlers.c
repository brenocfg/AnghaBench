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
struct proc {int dummy; } ;
struct intr_event {int ie_flags; scalar_t__ ie_count; char* ie_name; int /*<<< orphan*/  ie_source; int /*<<< orphan*/  (* ie_post_ithread ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  ie_warncnt; int /*<<< orphan*/  ie_warntm; } ;

/* Variables and functions */
 int IE_SOFT ; 
 int /*<<< orphan*/  THREAD_NO_SLEEPING () ; 
 int /*<<< orphan*/  THREAD_SLEEPING_OK () ; 
 int /*<<< orphan*/  intr_event_execute_handlers (struct proc*,struct intr_event*) ; 
 scalar_t__ intr_storm_threshold ; 
 int /*<<< orphan*/  pause (char*,int) ; 
 scalar_t__ ppsratecheck (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ithread_execute_handlers(struct proc *p, struct intr_event *ie)
{

	/* Interrupt handlers should not sleep. */
	if (!(ie->ie_flags & IE_SOFT))
		THREAD_NO_SLEEPING();
	intr_event_execute_handlers(p, ie);
	if (!(ie->ie_flags & IE_SOFT))
		THREAD_SLEEPING_OK();

	/*
	 * Interrupt storm handling:
	 *
	 * If this interrupt source is currently storming, then throttle
	 * it to only fire the handler once  per clock tick.
	 *
	 * If this interrupt source is not currently storming, but the
	 * number of back to back interrupts exceeds the storm threshold,
	 * then enter storming mode.
	 */
	if (intr_storm_threshold != 0 && ie->ie_count >= intr_storm_threshold &&
	    !(ie->ie_flags & IE_SOFT)) {
		/* Report the message only once every second. */
		if (ppsratecheck(&ie->ie_warntm, &ie->ie_warncnt, 1)) {
			printf(
	"interrupt storm detected on \"%s\"; throttling interrupt source\n",
			    ie->ie_name);
		}
		pause("istorm", 1);
	} else
		ie->ie_count++;

	/*
	 * Now that all the handlers have had a chance to run, reenable
	 * the interrupt source.
	 */
	if (ie->ie_post_ithread != NULL)
		ie->ie_post_ithread(ie->ie_source);
}