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
struct iicrb_pin_access {int /*<<< orphan*/  setscl; int /*<<< orphan*/  getscl; int /*<<< orphan*/  setsda; int /*<<< orphan*/  getsda; struct i2c_softc* ctx; } ;
struct i2c_softc {scalar_t__ rb_pinctl_idx; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  fdt_pinctrl_configure (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  i2c_recover_getscl ; 
 int /*<<< orphan*/  i2c_recover_getsda ; 
 int /*<<< orphan*/  i2c_recover_setscl ; 
 int /*<<< orphan*/  i2c_recover_setsda ; 
 int iic_recover_bus (struct iicrb_pin_access*) ; 

__attribute__((used)) static int
i2c_recover_bus(struct i2c_softc *sc)
{
	struct iicrb_pin_access pins;
	int err;

	/*
	 * If we have gpio pinmux config, reconfigure the pins to gpio mode,
	 * invoke iic_recover_bus which checks for a hung bus and bitbangs a
	 * recovery sequence if necessary, then configure the pins back to i2c
	 * mode (idx 0).
	 */
	if (sc->rb_pinctl_idx == 0)
		return (0);

	fdt_pinctrl_configure(sc->dev, sc->rb_pinctl_idx);

	pins.ctx = sc;
	pins.getsda = i2c_recover_getsda;
	pins.setsda = i2c_recover_setsda;
	pins.getscl = i2c_recover_getscl;
	pins.setscl = i2c_recover_setscl;
	err = iic_recover_bus(&pins);

	fdt_pinctrl_configure(sc->dev, 0);

	return (err);
}