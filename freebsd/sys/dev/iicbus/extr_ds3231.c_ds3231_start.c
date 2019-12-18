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
struct sysctl_oid_list {int dummy; } ;
struct sysctl_oid {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
struct ds3231_softc {int sc_status; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  enum_hook; } ;
typedef  scalar_t__ device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCKF_SETTIME_NO_ADJ ; 
 int CTLFLAG_MPSAFE ; 
 int CTLFLAG_RD ; 
 int CTLFLAG_RW ; 
 int CTLTYPE_INT ; 
 int CTLTYPE_STRING ; 
 int CTLTYPE_UINT ; 
 int DS3231_STATUS_OSF ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,struct ds3231_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 struct sysctl_oid_list* SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 int /*<<< orphan*/  clock_register_flags (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clock_schedule (scalar_t__,int) ; 
 int /*<<< orphan*/  config_intrhook_disestablish (int /*<<< orphan*/ *) ; 
 struct ds3231_softc* device_get_softc (scalar_t__) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (scalar_t__) ; 
 struct sysctl_oid* device_get_sysctl_tree (scalar_t__) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ds3231_bbsqw_sysctl ; 
 int /*<<< orphan*/  ds3231_conv_sysctl ; 
 scalar_t__ ds3231_ctrl_read (struct ds3231_softc*) ; 
 int /*<<< orphan*/  ds3231_ctrl_write (struct ds3231_softc*) ; 
 int /*<<< orphan*/  ds3231_en32khz_sysctl ; 
 int /*<<< orphan*/  ds3231_sqw_freq_sysctl ; 
 int /*<<< orphan*/  ds3231_sqw_mode_sysctl ; 
 scalar_t__ ds3231_status_read (struct ds3231_softc*) ; 
 int /*<<< orphan*/  ds3231_status_write (struct ds3231_softc*,int,int) ; 
 int /*<<< orphan*/  ds3231_temp_sysctl ; 

__attribute__((used)) static void
ds3231_start(void *xdev)
{
	device_t dev;
	struct ds3231_softc *sc;
	struct sysctl_ctx_list *ctx;
	struct sysctl_oid *tree_node;
	struct sysctl_oid_list *tree;

	dev = (device_t)xdev;
	sc = device_get_softc(dev);
	ctx = device_get_sysctl_ctx(dev);
	tree_node = device_get_sysctl_tree(dev);
	tree = SYSCTL_CHILDREN(tree_node);

	config_intrhook_disestablish(&sc->enum_hook);
	if (ds3231_ctrl_read(sc) != 0)
		return;
	if (ds3231_status_read(sc) != 0)
		return;
	/*
	 * Warn if the clock stopped, but don't restart it until the first
	 * clock_settime() call.
	 */
	if (sc->sc_status & DS3231_STATUS_OSF) {
		device_printf(sc->sc_dev,
		    "WARNING: RTC clock stopped, check the battery.\n");
	}

	/*
	 * Ack any pending alarm interrupts and clear the EOSC bit to ensure the
	 * clock runs even when on battery power.  Do not give up if these
	 * writes fail, because a factory-fresh chip is in a special mode that
	 * disables much of the chip to save battery power, and the only thing
	 * that gets it out of that mode is writing to the time registers.  In
	 * these pristine chips, the EOSC and alarm bits are zero already, so
	 * the first valid write of time will get everything running properly.
	 */
	ds3231_status_write(sc, 1, 1);
	ds3231_ctrl_write(sc);

	/* Temperature. */
	SYSCTL_ADD_PROC(ctx, tree, OID_AUTO, "temperature",
	    CTLTYPE_INT | CTLFLAG_RD | CTLFLAG_MPSAFE, sc, 0,
	    ds3231_temp_sysctl, "IK", "Current temperature");
	/* Configuration parameters. */
	SYSCTL_ADD_PROC(ctx, tree, OID_AUTO, "temp_conv",
	    CTLFLAG_RW | CTLTYPE_UINT | CTLFLAG_MPSAFE, sc, 0,
	    ds3231_conv_sysctl, "IU",
	    "DS3231 start a new temperature converstion");
	SYSCTL_ADD_PROC(ctx, tree, OID_AUTO, "bbsqw",
	    CTLFLAG_RW | CTLTYPE_UINT | CTLFLAG_MPSAFE, sc, 0,
	    ds3231_bbsqw_sysctl, "IU",
	    "DS3231 battery-backed square-wave output enable");
	SYSCTL_ADD_PROC(ctx, tree, OID_AUTO, "sqw_freq",
	    CTLFLAG_RW | CTLTYPE_UINT | CTLFLAG_MPSAFE, sc, 0,
	    ds3231_sqw_freq_sysctl, "IU",
	    "DS3231 square-wave output frequency");
	SYSCTL_ADD_PROC(ctx, tree, OID_AUTO, "sqw_mode",
	    CTLFLAG_RW | CTLTYPE_STRING | CTLFLAG_MPSAFE, sc, 0,
	    ds3231_sqw_mode_sysctl, "A", "DS3231 SQW output mode control");
	SYSCTL_ADD_PROC(ctx, tree, OID_AUTO, "32khz_enable",
	    CTLFLAG_RW | CTLTYPE_UINT | CTLFLAG_MPSAFE, sc, 0,
	    ds3231_en32khz_sysctl, "IU", "DS3231 enable the 32kHz output");

	/*
	 * Register as a clock with 1 second resolution.  Schedule the
	 * clock_settime() method to be called just after top-of-second;
	 * resetting the time resets top-of-second in the hardware.
	 */
	clock_register_flags(dev, 1000000, CLOCKF_SETTIME_NO_ADJ);
	clock_schedule(dev, 1);
}