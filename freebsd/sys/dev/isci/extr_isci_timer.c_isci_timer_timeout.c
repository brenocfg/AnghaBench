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
struct ISCI_TIMER {scalar_t__ is_started; int /*<<< orphan*/  cookie; int /*<<< orphan*/  (* callback ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  isci_log_message (int,char*,char*,struct ISCI_TIMER*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
isci_timer_timeout(void *arg)
{
	struct ISCI_TIMER *timer = (struct ISCI_TIMER *)arg;

	isci_log_message(3, "TIMER", "timeout %p\n", timer);

	/* callout_stop() will *not* keep the timer from running if it is
	 *  pending.  callout_drain() cannot be called from interrupt context,
	 *  because it may cause thread to sleep which is not allowed in
	 *  interrupt context.  So instead, check the is_started flag to see if
	 *  the timer routine should actually be run or not.
	 */
	if (timer->is_started == TRUE)
		timer->callback(timer->cookie);
}