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
struct timespec {scalar_t__ tv_nsec; scalar_t__ tv_sec; } ;
struct rtc_instance {int flags; int /*<<< orphan*/  clockdev; int /*<<< orphan*/  resadj; } ;

/* Variables and functions */
 int CLOCKF_SETTIME_NO_ADJ ; 
 int CLOCKF_SETTIME_NO_TS ; 
 int CLOCK_SETTIME (int /*<<< orphan*/ ,struct timespec*) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  getnanotime (struct timespec*) ; 
 int /*<<< orphan*/  timespecadd (struct timespec*,int /*<<< orphan*/ *,struct timespec*) ; 
 scalar_t__ utc_offset () ; 

__attribute__((used)) static void
settime_task_func(void *arg, int pending)
{
	struct timespec ts;
	struct rtc_instance *rtc;
	int error;

	rtc = arg;
	if (!(rtc->flags & CLOCKF_SETTIME_NO_TS)) {
		getnanotime(&ts);
		if (!(rtc->flags & CLOCKF_SETTIME_NO_ADJ)) {
			ts.tv_sec -= utc_offset();
			timespecadd(&ts, &rtc->resadj, &ts);
		}
	} else {
		ts.tv_sec  = 0;
		ts.tv_nsec = 0;
	}
	error = CLOCK_SETTIME(rtc->clockdev, &ts);
	if (error != 0 && bootverbose)
		device_printf(rtc->clockdev, "CLOCK_SETTIME error %d\n", error);
}