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
typedef  int /*<<< orphan*/  u_char ;
struct i2c_softc {int /*<<< orphan*/  mutex; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  I2CCR_RSTA ; 
 int /*<<< orphan*/  I2C_CONTROL_REG ; 
 int /*<<< orphan*/  I2C_DATA_REG ; 
 int IIC_NOERR ; 
 struct i2c_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int i2c_do_wait (int /*<<< orphan*/ ,struct i2c_softc*,int,int) ; 
 int /*<<< orphan*/  i2c_flag_set (struct i2c_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_write_reg (struct i2c_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
i2c_repeated_start(device_t dev, u_char slave, int timeout)
{
	struct i2c_softc *sc;
	int error;
	
	sc = device_get_softc(dev);

	mtx_lock(&sc->mutex);
	/* Set repeated start condition */
	i2c_flag_set(sc, I2C_CONTROL_REG ,I2CCR_RSTA);
	/* Write target address - LSB is R/W bit */
	i2c_write_reg(sc, I2C_DATA_REG, slave);
	DELAY(1250);

	error = i2c_do_wait(dev, sc, 1, 1);
	mtx_unlock(&sc->mutex);

	if (error)
		return (error);

	return (IIC_NOERR);
}