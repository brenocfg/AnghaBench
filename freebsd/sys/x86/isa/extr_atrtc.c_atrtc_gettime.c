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
struct bcd_clocktime {int sec; int min; int hour; int day; int mon; int year; scalar_t__ nsec; scalar_t__ dow; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_DBG_READ ; 
 int EINVAL ; 
 int RTCSA_TUP ; 
 int RTCSD_PWR ; 
 int /*<<< orphan*/  RTC_CENTURY ; 
 int /*<<< orphan*/  RTC_DAY ; 
 int /*<<< orphan*/  RTC_HRS ; 
 int /*<<< orphan*/  RTC_MIN ; 
 int /*<<< orphan*/  RTC_MONTH ; 
 int /*<<< orphan*/  RTC_SEC ; 
 int /*<<< orphan*/  RTC_STATUSA ; 
 int /*<<< orphan*/  RTC_STATUSD ; 
 int /*<<< orphan*/  RTC_YEAR ; 
 int /*<<< orphan*/  atrtc_lock ; 
 int /*<<< orphan*/  atrtc_time_lock ; 
 int clock_bcd_to_ts (struct bcd_clocktime*,struct timespec*,int) ; 
 int /*<<< orphan*/  clock_dbgprint_bcd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bcd_clocktime*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int rtcin (int /*<<< orphan*/ ) ; 
 int rtcin_locked (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
atrtc_gettime(device_t dev, struct timespec *ts)
{
	struct bcd_clocktime bct;

	/* Look if we have a RTC present and the time is valid */
	if (!(rtcin(RTC_STATUSD) & RTCSD_PWR)) {
		device_printf(dev, "WARNING: Battery failure indication\n");
		return (EINVAL);
	}

	/*
	 * wait for time update to complete
	 * If RTCSA_TUP is zero, we have at least 244us before next update.
	 * This is fast enough on most hardware, but a refinement would be
	 * to make sure that no more than 240us pass after we start reading,
	 * and try again if so.
	 */
	mtx_lock(&atrtc_time_lock);
	while (rtcin(RTC_STATUSA) & RTCSA_TUP)
		continue;
	mtx_lock_spin(&atrtc_lock);
	bct.sec  = rtcin_locked(RTC_SEC);
	bct.min  = rtcin_locked(RTC_MIN);
	bct.hour = rtcin_locked(RTC_HRS);
	bct.day  = rtcin_locked(RTC_DAY);
	bct.mon  = rtcin_locked(RTC_MONTH);
	bct.year = rtcin_locked(RTC_YEAR);
#ifdef USE_RTC_CENTURY
	bct.year |= rtcin_locked(RTC_CENTURY) << 8;
#endif
	mtx_unlock_spin(&atrtc_lock);
	mtx_unlock(&atrtc_time_lock);
	/* dow is unused in timespec conversion and we have no nsec info. */
	bct.dow  = 0;
	bct.nsec = 0;
	clock_dbgprint_bcd(dev, CLOCK_DBG_READ, &bct);
	return (clock_bcd_to_ts(&bct, ts, false));
}