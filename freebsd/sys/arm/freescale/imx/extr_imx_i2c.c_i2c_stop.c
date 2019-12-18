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
struct i2c_softc {int /*<<< orphan*/  slave; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_DEBUGF (struct i2c_softc*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I2CCR_MEN ; 
 int /*<<< orphan*/  I2C_CONTROL_REG ; 
 int IIC_NOERR ; 
 struct i2c_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_write_reg (struct i2c_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_busbusy (struct i2c_softc*,int) ; 

__attribute__((used)) static int
i2c_stop(device_t dev)
{
	struct i2c_softc *sc;

	sc = device_get_softc(dev);

	i2c_write_reg(sc, I2C_CONTROL_REG, I2CCR_MEN);
	wait_for_busbusy(sc, false);
	i2c_write_reg(sc, I2C_CONTROL_REG, 0);
	DEVICE_DEBUGF(sc, 2, "stop   0x%02x\n", sc->slave);
	return (IIC_NOERR);
}