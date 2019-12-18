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
struct vmbus_ic_softc {int /*<<< orphan*/  ic_buf; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 struct vmbus_ic_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmbus_chan_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmbus_get_channel (int /*<<< orphan*/ ) ; 

int
vmbus_ic_detach(device_t dev)
{
	struct vmbus_ic_softc *sc = device_get_softc(dev);

	vmbus_chan_close(vmbus_get_channel(dev));
	free(sc->ic_buf, M_DEVBUF);

	return (0);
}