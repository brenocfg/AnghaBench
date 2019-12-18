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
typedef  int u_char ;
struct i2c_softc {int /*<<< orphan*/  mutex; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int I2CCR_MEN ; 
 int I2CCR_MSTA ; 
 int I2CCR_MTX ; 
 int I2CSR_MBB ; 
 int /*<<< orphan*/  I2C_CONTROL_REG ; 
 int /*<<< orphan*/  I2C_DATA_REG ; 
 int /*<<< orphan*/  I2C_STATUS_REG ; 
 int IIC_EBUSERR ; 
 int IIC_NOERR ; 
 int /*<<< orphan*/  debugf (char*) ; 
 struct i2c_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int i2c_do_wait (int /*<<< orphan*/ ,struct i2c_softc*,int,int) ; 
 int i2c_read_reg (struct i2c_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_write_reg (struct i2c_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
i2c_start(device_t dev, u_char slave, int timeout)
{
	struct i2c_softc *sc;
	uint8_t status;
	int error;

	sc = device_get_softc(dev);
	DELAY(1000);

	mtx_lock(&sc->mutex);
	status = i2c_read_reg(sc, I2C_STATUS_REG);
	/* Check if bus is idle or busy */
	if (status & I2CSR_MBB) {
		debugf("bus busy");
		mtx_unlock(&sc->mutex);
		i2c_stop(dev);
		return (IIC_EBUSERR);
	}

	/* Set start condition */
	i2c_write_reg(sc, I2C_CONTROL_REG, I2CCR_MEN | I2CCR_MSTA | I2CCR_MTX);
	/* Write target address - LSB is R/W bit */
	i2c_write_reg(sc, I2C_DATA_REG, slave);
	DELAY(1250);

	error = i2c_do_wait(dev, sc, 1, 1);

	mtx_unlock(&sc->mutex);
	if (error)
		return (error);

	return (IIC_NOERR);
}