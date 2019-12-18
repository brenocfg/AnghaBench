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
struct hrtimer {int (* function ) (struct hrtimer*) ;int /*<<< orphan*/  callout; int /*<<< orphan*/  precision; int /*<<< orphan*/  expires; } ;
typedef  enum hrtimer_restart { ____Placeholder_hrtimer_restart } hrtimer_restart ;

/* Variables and functions */
 int HRTIMER_RESTART ; 
 int /*<<< orphan*/  callout_deactivate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_schedule_sbt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nstosbt (int /*<<< orphan*/ ) ; 
 int stub1 (struct hrtimer*) ; 

__attribute__((used)) static void
hrtimer_call_handler(void *arg)
{
	struct hrtimer *hrtimer;
	enum hrtimer_restart ret;

	hrtimer = arg;
	ret = hrtimer->function(hrtimer);

	if (ret == HRTIMER_RESTART) {
		callout_schedule_sbt(&hrtimer->callout,
		    nstosbt(hrtimer->expires), nstosbt(hrtimer->precision), 0);
	} else {
		callout_deactivate(&hrtimer->callout);
	}
}