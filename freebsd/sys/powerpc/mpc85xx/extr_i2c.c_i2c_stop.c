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
 int I2CCR_TXAK ; 
 int /*<<< orphan*/  I2C_CONTROL_REG ; 
 int IIC_NOERR ; 
 struct i2c_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_write_reg (struct i2c_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
i2c_stop(device_t dev)
{
	struct i2c_softc *sc;

	sc = device_get_softc(dev);
	mtx_lock(&sc->mutex);
	i2c_write_reg(sc, I2C_CONTROL_REG, I2CCR_MEN | I2CCR_TXAK);
	DELAY(1000);
	mtx_unlock(&sc->mutex);

	return (IIC_NOERR);
}