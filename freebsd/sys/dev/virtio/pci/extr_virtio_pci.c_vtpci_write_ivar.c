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
struct vtpci_softc {scalar_t__ vtpci_child_dev; void* vtpci_child_feat_desc; } ;
typedef  scalar_t__ device_t ;

/* Variables and functions */
 int ENOENT ; 
#define  VIRTIO_IVAR_FEATURE_DESC 128 
 struct vtpci_softc* device_get_softc (scalar_t__) ; 

__attribute__((used)) static int
vtpci_write_ivar(device_t dev, device_t child, int index, uintptr_t value)
{
	struct vtpci_softc *sc;

	sc = device_get_softc(dev);

	if (sc->vtpci_child_dev != child)
		return (ENOENT);

	switch (index) {
	case VIRTIO_IVAR_FEATURE_DESC:
		sc->vtpci_child_feat_desc = (void *) value;
		break;
	default:
		return (ENOENT);
	}

	return (0);
}