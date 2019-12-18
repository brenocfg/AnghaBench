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
typedef  void* uint8_t ;
struct i2c_softc {int /*<<< orphan*/  mutex; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ACKGEN ; 
 int /*<<< orphan*/  DPRINTF (char*,...) ; 
 int /*<<< orphan*/  I2CCON ; 
 int /*<<< orphan*/  I2CDS ; 
 int I2CMODE_MR ; 
 int I2CMODE_S ; 
 int /*<<< orphan*/  I2CSTAT ; 
 int I2C_START_STOP ; 
 int IIC_NOERR ; 
 void* READ1 (struct i2c_softc*,int /*<<< orphan*/ ) ; 
 int RXTX_EN ; 
 int /*<<< orphan*/  WRITE1 (struct i2c_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clear_ipend (struct i2c_softc*) ; 
 struct i2c_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int wait_for_iif (struct i2c_softc*) ; 

__attribute__((used)) static int
i2c_read(device_t dev, char *buf, int len,
    int *read, int last, int delay)
{
	struct i2c_softc *sc;
	int error;
	int reg;
	uint8_t d;

	sc = device_get_softc(dev);

	DPRINTF("i2c read\n");

	reg = (RXTX_EN);
	reg |= (I2CMODE_MR << I2CMODE_S);
	reg |= I2C_START_STOP;
	WRITE1(sc, I2CSTAT, reg);

	*read = 0;
	mtx_lock(&sc->mutex);

	/* dummy read */
	clear_ipend(sc);
	error = wait_for_iif(sc);
	if (error) {
		DPRINTF("cant i2c read: iif error\n");
		mtx_unlock(&sc->mutex);
		return (error);
	}
	READ1(sc, I2CDS);

	DPRINTF("Read ");
	while (*read < len) {

		/* Do not ack last read */
		if (*read == (len - 1)) {
			reg = READ1(sc, I2CCON);
			reg &= ~(ACKGEN);
			WRITE1(sc, I2CCON, reg);
		}

		clear_ipend(sc);

		error = wait_for_iif(sc);
		if (error) {
			DPRINTF("cant i2c read: iif error\n");
			mtx_unlock(&sc->mutex);
			return (error);
		}

		d = READ1(sc, I2CDS);
		DPRINTF("0x%02x ", d);
		*buf++ = d;
		(*read)++;
	}
	DPRINTF("\n");

	mtx_unlock(&sc->mutex);
	return (IIC_NOERR);
}