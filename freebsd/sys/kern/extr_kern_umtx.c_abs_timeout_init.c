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
struct timespec {int dummy; } ;
struct abs_timeout {int clockid; int is_abs_real; struct timespec end; int /*<<< orphan*/  cur; } ;

/* Variables and functions */
 int CLOCK_REALTIME ; 
 int CLOCK_REALTIME_FAST ; 
 int CLOCK_REALTIME_PRECISE ; 
 int /*<<< orphan*/  abs_timeout_update (struct abs_timeout*) ; 
 int /*<<< orphan*/  timespecadd (int /*<<< orphan*/ *,struct timespec const*,struct timespec*) ; 

__attribute__((used)) static void
abs_timeout_init(struct abs_timeout *timo, int clockid, int absolute,
	const struct timespec *timeout)
{

	timo->clockid = clockid;
	if (!absolute) {
		timo->is_abs_real = false;
		abs_timeout_update(timo);
		timespecadd(&timo->cur, timeout, &timo->end);
	} else {
		timo->end = *timeout;
		timo->is_abs_real = clockid == CLOCK_REALTIME ||
		    clockid == CLOCK_REALTIME_FAST ||
		    clockid == CLOCK_REALTIME_PRECISE;
		/*
		 * If is_abs_real, umtxq_sleep will read the clock
		 * after setting td_rtcgen; otherwise, read it here.
		 */
		if (!timo->is_abs_real) {
			abs_timeout_update(timo);
		}
	}
}