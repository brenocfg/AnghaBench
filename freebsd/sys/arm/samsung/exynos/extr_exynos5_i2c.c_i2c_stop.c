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
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int I2CMODE_M ; 
 int I2CMODE_S ; 
 int /*<<< orphan*/  I2CSTAT ; 
 int IIC_NOERR ; 
 int READ1 (struct i2c_softc*,int /*<<< orphan*/ ) ; 
 int RXTX_EN ; 
 int /*<<< orphan*/  WRITE1 (struct i2c_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clear_ipend (struct i2c_softc*) ; 
 struct i2c_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int wait_for_nibb (struct i2c_softc*) ; 

__attribute__((used)) static int
i2c_stop(device_t dev)
{
	struct i2c_softc *sc;
	int reg;
	int error;

	sc = device_get_softc(dev);

	DPRINTF("i2c stop\n");

	mtx_lock(&sc->mutex);

	reg = READ1(sc, I2CSTAT);
	int mode = (reg >> I2CMODE_S) & I2CMODE_M;

	reg = (RXTX_EN);
	reg |= (mode << I2CMODE_S);
	WRITE1(sc, I2CSTAT, reg);

	clear_ipend(sc);

	error = wait_for_nibb(sc);
	if (error) {
		DPRINTF("cant i2c stop: nibb error\n");
		return (error);
	}

	mtx_unlock(&sc->mutex);
	return (IIC_NOERR);
}