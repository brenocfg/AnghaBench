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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  tregs ;
struct timespec {int tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct time_regs {int day; int /*<<< orphan*/  month; int /*<<< orphan*/  hour; int /*<<< orphan*/  min; int /*<<< orphan*/  sec; int /*<<< orphan*/  msec; } ;
struct rtc8583_softc {int /*<<< orphan*/  dev; int /*<<< orphan*/  busdev; } ;
struct bcd_clocktime {int day; int year; int /*<<< orphan*/  mon; int /*<<< orphan*/  hour; int /*<<< orphan*/  min; int /*<<< orphan*/  sec; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_DBG_WRITE ; 
 int /*<<< orphan*/  IIC_WAIT ; 
 int /*<<< orphan*/  RTC8583_SC_REG ; 
 int /*<<< orphan*/  RTC8583_USERSRAM_REG ; 
 int /*<<< orphan*/  bcd2bin (int) ; 
 int /*<<< orphan*/  bin2bcd (int) ; 
 int /*<<< orphan*/  clock_dbgprint_bcd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bcd_clocktime*) ; 
 int /*<<< orphan*/  clock_ts_to_bcd (struct timespec*,struct bcd_clocktime*,int) ; 
 struct rtc8583_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iicbus_release_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iicbus_request_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc8583_write1 (struct rtc8583_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rtc8583_writeto (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct time_regs*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ utc_offset () ; 

__attribute__((used)) static int
rtc8583_settime(device_t dev, struct timespec *ts)
{
	struct rtc8583_softc	*sc;
	struct bcd_clocktime 	 bct;
	struct time_regs	 tregs;
	uint8_t			 sreg;
	int 			 err;

	sc = device_get_softc(dev);
	ts->tv_sec -= utc_offset();
	clock_ts_to_bcd(ts, &bct, false);
	clock_dbgprint_bcd(sc->dev, CLOCK_DBG_WRITE, &bct);

	/* The 'msec' reg is actually 1/100ths, in bcd.  */
	tregs.msec  = bin2bcd(ts->tv_nsec / (10 * 1000 * 1000));
	tregs.sec   = bct.sec;
	tregs.min   = bct.min;
	tregs.hour  = bct.hour;
	tregs.day   = bct.day | (bct.year & 0x03 << 6);
	tregs.month = bct.mon;

	if ((err = iicbus_request_bus(sc->busdev, sc->dev, IIC_WAIT)) != 0)
		return (err);
	err = rtc8583_writeto(sc->dev, RTC8583_SC_REG, &tregs,
	    sizeof(tregs), IIC_WAIT);
	sreg = bcd2bin(bct.year & 0xff);
	/* save to year to sram */
	rtc8583_write1(sc, RTC8583_USERSRAM_REG, sreg);
	iicbus_release_bus(sc->busdev, sc->dev);

	return (err);
}