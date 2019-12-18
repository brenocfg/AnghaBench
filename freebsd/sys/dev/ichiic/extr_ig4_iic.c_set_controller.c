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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  ig4iic_softc_t ;

/* Variables and functions */
 int IG4_I2C_ENABLE ; 
 int /*<<< orphan*/  IG4_REG_CLR_INTR ; 
 int /*<<< orphan*/  IG4_REG_ENABLE_STATUS ; 
 int /*<<< orphan*/  IG4_REG_I2C_EN ; 
 int IIC_ETIMEOUT ; 
 int /*<<< orphan*/  ig4iic_set_intr_mask (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pause (char*,int) ; 
 int reg_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
set_controller(ig4iic_softc_t *sc, uint32_t ctl)
{
	int retry;
	int error;
	uint32_t v;

	/*
	 * When the controller is enabled, interrupt on STOP detect
	 * or receive character ready and clear pending interrupts.
	 */
	ig4iic_set_intr_mask(sc, 0);
	if (ctl & IG4_I2C_ENABLE)
		reg_read(sc, IG4_REG_CLR_INTR);

	reg_write(sc, IG4_REG_I2C_EN, ctl);
	error = IIC_ETIMEOUT;

	for (retry = 100; retry > 0; --retry) {
		v = reg_read(sc, IG4_REG_ENABLE_STATUS);
		if (((v ^ ctl) & IG4_I2C_ENABLE) == 0) {
			error = 0;
			break;
		}
		pause("i2cslv", 1);
	}
	return (error);
}