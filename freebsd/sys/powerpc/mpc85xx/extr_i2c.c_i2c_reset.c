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
 int I2C_BAUD_RATE_DEF ; 
 int I2C_BAUD_RATE_FAST ; 
 int /*<<< orphan*/  I2C_CONTROL_REG ; 
 int /*<<< orphan*/  I2C_DFSRR_REG ; 
 int I2C_DFSSR_DIV ; 
 int I2C_ENABLE ; 
 int /*<<< orphan*/  I2C_FDR_REG ; 
 int /*<<< orphan*/  I2C_STATUS_REG ; 
#define  IIC_FAST 131 
#define  IIC_FASTEST 130 
 int IIC_NOERR ; 
#define  IIC_SLOW 129 
#define  IIC_UNKNOWN 128 
 struct i2c_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_write_reg (struct i2c_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
i2c_reset(device_t dev, u_char speed, u_char addr, u_char *oldadr)
{
	struct i2c_softc *sc;
	uint8_t baud_rate;

	sc = device_get_softc(dev);

	switch (speed) {
	case IIC_FAST:
		baud_rate = I2C_BAUD_RATE_FAST;
		break;
	case IIC_SLOW:
	case IIC_UNKNOWN:
	case IIC_FASTEST:
	default:
		baud_rate = I2C_BAUD_RATE_DEF;
		break;
	}

	mtx_lock(&sc->mutex);
	i2c_write_reg(sc, I2C_CONTROL_REG, 0x0);
	i2c_write_reg(sc, I2C_STATUS_REG, 0x0);
	DELAY(1000);
	i2c_write_reg(sc, I2C_FDR_REG, baud_rate);
	i2c_write_reg(sc, I2C_DFSRR_REG, I2C_DFSSR_DIV);
	i2c_write_reg(sc, I2C_CONTROL_REG, I2C_ENABLE);
	DELAY(1000);
	mtx_unlock(&sc->mutex);

	return (IIC_NOERR);
}