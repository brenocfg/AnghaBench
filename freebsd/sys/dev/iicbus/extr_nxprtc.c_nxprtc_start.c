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
struct nxprtc_softc {int chiptype; int is212x; int /*<<< orphan*/  dev; scalar_t__ use_timer; int /*<<< orphan*/  config_hook; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CLOCKF_GETTIME_NO_ADJ ; 
 int CLOCKF_SETTIME_NO_TS ; 
 int TMR_TICKS_SEC ; 
#define  TYPE_PCA2129 133 
#define  TYPE_PCA8565 132 
#define  TYPE_PCF2127 131 
#define  TYPE_PCF2129 130 
#define  TYPE_PCF8523 129 
#define  TYPE_PCF8563 128 
 int /*<<< orphan*/  clock_register_flags (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  clock_schedule (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  config_intrhook_disestablish (int /*<<< orphan*/ *) ; 
 struct nxprtc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pcf2127_start_timer (struct nxprtc_softc*) ; 
 int /*<<< orphan*/  pcf8523_start (struct nxprtc_softc*) ; 
 int /*<<< orphan*/  pcf8523_start_timer (struct nxprtc_softc*) ; 
 int /*<<< orphan*/  pcf8563_start (struct nxprtc_softc*) ; 
 int /*<<< orphan*/  pcf8563_start_timer (struct nxprtc_softc*) ; 

__attribute__((used)) static void
nxprtc_start(void *dev)
{
	struct nxprtc_softc *sc;
	int clockflags, resolution;

	sc = device_get_softc((device_t)dev);
	config_intrhook_disestablish(&sc->config_hook);

	/* First do chip-specific inits. */
	switch (sc->chiptype) {
	case TYPE_PCA2129:
	case TYPE_PCF2129:
	case TYPE_PCF2127:
		sc->is212x = true;
		if (pcf8523_start(sc) != 0)
			return;
		if (pcf2127_start_timer(sc) != 0) {
			device_printf(sc->dev, "cannot set up timer\n");
			return;
		}
		break;
	case TYPE_PCF8523:
		if (pcf8523_start(sc) != 0)
			return;
		if (pcf8523_start_timer(sc) != 0) {
			device_printf(sc->dev, "cannot set up timer\n");
			return;
		}
		break;
	case TYPE_PCA8565:
	case TYPE_PCF8563:
		if (pcf8563_start(sc) != 0)
			return;
		if (pcf8563_start_timer(sc) != 0) {
			device_printf(sc->dev, "cannot set up timer\n");
			return;
		}
		break;
	default:
		device_printf(sc->dev, "missing init code for this chiptype\n");
		return;
	}

	/*
	 * Everything looks good if we make it to here; register as an RTC.  If
	 * we're using the timer to count fractional seconds, our resolution is
	 * 1e6/64, about 15.6ms.  Without the timer we still align the RTC clock
	 * when setting it so our error is an average .5s when reading it.
	 * Schedule our clock_settime() method to be called at a .495ms offset
	 * into the second, because the clock hardware resets the divider chain
	 * to the mid-second point when you set the time and it takes about 5ms
	 * of i2c bus activity to set the clock.
	 */
	resolution = sc->use_timer ? 1000000 / TMR_TICKS_SEC : 1000000 / 2;
	clockflags = CLOCKF_GETTIME_NO_ADJ | CLOCKF_SETTIME_NO_TS;
	clock_register_flags(sc->dev, resolution, clockflags);
	clock_schedule(sc->dev, 495000000);
}