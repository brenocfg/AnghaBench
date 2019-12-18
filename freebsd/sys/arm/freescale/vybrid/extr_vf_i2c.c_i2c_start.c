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
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  I2C_IBAD ; 
 int /*<<< orphan*/  I2C_IBCR ; 
 int /*<<< orphan*/  I2C_IBDR ; 
 int /*<<< orphan*/  I2C_IBSR ; 
 int IBCR_IBIE ; 
 int IBCR_MSSL ; 
 int IBCR_NOACK ; 
 int IBCR_TXRX ; 
 int IBSR_IBB ; 
 int IIC_EBUSERR ; 
 int IIC_NOERR ; 
 int READ1 (struct i2c_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE1 (struct i2c_softc*,int /*<<< orphan*/ ,int) ; 
 struct i2c_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vf_i2c_dbg (struct i2c_softc*,char*) ; 
 int wait_for_iif (struct i2c_softc*) ; 

__attribute__((used)) static int
i2c_start(device_t dev, u_char slave, int timeout)
{
	struct i2c_softc *sc;
	int error;
	int reg;

	sc = device_get_softc(dev);

	vf_i2c_dbg(sc, "i2c start\n");

	mtx_lock(&sc->mutex);

	WRITE1(sc, I2C_IBAD, slave);

	if (READ1(sc, I2C_IBSR) & IBSR_IBB) {
		mtx_unlock(&sc->mutex);
		vf_i2c_dbg(sc, "cant i2c start: IIC_EBUSBSY\n");
		return (IIC_EBUSERR);
	}

	/* Set start condition */
	reg = (IBCR_MSSL | IBCR_NOACK | IBCR_IBIE);
	WRITE1(sc, I2C_IBCR, reg);

	DELAY(100);

	reg |= (IBCR_TXRX);
	WRITE1(sc, I2C_IBCR, reg);

	/* Write target address - LSB is R/W bit */
	WRITE1(sc, I2C_IBDR, slave);

	error = wait_for_iif(sc);

	mtx_unlock(&sc->mutex);
	if (error) {
		vf_i2c_dbg(sc, "cant i2c start: iif error\n");
		return (error);
	}

	return (IIC_NOERR);
}