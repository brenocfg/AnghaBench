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
 int /*<<< orphan*/  I2C_IBDR ; 
 int IIC_NOERR ; 
 int /*<<< orphan*/  WRITE1 (struct i2c_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct i2c_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vf_i2c_dbg (struct i2c_softc*,char*) ; 
 int wait_for_iif (struct i2c_softc*) ; 

__attribute__((used)) static int
i2c_write(device_t dev, const char *buf, int len, int *sent, int timeout)
{
	struct i2c_softc *sc;
	int error;

	sc = device_get_softc(dev);

	vf_i2c_dbg(sc, "i2c write\n");

	*sent = 0;

	mtx_lock(&sc->mutex);
	while (*sent < len) {

		WRITE1(sc, I2C_IBDR, *buf++);

		error = wait_for_iif(sc);
		if (error) {
			mtx_unlock(&sc->mutex);
			return (error);
		}

		(*sent)++;
	}
	mtx_unlock(&sc->mutex);

	return (IIC_NOERR);
}