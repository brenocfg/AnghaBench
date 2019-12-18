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
struct fman_softc {int qman_chan_count; int qman_chan_base; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct fman_softc* device_get_softc (int /*<<< orphan*/ ) ; 

int
fman_qman_channel_id(device_t dev, int port)
{
	struct fman_softc *sc;
	int qman_port_id[] = {0x31, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e,
	    0x2f, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};
	int i;

	sc = device_get_softc(dev);
	for (i = 0; i < sc->qman_chan_count; i++) {
		if (qman_port_id[i] == port)
			return (sc->qman_chan_base + i);
	}

	return (0);
}