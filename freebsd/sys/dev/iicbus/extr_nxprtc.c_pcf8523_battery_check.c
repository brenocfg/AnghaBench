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
struct timespec {scalar_t__ tv_sec; } ;
struct nxprtc_softc {scalar_t__ bat_time; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int PCF8523_B_CS3_BLF ; 
 int /*<<< orphan*/  PCF8523_B_CS3_PM_DSNBM ; 
 int /*<<< orphan*/  PCF8523_B_CS3_PM_STD ; 
 int /*<<< orphan*/  PCF8523_R_CS3 ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  getnanouptime (struct timespec*) ; 
 int /*<<< orphan*/  mstosbt (int) ; 
 int /*<<< orphan*/  pause_sbt (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int read_reg (struct nxprtc_softc*,int /*<<< orphan*/ ,int*) ; 
 int write_reg (struct nxprtc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pcf8523_battery_check(struct nxprtc_softc *sc)
{
	struct timespec ts;
	int err;
	uint8_t cs3;

	/* We check the battery when starting up, and then only once a day. */
	getnanouptime(&ts);
	if (ts.tv_sec < sc->bat_time)
		return (0);
	sc->bat_time = ts.tv_sec + (60 * 60 * 24);

	/*
	 * The 8523, 2127, and 2129 chips have a "power manager" which includes
	 * an optional battery voltage monitor and several choices for power
	 * switching modes.  The battery monitor uses a lot of current and it
	 * remains active when running from battery, making it the "drain my
	 * battery twice as fast" mode.  So, we run the chip in direct-switching
	 * mode with the battery monitor disabled, reducing the current draw
	 * when running on battery from 1930nA to 880nA.  While it's not clear
	 * from the datasheets, empirical testing shows that both disabling the
	 * battery monitor and using direct-switch mode are required to get the
	 * full power savings.
	 *
	 * There isn't any need to continuously monitor the battery voltage, so
	 * this function is used to periodically enable the monitor, check the
	 * voltage, then return to the low-power monitor-disabled mode.
	 */
	err = write_reg(sc, PCF8523_R_CS3, PCF8523_B_CS3_PM_STD);
	if (err != 0) {
		device_printf(sc->dev, "cannot write CS3 reg\n");
		return (err);
	}
	pause_sbt("nxpbat", mstosbt(10), 0, 0);
	if ((err = read_reg(sc, PCF8523_R_CS3, &cs3)) != 0) {
		device_printf(sc->dev, "cannot read CS3 reg\n");
		return (err);
	}
	err = write_reg(sc, PCF8523_R_CS3, PCF8523_B_CS3_PM_DSNBM);
	if (err != 0) {
		device_printf(sc->dev, "cannot write CS3 reg\n");
		return (err);
	}

	if (cs3 & PCF8523_B_CS3_BLF)
		device_printf(sc->dev, "WARNING: RTC battery is low\n");

	return (0);
}