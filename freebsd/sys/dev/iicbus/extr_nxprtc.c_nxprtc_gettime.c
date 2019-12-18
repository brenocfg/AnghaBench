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
typedef  int uint64_t ;
struct timespec {int /*<<< orphan*/  tv_sec; } ;
struct time_regs {int sec; int hour; int min; int day; int month; int year; } ;
struct nxprtc_softc {scalar_t__ chiptype; scalar_t__ use_ampm; int /*<<< orphan*/  dev; int /*<<< orphan*/  flags; int /*<<< orphan*/  busdev; } ;
struct bcd_clocktime {int nsec; int ispm; int sec; int min; int hour; int day; int mon; int year; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_DBG_READ ; 
 int EINVAL ; 
 int /*<<< orphan*/  IIC_WAIT ; 
 int PCF8523_B_HOUR_PM ; 
 int PCF8563_B_MONTH_C ; 
 int PCF85xx_B_CS1_STOP ; 
 int PCF85xx_B_SECOND_OS ; 
 int PCF85xx_M_12HOUR ; 
 int PCF85xx_M_24HOUR ; 
 int PCF85xx_M_DAY ; 
 int PCF85xx_M_MINUTE ; 
 int PCF85xx_M_MONTH ; 
 int PCF85xx_M_SECOND ; 
 int PCF85xx_M_YEAR ; 
 int /*<<< orphan*/  PCF85xx_R_CS1 ; 
 int /*<<< orphan*/  SC_F_CPOL ; 
 int TMR_TICKS_SEC ; 
 scalar_t__ TYPE_PCF8563 ; 
 int clock_bcd_to_ts (struct bcd_clocktime*,struct timespec*,scalar_t__) ; 
 int /*<<< orphan*/  clock_dbgprint_bcd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bcd_clocktime*) ; 
 struct nxprtc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  iicbus_release_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iicbus_request_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int read_reg (struct nxprtc_softc*,int /*<<< orphan*/ ,int*) ; 
 int read_timeregs (struct nxprtc_softc*,struct time_regs*,int*) ; 
 scalar_t__ utc_offset () ; 

__attribute__((used)) static int
nxprtc_gettime(device_t dev, struct timespec *ts)
{
	struct bcd_clocktime bct;
	struct time_regs tregs;
	struct nxprtc_softc *sc;
	int err;
	uint8_t cs1, hourmask, tmrcount;

	sc = device_get_softc(dev);

	/*
	 * Read the time, but before using it, validate that the oscillator-
	 * stopped/power-fail bit is not set, and that the time-increment STOP
	 * bit is not set in the control reg.  The latter can happen if there
	 * was an error when setting the time.
	 */
	if ((err = iicbus_request_bus(sc->busdev, sc->dev, IIC_WAIT)) == 0) {
		if ((err = read_timeregs(sc, &tregs, &tmrcount)) == 0) {
			err = read_reg(sc, PCF85xx_R_CS1, &cs1);
		}
		iicbus_release_bus(sc->busdev, sc->dev);
	}
	if (err != 0)
		return (err);

	if ((tregs.sec & PCF85xx_B_SECOND_OS) || (cs1 & PCF85xx_B_CS1_STOP)) {
		device_printf(dev, "RTC clock not running\n");
		return (EINVAL); /* hardware is good, time is not. */
	}

	if (sc->use_ampm)
		hourmask = PCF85xx_M_12HOUR;
	else
		hourmask = PCF85xx_M_24HOUR;

	bct.nsec = ((uint64_t)tmrcount * 1000000000) / TMR_TICKS_SEC;
	bct.ispm = (tregs.hour & PCF8523_B_HOUR_PM) != 0;
	bct.sec  = tregs.sec   & PCF85xx_M_SECOND;
	bct.min  = tregs.min   & PCF85xx_M_MINUTE;
	bct.hour = tregs.hour  & hourmask;
	bct.day  = tregs.day   & PCF85xx_M_DAY;
	bct.mon  = tregs.month & PCF85xx_M_MONTH;
	bct.year = tregs.year  & PCF85xx_M_YEAR;

	/*
	 * Old PCF8563 datasheets recommended that the C bit be 1 for 19xx and 0
	 * for 20xx; newer datasheets don't recommend that.  We don't care,
	 * but we may co-exist with other OSes sharing the hardware. Determine
	 * existing polarity on a read so that we can preserve it on a write.
	 */
	if (sc->chiptype == TYPE_PCF8563) {
		if (tregs.month & PCF8563_B_MONTH_C) {
			if (bct.year < 0x70)
				sc->flags |= SC_F_CPOL;
		} else if (bct.year >= 0x70)
				sc->flags |= SC_F_CPOL;
	}

	clock_dbgprint_bcd(sc->dev, CLOCK_DBG_READ, &bct); 
	err = clock_bcd_to_ts(&bct, ts, sc->use_ampm);
	ts->tv_sec += utc_offset();

	return (err);
}