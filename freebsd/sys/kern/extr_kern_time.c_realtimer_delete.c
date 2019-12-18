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
struct TYPE_2__ {int /*<<< orphan*/  it_interval; int /*<<< orphan*/  it_value; } ;
struct itimer {int /*<<< orphan*/  it_callout; TYPE_1__ it_time; int /*<<< orphan*/  it_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  ITIMER_LOCK (struct itimer*) ; 
 int /*<<< orphan*/  ITIMER_UNLOCK (struct itimer*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timespecclear (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
realtimer_delete(struct itimer *it)
{
	mtx_assert(&it->it_mtx, MA_OWNED);
	
	/*
	 * clear timer's value and interval to tell realtimer_expire
	 * to not rearm the timer.
	 */
	timespecclear(&it->it_time.it_value);
	timespecclear(&it->it_time.it_interval);
	ITIMER_UNLOCK(it);
	callout_drain(&it->it_callout);
	ITIMER_LOCK(it);
	return (0);
}