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
struct vtpci_softc {scalar_t__ vtpci_child_dev; } ;
typedef  scalar_t__ device_t ;

/* Variables and functions */
 int ENOENT ; 
#define  VIRTIO_IVAR_DEVICE 132 
#define  VIRTIO_IVAR_DEVTYPE 131 
#define  VIRTIO_IVAR_SUBDEVICE 130 
#define  VIRTIO_IVAR_SUBVENDOR 129 
#define  VIRTIO_IVAR_VENDOR 128 
 struct vtpci_softc* device_get_softc (scalar_t__) ; 
 uintptr_t pci_get_device (scalar_t__) ; 
 uintptr_t pci_get_subdevice (scalar_t__) ; 
 uintptr_t pci_get_subvendor (scalar_t__) ; 
 uintptr_t pci_get_vendor (scalar_t__) ; 

__attribute__((used)) static int
vtpci_read_ivar(device_t dev, device_t child, int index, uintptr_t *result)
{
	struct vtpci_softc *sc;

	sc = device_get_softc(dev);

	if (sc->vtpci_child_dev != child)
		return (ENOENT);

	switch (index) {
	case VIRTIO_IVAR_DEVTYPE:
	case VIRTIO_IVAR_SUBDEVICE:
		*result = pci_get_subdevice(dev);
		break;
	case VIRTIO_IVAR_VENDOR:
		*result = pci_get_vendor(dev);
		break;
	case VIRTIO_IVAR_DEVICE:
		*result = pci_get_device(dev);
		break;
	case VIRTIO_IVAR_SUBVENDOR:
		*result = pci_get_subvendor(dev);
		break;
	default:
		return (ENOENT);
	}

	return (0);
}