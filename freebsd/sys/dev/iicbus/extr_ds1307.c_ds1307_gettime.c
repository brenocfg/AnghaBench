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
struct timespec {int dummy; } ;
struct ds1307_softc {int sc_use_ampm; int /*<<< orphan*/  sc_dev; scalar_t__ sc_mcp7941x; } ;
struct bcd_clocktime {int ispm; int sec; int min; int hour; int day; int mon; int year; scalar_t__ nsec; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_DBG_READ ; 
 size_t DS1307_DATE ; 
 int DS1307_DATE_MASK ; 
 size_t DS1307_HOUR ; 
 int DS1307_HOUR_IS_PM ; 
 int DS1307_HOUR_MASK_12HR ; 
 int DS1307_HOUR_MASK_24HR ; 
 int DS1307_HOUR_USE_AMPM ; 
 size_t DS1307_MINS ; 
 int DS1307_MINS_MASK ; 
 size_t DS1307_MONTH ; 
 int DS1307_MONTH_MASK ; 
 size_t DS1307_SECS ; 
 int DS1307_SECS_CH ; 
 int DS1307_SECS_MASK ; 
 size_t DS1307_YEAR ; 
 int DS1307_YEAR_MASK ; 
 int EINVAL ; 
 int /*<<< orphan*/  IIC_INTRWAIT ; 
 int clock_bcd_to_ts (struct bcd_clocktime*,struct timespec*,int) ; 
 int /*<<< orphan*/  clock_dbgprint_bcd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bcd_clocktime*) ; 
 struct ds1307_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int iicdev_readfrom (int /*<<< orphan*/ ,size_t,int*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ds1307_gettime(device_t dev, struct timespec *ts)
{
	int error;
	struct bcd_clocktime bct;
	struct ds1307_softc *sc;
	uint8_t data[7], hourmask, st_mask;

	sc = device_get_softc(dev);
	error = iicdev_readfrom(sc->sc_dev, DS1307_SECS, data, sizeof(data),
	    IIC_INTRWAIT);
	if (error != 0) {
		device_printf(dev, "cannot read from RTC.\n");
		return (error);
	}

	/* If the clock halted, we don't have good data. */
	if (sc->sc_mcp7941x)
		st_mask = 0x80;
	else
		st_mask = 0x00;

	if (((data[DS1307_SECS] & DS1307_SECS_CH) ^ st_mask) != 0)
		return (EINVAL);

	/* If chip is in AM/PM mode remember that. */
	if (data[DS1307_HOUR] & DS1307_HOUR_USE_AMPM) {
		sc->sc_use_ampm = true;
		hourmask = DS1307_HOUR_MASK_12HR;
	} else
		hourmask = DS1307_HOUR_MASK_24HR;

	bct.nsec = 0;
	bct.ispm = (data[DS1307_HOUR] & DS1307_HOUR_IS_PM) != 0;
	bct.sec  = data[DS1307_SECS]  & DS1307_SECS_MASK;
	bct.min  = data[DS1307_MINS]  & DS1307_MINS_MASK;
	bct.hour = data[DS1307_HOUR]  & hourmask;
	bct.day  = data[DS1307_DATE]  & DS1307_DATE_MASK;
	bct.mon  = data[DS1307_MONTH] & DS1307_MONTH_MASK;
	bct.year = data[DS1307_YEAR]  & DS1307_YEAR_MASK;

	clock_dbgprint_bcd(sc->sc_dev, CLOCK_DBG_READ, &bct); 
	return (clock_bcd_to_ts(&bct, ts, sc->sc_use_ampm));
}