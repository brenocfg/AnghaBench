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
typedef  int uint32_t ;
struct timespec {int tv_sec; scalar_t__ tv_nsec; } ;
struct mv_rtc_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  MV_RTC_LOCK (struct mv_rtc_softc*) ; 
 int /*<<< orphan*/  MV_RTC_UNLOCK (struct mv_rtc_softc*) ; 
 int /*<<< orphan*/  RTC_TIME ; 
 struct mv_rtc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int mv_rtc_reg_read (struct mv_rtc_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mv_rtc_gettime(device_t dev, struct timespec *ts)
{
	struct mv_rtc_softc *sc;
	uint32_t val, val_check;

	sc = device_get_softc(dev);

	MV_RTC_LOCK(sc);
	/*
	 * According to HW Errata if more than one second between
	 * two time reads is detected, then read once again
	 */
	val = mv_rtc_reg_read(sc, RTC_TIME);
	val_check = mv_rtc_reg_read(sc, RTC_TIME);
	if (val_check - val > 1)
		val_check = mv_rtc_reg_read(sc, RTC_TIME);

	MV_RTC_UNLOCK(sc);

	ts->tv_sec = val_check;
	/* RTC resolution is 1 sec */
	ts->tv_nsec = 0;

	return (0);
}