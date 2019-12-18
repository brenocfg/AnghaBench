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
struct i2c_softc {int /*<<< orphan*/  mutex; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int I2CCR_MEN ; 
 int I2CCR_MSTA ; 
 int I2CCR_TXAK ; 
 int /*<<< orphan*/  I2C_CONTROL_REG ; 
 int /*<<< orphan*/  I2C_DATA_REG ; 
 int IIC_NOERR ; 
 struct i2c_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int i2c_do_wait (int /*<<< orphan*/ ,struct i2c_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_read_reg (struct i2c_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_write_reg (struct i2c_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
i2c_read(device_t dev, char *buf, int len, int *read, int last, int delay)
{
	struct i2c_softc *sc;
	int error;

	sc = device_get_softc(dev);
	*read = 0;

	mtx_lock(&sc->mutex);
	if (len) {
		if (len == 1)
			i2c_write_reg(sc, I2C_CONTROL_REG, I2CCR_MEN |
			    I2CCR_MSTA | I2CCR_TXAK);

		else
			i2c_write_reg(sc, I2C_CONTROL_REG, I2CCR_MEN |
			    I2CCR_MSTA);

		/* dummy read */
		i2c_read_reg(sc, I2C_DATA_REG);
		DELAY(1000);
	}

	while (*read < len) {
		DELAY(1000);
		error = i2c_do_wait(dev, sc, 0, 0);
		if (error) {
			mtx_unlock(&sc->mutex);
			return (error);
		}
		if ((*read == len - 2) && last) {
			i2c_write_reg(sc, I2C_CONTROL_REG, I2CCR_MEN |
			    I2CCR_MSTA | I2CCR_TXAK);
		}

		if ((*read == len - 1) && last) {
			i2c_write_reg(sc, I2C_CONTROL_REG,  I2CCR_MEN |
			    I2CCR_TXAK);
		}

		*buf++ = i2c_read_reg(sc, I2C_DATA_REG);
		(*read)++;
		DELAY(1250);
	}
	mtx_unlock(&sc->mutex);

	return (IIC_NOERR);
}