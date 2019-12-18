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
typedef  int uint32_t ;
struct twsi_softc {int /*<<< orphan*/  mutex; int /*<<< orphan*/  reg_data; int /*<<< orphan*/  reg_status; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int IIC_ESTATUS ; 
 int IIC_ETIMEOUT ; 
 int IIC_NOERR ; 
 int /*<<< orphan*/  TWSI_CONTROL_ACK ; 
 int /*<<< orphan*/  TWSI_CONTROL_IFLG ; 
 void* TWSI_READ (struct twsi_softc*,int /*<<< orphan*/ ) ; 
 int TWSI_STATUS_DATA_RD_ACK ; 
 int TWSI_STATUS_DATA_RD_NOACK ; 
 int /*<<< orphan*/  debugf (int /*<<< orphan*/ ,char*,int) ; 
 struct twsi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  twsi_clear_iflg (struct twsi_softc*) ; 
 int /*<<< orphan*/  twsi_control_clear (struct twsi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twsi_control_set (struct twsi_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ twsi_poll_ctrl (struct twsi_softc*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
twsi_read(device_t dev, char *buf, int len, int *read, int last, int delay)
{
	struct twsi_softc *sc;
	uint32_t status;
	int last_byte, rv;

	sc = device_get_softc(dev);

	mtx_lock(&sc->mutex);
	*read = 0;
	while (*read < len) {
		/*
		 * Check if we are reading last byte of the last buffer,
		 * do not send ACK then, per I2C specs
		 */
		last_byte = ((*read == len - 1) && last) ? 1 : 0;
		if (last_byte)
			twsi_control_clear(sc, TWSI_CONTROL_ACK);
		else
			twsi_control_set(sc, TWSI_CONTROL_ACK);

		twsi_clear_iflg(sc);
		DELAY(1000);

		if (twsi_poll_ctrl(sc, delay, TWSI_CONTROL_IFLG)) {
			debugf(dev, "timeout reading data (delay=%d)\n", delay);
			rv = IIC_ETIMEOUT;
			goto out;
		}

		status = TWSI_READ(sc, sc->reg_status);
		if (status != (last_byte ?
		    TWSI_STATUS_DATA_RD_NOACK : TWSI_STATUS_DATA_RD_ACK)) {
			debugf(dev, "wrong status (%02x) while reading\n", status);
			rv = IIC_ESTATUS;
			goto out;
		}

		*buf++ = TWSI_READ(sc, sc->reg_data);
		(*read)++;
	}
	rv = IIC_NOERR;
out:
	mtx_unlock(&sc->mutex);
	return (rv);
}