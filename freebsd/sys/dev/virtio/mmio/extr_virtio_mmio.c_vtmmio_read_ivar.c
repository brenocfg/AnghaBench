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
struct vtmmio_softc {scalar_t__ vtmmio_child_dev; } ;
typedef  scalar_t__ device_t ;

/* Variables and functions */
 int ENOENT ; 
#define  VIRTIO_IVAR_DEVICE 132 
#define  VIRTIO_IVAR_DEVTYPE 131 
#define  VIRTIO_IVAR_SUBDEVICE 130 
#define  VIRTIO_IVAR_SUBVENDOR 129 
#define  VIRTIO_IVAR_VENDOR 128 
 int /*<<< orphan*/  VIRTIO_MMIO_DEVICE_ID ; 
 int /*<<< orphan*/  VIRTIO_MMIO_VENDOR_ID ; 
 struct vtmmio_softc* device_get_softc (scalar_t__) ; 
 uintptr_t vtmmio_read_config_4 (struct vtmmio_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vtmmio_read_ivar(device_t dev, device_t child, int index, uintptr_t *result)
{
	struct vtmmio_softc *sc;

	sc = device_get_softc(dev);

	if (sc->vtmmio_child_dev != child)
		return (ENOENT);

	switch (index) {
	case VIRTIO_IVAR_DEVTYPE:
	case VIRTIO_IVAR_SUBDEVICE:
		*result = vtmmio_read_config_4(sc, VIRTIO_MMIO_DEVICE_ID);
		break;
	case VIRTIO_IVAR_VENDOR:
		*result = vtmmio_read_config_4(sc, VIRTIO_MMIO_VENDOR_ID);
		break;
	case VIRTIO_IVAR_SUBVENDOR:
	case VIRTIO_IVAR_DEVICE:
		/*
		 * Dummy value for fields not present in this bus.  Used by
		 * bus-agnostic virtio_child_pnpinfo_str.
		 */
		*result = 0;
		break;
	default:
		return (ENOENT);
	}

	return (0);
}