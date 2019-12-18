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
struct hrtimer {int /*<<< orphan*/  mtx; int /*<<< orphan*/  precision; int /*<<< orphan*/  callout; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  callout_reset_sbt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hrtimer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hrtimer_call_handler ; 
 int /*<<< orphan*/  ktime_to_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nstosbt (int /*<<< orphan*/ ) ; 

void
linux_hrtimer_forward_now(struct hrtimer *hrtimer, ktime_t interval)
{

	mtx_lock(&hrtimer->mtx);
	callout_reset_sbt(&hrtimer->callout, nstosbt(ktime_to_ns(interval)),
	    nstosbt(hrtimer->precision), hrtimer_call_handler, hrtimer, 0);
	mtx_unlock(&hrtimer->mtx);
}