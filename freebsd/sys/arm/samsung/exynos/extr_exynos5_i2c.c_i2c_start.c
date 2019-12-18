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
typedef  int u_char ;
struct i2c_softc {int /*<<< orphan*/  mutex; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ACKGEN ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  DPRINTF (char*,...) ; 
 int /*<<< orphan*/  I2CCON ; 
 int /*<<< orphan*/  I2CDS ; 
 int I2CMODE_MT ; 
 int I2CMODE_S ; 
 int /*<<< orphan*/  I2CSTAT ; 
 int I2C_START_STOP ; 
 int IIC_EBUSERR ; 
 int IIC_ENOACK ; 
 int IIC_NOERR ; 
 int IRQ_EN ; 
 int READ1 (struct i2c_softc*,int /*<<< orphan*/ ) ; 
 int RXTX_EN ; 
 int /*<<< orphan*/  WRITE1 (struct i2c_softc*,int /*<<< orphan*/ ,int) ; 
 struct i2c_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_ack (struct i2c_softc*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int wait_for_iif (struct i2c_softc*) ; 
 int wait_for_nibb (struct i2c_softc*) ; 

__attribute__((used)) static int
i2c_start(device_t dev, u_char slave, int timeout)
{
	struct i2c_softc *sc;
	int error;
	int reg;

	sc = device_get_softc(dev);

	DPRINTF("i2c start\n");

	mtx_lock(&sc->mutex);

#if 0
	DPRINTF("I2CCON == 0x%08x\n", READ1(sc, I2CCON));
	DPRINTF("I2CSTAT == 0x%08x\n", READ1(sc, I2CSTAT));
#endif

	if (slave & 1) {
		slave &= ~(1);
		slave <<= 1;
		slave |= 1;
	} else {
		slave <<= 1;
	}

	error = wait_for_nibb(sc);
	if (error) {
		mtx_unlock(&sc->mutex);
		DPRINTF("cant i2c start: IIC_EBUSERR\n");
		return (IIC_EBUSERR);
	}

	reg = READ1(sc, I2CCON);
	reg |= (IRQ_EN | ACKGEN);
	WRITE1(sc, I2CCON, reg);

	WRITE1(sc, I2CDS, slave);
	DELAY(50);

	reg = (RXTX_EN);
	reg |= I2C_START_STOP;
	reg |= (I2CMODE_MT << I2CMODE_S);
	WRITE1(sc, I2CSTAT, reg);

	error = wait_for_iif(sc);
	if (error) {
		DPRINTF("cant i2c start: iif error\n");

		mtx_unlock(&sc->mutex);
		return (error);
	}

	if (!is_ack(sc)) {
		DPRINTF("cant i2c start: no ack\n");

		mtx_unlock(&sc->mutex);
		return (IIC_ENOACK);
	}

	mtx_unlock(&sc->mutex);
	return (IIC_NOERR);
}