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
struct i2c_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2CCR_MEN ; 
 int /*<<< orphan*/  I2C_CONTROL_REG ; 
 int /*<<< orphan*/  I2C_STATUS_REG ; 
 int /*<<< orphan*/  i2c_write_reg (struct i2c_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_busbusy (struct i2c_softc*,int) ; 

__attribute__((used)) static int
i2c_error_handler(struct i2c_softc *sc, int error)
{

	if (error != 0) {
		i2c_write_reg(sc, I2C_STATUS_REG, 0);
		i2c_write_reg(sc, I2C_CONTROL_REG, I2CCR_MEN);
		wait_for_busbusy(sc, false);
		i2c_write_reg(sc, I2C_CONTROL_REG, 0);
	}
	return (error);
}