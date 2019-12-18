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
struct timespec {int tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct mv_rtc_softc {int dummy; } ;
struct clocktime {scalar_t__ year; scalar_t__ mon; scalar_t__ day; scalar_t__ dow; scalar_t__ hour; scalar_t__ min; scalar_t__ sec; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  MV_RTC_DATE_REG ; 
 int /*<<< orphan*/  MV_RTC_TIME_REG ; 
 int TOBCD (scalar_t__) ; 
 scalar_t__ YEAR_BASE ; 
 int /*<<< orphan*/  clock_ts_to_ct (struct timespec*,struct clocktime*) ; 
 struct mv_rtc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mv_rtc_reg_write (struct mv_rtc_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
mv_rtc_settime(device_t dev, struct timespec *ts)
{
	struct clocktime ct;
	struct mv_rtc_softc *sc;
	uint32_t val;

	sc = device_get_softc(dev);

	/* Resolution: 1 sec */
	if (ts->tv_nsec >= 500000000)
		ts->tv_sec++;
	ts->tv_nsec = 0;
	clock_ts_to_ct(ts, &ct);

	val = TOBCD(ct.sec) | (TOBCD(ct.min) << 8) |
	    (TOBCD(ct.hour) << 16) | (TOBCD( ct.dow + 1) << 24);
	mv_rtc_reg_write(sc, MV_RTC_TIME_REG, val);

	val = TOBCD(ct.day) | (TOBCD(ct.mon) << 8) |
	    (TOBCD(ct.year - YEAR_BASE) << 16);
	mv_rtc_reg_write(sc, MV_RTC_DATE_REG, val);

	return (0);
}