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
struct timespec {int dummy; } ;
struct clocktime {int dow; scalar_t__ nsec; scalar_t__ year; int /*<<< orphan*/  mon; int /*<<< orphan*/  day; int /*<<< orphan*/  hour; int /*<<< orphan*/  min; int /*<<< orphan*/  sec; } ;
struct aw_rtc_softc {TYPE_1__* conf; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  rtc_date; int /*<<< orphan*/  rtc_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  GET_DAY_VALUE (int) ; 
 int /*<<< orphan*/  GET_HOUR_VALUE (int) ; 
 int /*<<< orphan*/  GET_MIN_VALUE (int) ; 
 int /*<<< orphan*/  GET_MON_VALUE (int) ; 
 int /*<<< orphan*/  GET_SEC_VALUE (int) ; 
 scalar_t__ GET_YEAR_VALUE (int) ; 
 int RTC_READ (struct aw_rtc_softc*,int /*<<< orphan*/ ) ; 
 int TIME_MASK ; 
 scalar_t__ YEAR_OFFSET ; 
 int clock_ct_to_ts (struct clocktime*,struct timespec*) ; 
 struct aw_rtc_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aw_rtc_gettime(device_t dev, struct timespec *ts)
{
	struct aw_rtc_softc *sc  = device_get_softc(dev);
	struct clocktime ct;
	uint32_t rdate, rtime;

	rdate = RTC_READ(sc, sc->conf->rtc_date);
	rtime = RTC_READ(sc, sc->conf->rtc_time);
	
	if ((rtime & TIME_MASK) == 0)
		rdate = RTC_READ(sc, sc->conf->rtc_date);

	ct.sec = GET_SEC_VALUE(rtime);
	ct.min = GET_MIN_VALUE(rtime);
	ct.hour = GET_HOUR_VALUE(rtime);
	ct.day = GET_DAY_VALUE(rdate);
	ct.mon = GET_MON_VALUE(rdate);
	ct.year = GET_YEAR_VALUE(rdate) + YEAR_OFFSET;
	ct.dow = -1;
	/* RTC resolution is 1 sec */
	ct.nsec = 0;
	
	return (clock_ct_to_ts(&ct, ts));
}