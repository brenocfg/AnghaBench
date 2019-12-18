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
struct twsi_softc {int /*<<< orphan*/  mutex; int /*<<< orphan*/  reg_status; int /*<<< orphan*/  reg_data; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int IIC_ESTATUS ; 
 int IIC_ETIMEOUT ; 
 int IIC_NOERR ; 
 int /*<<< orphan*/  TWSI_CONTROL_IFLG ; 
 int TWSI_READ (struct twsi_softc*,int /*<<< orphan*/ ) ; 
 int TWSI_STATUS_DATA_WR_ACK ; 
 int /*<<< orphan*/  TWSI_WRITE (struct twsi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugf (int /*<<< orphan*/ ,char*,int) ; 
 struct twsi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  twsi_clear_iflg (struct twsi_softc*) ; 
 scalar_t__ twsi_poll_ctrl (struct twsi_softc*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
twsi_write(device_t dev, const char *buf, int len, int *sent, int timeout)
{
	struct twsi_softc *sc;
	uint32_t status;
	int rv;

	sc = device_get_softc(dev);

	mtx_lock(&sc->mutex);
	*sent = 0;
	while (*sent < len) {
		TWSI_WRITE(sc, sc->reg_data, *buf++);

		twsi_clear_iflg(sc);
		DELAY(1000);
		if (twsi_poll_ctrl(sc, timeout, TWSI_CONTROL_IFLG)) {
			debugf(dev, "timeout writing data (timeout=%d)\n", timeout);
			rv = IIC_ETIMEOUT;
			goto out;
		}

		status = TWSI_READ(sc, sc->reg_status);
		if (status != TWSI_STATUS_DATA_WR_ACK) {
			debugf(dev, "wrong status (%02x) while writing\n", status);
			rv = IIC_ESTATUS;
			goto out;
		}
		(*sent)++;
	}
	rv = IIC_NOERR;
out:
	mtx_unlock(&sc->mutex);
	return (rv);
}