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
typedef  scalar_t__ uint8_t ;
struct ds13rtc_softc {int chiptype; int use_ampm; int /*<<< orphan*/  dev; scalar_t__ secaddr; int /*<<< orphan*/  is_binary_counter; scalar_t__ osfaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCKF_SETTIME_NO_ADJ ; 
 scalar_t__ DS130x_R_CONTROL ; 
 scalar_t__ DS133x_R_CONTROL ; 
 scalar_t__ DS1341_R_CONTROL ; 
 scalar_t__ DS1388_R_CONTROL ; 
 scalar_t__ DS13xx_B_HOUR_AMPM ; 
 scalar_t__ DS13xx_B_STATUS_OSF ; 
 scalar_t__ DS13xx_R_NONE ; 
#define  TYPE_DS1307 140 
#define  TYPE_DS1308 139 
#define  TYPE_DS1337 138 
#define  TYPE_DS1338 137 
#define  TYPE_DS1339 136 
#define  TYPE_DS1340 135 
#define  TYPE_DS1341 134 
#define  TYPE_DS1342 133 
#define  TYPE_DS1371 132 
#define  TYPE_DS1372 131 
#define  TYPE_DS1374 130 
#define  TYPE_DS1375 129 
#define  TYPE_DS1388 128 
 int /*<<< orphan*/  clock_register_flags (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clock_schedule (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ read_reg (struct ds13rtc_softc*,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  write_reg (struct ds13rtc_softc*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ds13rtc_start(void *arg)
{
	struct ds13rtc_softc *sc;
	uint8_t ctlreg, statreg;

	sc = arg;

	/*
	 * Every chip in this family can be usefully initialized by writing 0 to
	 * the control register, except DS1375 which has an external oscillator
	 * controlled by values in the ctlreg that we know nothing about, so
	 * we'd best leave them alone.  For all other chips, writing 0 enables
	 * the oscillator, disables signals/outputs in battery-backed mode
	 * (saves power) and disables features like watchdog timers and alarms.
	 */
	switch (sc->chiptype) {
	case TYPE_DS1307:
	case TYPE_DS1308:
	case TYPE_DS1338:
	case TYPE_DS1340:
	case TYPE_DS1371:
	case TYPE_DS1372:
	case TYPE_DS1374:
		ctlreg = DS130x_R_CONTROL;
		break;
	case TYPE_DS1337:
	case TYPE_DS1339:
		ctlreg = DS133x_R_CONTROL;
		break;
	case TYPE_DS1341:
	case TYPE_DS1342:
		ctlreg = DS1341_R_CONTROL;
		break;
	case TYPE_DS1375:
		ctlreg = DS13xx_R_NONE;
		break;
	case TYPE_DS1388:
		ctlreg = DS1388_R_CONTROL;
		break;
	default:
		device_printf(sc->dev, "missing init code for this chiptype\n");
		return;
	}
	if (ctlreg != DS13xx_R_NONE)
		write_reg(sc, ctlreg, 0);

	/*
	 * Common init.  Read the OSF/CH status bit and report stopped clocks to
	 * the user.  The status bit will be cleared the first time we write
	 * valid time to the chip (and must not be cleared before that).
	 */
	if (read_reg(sc, sc->osfaddr, &statreg) != 0) {
		device_printf(sc->dev, "cannot read RTC clock status bit\n");
		return;
	}
	if (statreg & DS13xx_B_STATUS_OSF) {
		device_printf(sc->dev, 
		    "WARNING: RTC battery failed; time is invalid\n");
	}

	/*
	 * Figure out whether the chip is configured for AM/PM mode.  On all
	 * chips that do AM/PM mode, the flag bit is in the hours register,
	 * which is secaddr+2.
	 */
	if ((sc->chiptype != TYPE_DS1340) && !sc->is_binary_counter) {
		if (read_reg(sc, sc->secaddr + 2, &statreg) != 0) {
			device_printf(sc->dev,
			    "cannot read RTC clock AM/PM bit\n");
			return;
		}
		if (statreg & DS13xx_B_HOUR_AMPM)
			sc->use_ampm = true;
	}

	/*
	 * Everything looks good if we make it to here; register as an RTC.
	 * Schedule RTC updates to happen just after top-of-second.
	 */
	clock_register_flags(sc->dev, 1000000, CLOCKF_SETTIME_NO_ADJ);
	clock_schedule(sc->dev, 1);
}