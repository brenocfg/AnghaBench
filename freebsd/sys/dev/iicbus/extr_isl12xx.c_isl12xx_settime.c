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
typedef  int /*<<< orphan*/  tregs ;
struct timespec {scalar_t__ tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct time_regs {int hour; int year; int /*<<< orphan*/  month; int /*<<< orphan*/  day; int /*<<< orphan*/  min; int /*<<< orphan*/  sec; } ;
struct isl12xx_softc {int /*<<< orphan*/  dev; int /*<<< orphan*/  busdev; int /*<<< orphan*/  use_ampm; } ;
struct bcd_clocktime {int hour; int year; int /*<<< orphan*/  mon; int /*<<< orphan*/  day; int /*<<< orphan*/  min; int /*<<< orphan*/  sec; scalar_t__ ispm; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_DBG_WRITE ; 
 int /*<<< orphan*/  IIC_WAIT ; 
 int ISL12XX_24HR_FLAG ; 
 int ISL12XX_PM_FLAG ; 
 int /*<<< orphan*/  ISL12XX_SC_REG ; 
 int /*<<< orphan*/  ISL12XX_SR_REG ; 
 int ISL12XX_SR_W0C_BITS ; 
 int ISL12XX_SR_WRTC ; 
 int /*<<< orphan*/  WAITFLAGS ; 
 int /*<<< orphan*/  clock_dbgprint_bcd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bcd_clocktime*) ; 
 int /*<<< orphan*/  clock_ts_to_bcd (struct timespec*,struct bcd_clocktime*,int /*<<< orphan*/ ) ; 
 struct isl12xx_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iicbus_release_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iicbus_request_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iicdev_writeto (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct time_regs*,int,int /*<<< orphan*/ ) ; 
 int isl12xx_read1 (struct isl12xx_softc*,int /*<<< orphan*/ ,int*) ; 
 int isl12xx_write1 (struct isl12xx_softc*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ utc_offset () ; 

__attribute__((used)) static int
isl12xx_settime(device_t dev, struct timespec *ts)
{
	struct isl12xx_softc *sc = device_get_softc(dev);
	struct bcd_clocktime bct;
	struct time_regs tregs;
	int err;
	uint8_t ampmflags, sreg;

	/*
	 * We request a timespec with no resolution-adjustment.  That also
	 * disables utc adjustment, so apply that ourselves.
	 */
	ts->tv_sec -= utc_offset();
	ts->tv_nsec = 0;
	clock_ts_to_bcd(ts, &bct, sc->use_ampm);
	clock_dbgprint_bcd(sc->dev, CLOCK_DBG_WRITE, &bct); 

	/* If the chip is in AM/PM mode, set flags as needed. */
	if (!sc->use_ampm)
		ampmflags = ISL12XX_24HR_FLAG;
	else
		ampmflags = bct.ispm ? ISL12XX_PM_FLAG : 0;

	tregs.sec   = bct.sec;
	tregs.min   = bct.min;
	tregs.hour  = bct.hour | ampmflags;
	tregs.day   = bct.day;
	tregs.month = bct.mon;
	tregs.year  = bct.year % 100;

	/*
	 * To set the time we have to set the WRTC enable bit in the control
	 * register, then write the time regs, then clear the WRTC bit.  While
	 * doing so we have to be careful to not write a 0 to any sreg bit which
	 * is "write 0 to clear". One of those bits could get set between
	 * reading and writing the register.  All those bits ignore attempts to
	 * write a 1, so just always OR-in all the W0C bits to be sure we never
	 * accidentally clear one.  We hold ownership of the i2c bus for the
	 * whole read-modify-write sequence.
	 */
	if ((err = iicbus_request_bus(sc->busdev, sc->dev, IIC_WAIT)) != 0)
		return (err);
	if ((err = isl12xx_read1(sc, ISL12XX_SR_REG, &sreg)) == 0) {
		sreg |= ISL12XX_SR_WRTC | ISL12XX_SR_W0C_BITS;
		if ((err = isl12xx_write1(sc, ISL12XX_SR_REG, sreg)) == 0) {
			err = iicdev_writeto(sc->dev, ISL12XX_SC_REG, &tregs,
			    sizeof(tregs), WAITFLAGS);
			sreg &= ~ISL12XX_SR_WRTC;
			isl12xx_write1(sc, ISL12XX_SR_REG, sreg);
		}
	}
	iicbus_release_bus(sc->busdev, sc->dev);

	return (err);
}