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
typedef  int /*<<< orphan*/  uint32_t ;
struct bcm_mbox_softc {scalar_t__* have_message; scalar_t__* msg; int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  MBOX_DATA (scalar_t__) ; 
 int /*<<< orphan*/  MBOX_LOCK (struct bcm_mbox_softc*) ; 
 int /*<<< orphan*/  MBOX_UNLOCK (struct bcm_mbox_softc*) ; 
 int /*<<< orphan*/  REG_STATUS ; 
 int STATUS_EMPTY ; 
 scalar_t__ bcm_mbox_read_msg (struct bcm_mbox_softc*,int*) ; 
 int /*<<< orphan*/  cold ; 
 struct bcm_mbox_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dprintf (char*,int,...) ; 
 int hz ; 
 int mbox_read_4 (struct bcm_mbox_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ mtx_sleep (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
bcm_mbox_read(device_t dev, int chan, uint32_t *data)
{
	struct bcm_mbox_softc *sc = device_get_softc(dev);
	int err, read_chan;

	dprintf("bcm_mbox_read: chan %d\n", chan);

	err = 0;
	MBOX_LOCK(sc);
	if (!cold) {
		if (sc->have_message[chan] == 0) {
			if (mtx_sleep(&sc->have_message[chan], &sc->lock, 0,
			    "mbox", 10*hz) != 0) {
				device_printf(dev, "timeout waiting for message on chan %d\n", chan);
				err = ETIMEDOUT;
			}
		}
	} else {
		do {
			/* Wait for a message */
			while ((mbox_read_4(sc, REG_STATUS) & STATUS_EMPTY))
				;
			/* Read the message */
			if (bcm_mbox_read_msg(sc, &read_chan) != 0) {
				err = EINVAL;
				goto out;
			}
		} while (read_chan != chan);
	}
	/*
	 *  get data from intr handler, the same channel is never coming
	 *  because of holding sc lock.
	 */
	*data = MBOX_DATA(sc->msg[chan]);
	sc->msg[chan] = 0;
	sc->have_message[chan] = 0;
out:
	MBOX_UNLOCK(sc);
	dprintf("bcm_mbox_read: chan %d, data %08x\n", chan, *data);

	return (err);
}