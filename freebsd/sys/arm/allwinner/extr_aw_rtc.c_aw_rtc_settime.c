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
typedef  int uint32_t ;
struct timespec {scalar_t__ tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct clocktime {scalar_t__ year; int /*<<< orphan*/  hour; int /*<<< orphan*/  min; int /*<<< orphan*/  sec; int /*<<< orphan*/  mon; int /*<<< orphan*/  day; } ;
struct aw_rtc_softc {TYPE_1__* conf; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  rtc_time; int /*<<< orphan*/  rtc_date; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int EINVAL ; 
 scalar_t__ HALF_OF_SEC_NS ; 
 int /*<<< orphan*/  IS_LEAP_YEAR (scalar_t__) ; 
 int LOSC_BUSY_MASK ; 
 int /*<<< orphan*/  LOSC_CTRL_REG ; 
 int RTC_READ (struct aw_rtc_softc*,int /*<<< orphan*/ ) ; 
 int RTC_TIMEOUT ; 
 int /*<<< orphan*/  RTC_WRITE (struct aw_rtc_softc*,int /*<<< orphan*/ ,int) ; 
 int SET_DAY_VALUE (int /*<<< orphan*/ ) ; 
 int SET_HOUR_VALUE (int /*<<< orphan*/ ) ; 
 int SET_LEAP_VALUE (int /*<<< orphan*/ ) ; 
 int SET_MIN_VALUE (int /*<<< orphan*/ ) ; 
 int SET_MON_VALUE (int /*<<< orphan*/ ) ; 
 int SET_SEC_VALUE (int /*<<< orphan*/ ) ; 
 int SET_YEAR_VALUE (scalar_t__) ; 
 scalar_t__ YEAR_MAX ; 
 scalar_t__ YEAR_MIN ; 
 scalar_t__ YEAR_OFFSET ; 
 int /*<<< orphan*/  clock_ts_to_ct (struct timespec*,struct clocktime*) ; 
 struct aw_rtc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
aw_rtc_settime(device_t dev, struct timespec *ts)
{
	struct aw_rtc_softc *sc  = device_get_softc(dev);
	struct clocktime ct;
	uint32_t clk, rdate, rtime;

	/* RTC resolution is 1 sec */
	if (ts->tv_nsec >= HALF_OF_SEC_NS)
		ts->tv_sec++;
	ts->tv_nsec = 0;

	clock_ts_to_ct(ts, &ct);
	
	if ((ct.year < YEAR_MIN) || (ct.year > YEAR_MAX)) {
		device_printf(dev, "could not set time, year out of range\n");
		return (EINVAL);
	}

	for (clk = 0; RTC_READ(sc, LOSC_CTRL_REG) & LOSC_BUSY_MASK; clk++) {
		if (clk > RTC_TIMEOUT) {
			device_printf(dev, "could not set time, RTC busy\n");
			return (EINVAL);
		}
		DELAY(1);
	}
	/* reset time register to avoid unexpected date increment */
	RTC_WRITE(sc, sc->conf->rtc_time, 0);

	rdate = SET_DAY_VALUE(ct.day) | SET_MON_VALUE(ct.mon) |
		SET_YEAR_VALUE(ct.year - YEAR_OFFSET) | 
		SET_LEAP_VALUE(IS_LEAP_YEAR(ct.year));
			
	rtime = SET_SEC_VALUE(ct.sec) | SET_MIN_VALUE(ct.min) |
		SET_HOUR_VALUE(ct.hour);

	for (clk = 0; RTC_READ(sc, LOSC_CTRL_REG) & LOSC_BUSY_MASK; clk++) {
		if (clk > RTC_TIMEOUT) {
			device_printf(dev, "could not set date, RTC busy\n");
			return (EINVAL);
		}
		DELAY(1);
	}
	RTC_WRITE(sc, sc->conf->rtc_date, rdate);

	for (clk = 0; RTC_READ(sc, LOSC_CTRL_REG) & LOSC_BUSY_MASK; clk++) {
		if (clk > RTC_TIMEOUT) {
			device_printf(dev, "could not set time, RTC busy\n");
			return (EINVAL);
		}
		DELAY(1);
	}
	RTC_WRITE(sc, sc->conf->rtc_time, rtime);

	DELAY(RTC_TIMEOUT);

	return (0);
}