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
struct thread {scalar_t__ td_rtcgen; } ;

/* Variables and functions */
 scalar_t__ rtc_generation ; 

__attribute__((used)) static bool
sleeping_on_old_rtc(struct thread *td)
{

	/*
	 * td_rtcgen is modified by curthread when it is running,
	 * and by other threads in this function.  By finding the thread
	 * on a sleepqueue and holding the lock on the sleepqueue
	 * chain, we guarantee that the thread is not running and that
	 * modifying td_rtcgen is safe.  Setting td_rtcgen to zero informs
	 * the thread that it was woken due to a real-time clock adjustment.
	 * (The declaration of td_rtcgen refers to this comment.)
	 */
	if (td->td_rtcgen != 0 && td->td_rtcgen != rtc_generation) {
		td->td_rtcgen = 0;
		return (true);
	}
	return (false);
}