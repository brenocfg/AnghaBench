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
struct vtmmio_softc {int /*<<< orphan*/ * vtmmio_child_dev; int /*<<< orphan*/ * res; int /*<<< orphan*/ * dev; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  VIRTIO_CONFIG_STATUS_ACK ; 
 int /*<<< orphan*/  VIRTIO_CONFIG_STATUS_FAILED ; 
 int /*<<< orphan*/  bus_alloc_resource_any (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct vtmmio_softc* device_get_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vtmmio_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vtmmio_probe_and_attach_child (struct vtmmio_softc*) ; 
 int /*<<< orphan*/  vtmmio_reset (struct vtmmio_softc*) ; 
 int /*<<< orphan*/  vtmmio_set_status (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
vtmmio_attach(device_t dev)
{
	struct vtmmio_softc *sc;
	device_t child;
	int rid;

	sc = device_get_softc(dev);
	sc->dev = dev;

	rid = 0;
	sc->res[0] = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
			RF_ACTIVE);
	if (!sc->res[0]) {
		device_printf(dev, "Cannot allocate memory window.\n");
		return (ENXIO);
	}

	vtmmio_reset(sc);

	/* Tell the host we've noticed this device. */
	vtmmio_set_status(dev, VIRTIO_CONFIG_STATUS_ACK);

	if ((child = device_add_child(dev, NULL, -1)) == NULL) {
		device_printf(dev, "Cannot create child device.\n");
		vtmmio_set_status(dev, VIRTIO_CONFIG_STATUS_FAILED);
		vtmmio_detach(dev);
		return (ENOMEM);
	}

	sc->vtmmio_child_dev = child;
	vtmmio_probe_and_attach_child(sc);

	return (0);
}