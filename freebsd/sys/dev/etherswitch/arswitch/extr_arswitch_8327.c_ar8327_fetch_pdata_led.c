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
struct arswitch_softc {int /*<<< orphan*/  sc_dev; } ;
struct ar8327_led_cfg {int led_ctrl0; int led_ctrl1; int led_ctrl2; int led_ctrl3; int open_drain; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 scalar_t__ resource_int_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*) ; 

__attribute__((used)) static int
ar8327_fetch_pdata_led(struct arswitch_softc *sc,
    struct ar8327_led_cfg *lcfg)
{
	int val;

	val = 0;
	if (resource_int_value(device_get_name(sc->sc_dev),
	    device_get_unit(sc->sc_dev),
	    "led.ctrl0", &val) != 0)
		return (0);
	lcfg->led_ctrl0 = val;

	val = 0;
	if (resource_int_value(device_get_name(sc->sc_dev),
	    device_get_unit(sc->sc_dev),
	    "led.ctrl1", &val) != 0)
		return (0);
	lcfg->led_ctrl1 = val;

	val = 0;
	if (resource_int_value(device_get_name(sc->sc_dev),
	    device_get_unit(sc->sc_dev),
	    "led.ctrl2", &val) != 0)
		return (0);
	lcfg->led_ctrl2 = val;

	val = 0;
	if (resource_int_value(device_get_name(sc->sc_dev),
	    device_get_unit(sc->sc_dev),
	    "led.ctrl3", &val) != 0)
		return (0);
	lcfg->led_ctrl3 = val;

	val = 0;
	if (resource_int_value(device_get_name(sc->sc_dev),
	    device_get_unit(sc->sc_dev),
	    "led.open_drain", &val) != 0)
		return (0);
	lcfg->open_drain = val;

	return (1);
}