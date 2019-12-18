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
typedef  int /*<<< orphan*/  uint8_t ;
struct i2c_softc {int /*<<< orphan*/  mutex; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  DPRINTF (char*,...) ; 
 int /*<<< orphan*/  I2CDS ; 
 int IIC_ENOACK ; 
 int IIC_NOERR ; 
 int /*<<< orphan*/  WRITE1 (struct i2c_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_ipend (struct i2c_softc*) ; 
 struct i2c_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_ack (struct i2c_softc*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int wait_for_iif (struct i2c_softc*) ; 

__attribute__((used)) static int
i2c_write(device_t dev, const char *buf, int len, int *sent, int timeout)
{
	struct i2c_softc *sc;
	int error;

	sc = device_get_softc(dev);

	DPRINTF("i2c write\n");

	*sent = 0;

	mtx_lock(&sc->mutex);

	DPRINTF("writing ");
	while (*sent < len) {
		uint8_t d = *buf++;
		DPRINTF("0x%02x ", d);

		WRITE1(sc, I2CDS, d);
		DELAY(50);

		clear_ipend(sc);

		error = wait_for_iif(sc);
		if (error) {
			DPRINTF("cant i2c write: iif error\n");
			mtx_unlock(&sc->mutex);
			return (error);
		}

		if (!is_ack(sc)) {
			DPRINTF("cant i2c write: no ack\n");
			mtx_unlock(&sc->mutex);
			return (IIC_ENOACK);
		}

		(*sent)++;
	}
	DPRINTF("\n");

	mtx_unlock(&sc->mutex);
	return (IIC_NOERR);
}