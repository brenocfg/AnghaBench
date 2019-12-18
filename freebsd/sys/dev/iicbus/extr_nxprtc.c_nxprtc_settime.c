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
struct timespec {scalar_t__ tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct time_regs {int hour; int year; int /*<<< orphan*/  wday; int /*<<< orphan*/  month; int /*<<< orphan*/  day; int /*<<< orphan*/  min; int /*<<< orphan*/  sec; } ;
struct nxprtc_softc {scalar_t__ chiptype; int flags; int /*<<< orphan*/  dev; int /*<<< orphan*/  busdev; int /*<<< orphan*/  tmcaddr; int /*<<< orphan*/  use_ampm; } ;
struct bcd_clocktime {int year; int hour; int /*<<< orphan*/  dow; int /*<<< orphan*/  mon; int /*<<< orphan*/  day; scalar_t__ ispm; int /*<<< orphan*/  min; int /*<<< orphan*/  sec; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_DBG_WRITE ; 
 int /*<<< orphan*/  IIC_WAIT ; 
 int PCF8523_B_HOUR_PM ; 
 int PCF8563_B_MONTH_C ; 
 int PCF85xx_B_CS1_STOP ; 
 int /*<<< orphan*/  PCF85xx_R_CS1 ; 
 int SC_F_CPOL ; 
 int TMR_TICKS_SEC ; 
 scalar_t__ TYPE_PCF8563 ; 
 int /*<<< orphan*/  clock_dbgprint_bcd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bcd_clocktime*) ; 
 int /*<<< orphan*/  clock_ts_to_bcd (struct timespec*,struct bcd_clocktime*,int /*<<< orphan*/ ) ; 
 struct nxprtc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  getnanotime (struct timespec*) ; 
 int /*<<< orphan*/  iicbus_release_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iicbus_request_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcf8523_battery_check (struct nxprtc_softc*) ; 
 int read_reg (struct nxprtc_softc*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ utc_offset () ; 
 int write_reg (struct nxprtc_softc*,int /*<<< orphan*/ ,int) ; 
 int write_timeregs (struct nxprtc_softc*,struct time_regs*) ; 

__attribute__((used)) static int
nxprtc_settime(device_t dev, struct timespec *ts)
{
	struct bcd_clocktime bct;
	struct time_regs tregs;
	struct nxprtc_softc *sc;
	int err;
	uint8_t cflag, cs1;

	sc = device_get_softc(dev);

	/*
	 * We stop the clock, set the time, then restart the clock.  Half a
	 * second after restarting the clock it ticks over to the next second.
	 * So to align the RTC, we schedule this function to be called when
	 * system time is roughly halfway (.495) through the current second.
	 *
	 * Reserve use of the i2c bus and stop the RTC clock.  Note that if
	 * anything goes wrong from this point on, we leave the clock stopped,
	 * because we don't really know what state it's in.
	 */
	if ((err = iicbus_request_bus(sc->busdev, sc->dev, IIC_WAIT)) != 0)
		return (err);
	if ((err = read_reg(sc, PCF85xx_R_CS1, &cs1)) != 0)
		goto errout;
	cs1 |= PCF85xx_B_CS1_STOP;
	if ((err = write_reg(sc, PCF85xx_R_CS1, cs1)) != 0)
		goto errout;

	/* Grab a fresh post-sleep idea of what time it is. */
	getnanotime(ts);
	ts->tv_sec -= utc_offset();
	ts->tv_nsec = 0;
	clock_ts_to_bcd(ts, &bct, sc->use_ampm);
	clock_dbgprint_bcd(sc->dev, CLOCK_DBG_WRITE, &bct);

	/* On 8563 set the century based on the polarity seen when reading. */
	cflag = 0;
	if (sc->chiptype == TYPE_PCF8563) {
		if ((sc->flags & SC_F_CPOL) != 0) {
			if (bct.year >= 0x2000)
				cflag = PCF8563_B_MONTH_C;
		} else if (bct.year < 0x2000)
				cflag = PCF8563_B_MONTH_C;
	}

	tregs.sec   = bct.sec;
	tregs.min   = bct.min;
	tregs.hour  = bct.hour | (bct.ispm ? PCF8523_B_HOUR_PM : 0);
	tregs.day   = bct.day;
	tregs.month = bct.mon;
	tregs.year  = (bct.year & 0xff) | cflag;
	tregs.wday  = bct.dow;

	/*
	 * Set the time, reset the timer count register, then start the clocks.
	 */
	if ((err = write_timeregs(sc, &tregs)) != 0)
		goto errout;

	if ((err = write_reg(sc, sc->tmcaddr, TMR_TICKS_SEC)) != 0)
		return (err);

	cs1 &= ~PCF85xx_B_CS1_STOP;
	err = write_reg(sc, PCF85xx_R_CS1, cs1);

	/*
	 * Check for battery-low.  The actual check is throttled to only occur
	 * once a day, mostly to avoid spamming the user with frequent warnings.
	 */
	pcf8523_battery_check(sc);

errout:

	iicbus_release_bus(sc->busdev, sc->dev);

	if (err != 0)
		device_printf(dev, "cannot write RTC time\n");

	return (err);
}