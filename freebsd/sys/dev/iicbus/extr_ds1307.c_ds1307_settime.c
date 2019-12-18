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
typedef  int uint8_t ;
struct timespec {int /*<<< orphan*/  tv_sec; } ;
struct ds1307_softc {int /*<<< orphan*/  sc_dev; scalar_t__ sc_mcp7941x; scalar_t__ sc_use_ampm; } ;
struct bcd_clocktime {int sec; int min; int hour; int day; int dow; int mon; int year; scalar_t__ ispm; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_DBG_WRITE ; 
 size_t DS1307_DATE ; 
 size_t DS1307_HOUR ; 
 int DS1307_HOUR_IS_PM ; 
 int DS1307_HOUR_USE_AMPM ; 
 size_t DS1307_MINS ; 
 size_t DS1307_MONTH ; 
 size_t DS1307_SECS ; 
 size_t DS1307_WEEKDAY ; 
 size_t DS1307_YEAR ; 
 int /*<<< orphan*/  IIC_INTRWAIT ; 
 int MCP7941X_MONTH_LPYR ; 
 int MCP7941X_SECS_ST ; 
 int MCP7941X_WEEKDAY_VBATEN ; 
 int bcd2bin (int) ; 
 int /*<<< orphan*/  clock_dbgprint_bcd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bcd_clocktime*) ; 
 int /*<<< orphan*/  clock_ts_to_bcd (struct timespec*,struct bcd_clocktime*,scalar_t__) ; 
 struct ds1307_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int iicdev_writeto (int /*<<< orphan*/ ,size_t,int*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ utc_offset () ; 

__attribute__((used)) static int
ds1307_settime(device_t dev, struct timespec *ts)
{
	struct bcd_clocktime bct;
	struct ds1307_softc *sc;
	int error, year;
	uint8_t data[7];
	uint8_t pmflags;

	sc = device_get_softc(dev);

	/*
	 * We request a timespec with no resolution-adjustment.  That also
	 * disables utc adjustment, so apply that ourselves.
	 */
	ts->tv_sec -= utc_offset();
	clock_ts_to_bcd(ts, &bct, sc->sc_use_ampm);
	clock_dbgprint_bcd(sc->sc_dev, CLOCK_DBG_WRITE, &bct);

	/* If the chip is in AM/PM mode, adjust hour and set flags as needed. */
	if (sc->sc_use_ampm) {
		pmflags = DS1307_HOUR_USE_AMPM;
		if (bct.ispm)
			pmflags |= DS1307_HOUR_IS_PM;
	} else
		pmflags = 0;

	data[DS1307_SECS]    = bct.sec;
	data[DS1307_MINS]    = bct.min;
	data[DS1307_HOUR]    = bct.hour | pmflags;
	data[DS1307_DATE]    = bct.day;
	data[DS1307_WEEKDAY] = bct.dow;
	data[DS1307_MONTH]   = bct.mon;
	data[DS1307_YEAR]    = bct.year & 0xff;
	if (sc->sc_mcp7941x) {
		data[DS1307_SECS] |= MCP7941X_SECS_ST;
		data[DS1307_WEEKDAY] |= MCP7941X_WEEKDAY_VBATEN;
		year = bcd2bin(bct.year >> 8) * 100 + bcd2bin(bct.year & 0xff);
		if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
			data[DS1307_MONTH] |= MCP7941X_MONTH_LPYR;
	}
	/* Write the time back to RTC. */
	error = iicdev_writeto(sc->sc_dev, DS1307_SECS, data, sizeof(data),
	    IIC_INTRWAIT);
	if (error != 0)
		device_printf(dev, "cannot write to RTC.\n");

	return (error);
}