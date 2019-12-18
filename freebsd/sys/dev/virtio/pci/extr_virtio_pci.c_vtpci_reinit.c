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
typedef  int /*<<< orphan*/  uint64_t ;
struct vtpci_softc {int vtpci_nvqs; int vtpci_flags; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  VIRTIO_CONFIG_STATUS_ACK ; 
 int /*<<< orphan*/  VIRTIO_CONFIG_STATUS_DRIVER ; 
 scalar_t__ VIRTIO_CONFIG_STATUS_RESET ; 
 int VTPCI_FLAG_MSIX ; 
 struct vtpci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ vtpci_get_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtpci_negotiate_features (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vtpci_reinit_virtqueue (struct vtpci_softc*,int) ; 
 int vtpci_set_host_msix_vectors (struct vtpci_softc*) ; 
 int /*<<< orphan*/  vtpci_set_status (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtpci_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vtpci_reinit(device_t dev, uint64_t features)
{
	struct vtpci_softc *sc;
	int idx, error;

	sc = device_get_softc(dev);

	/*
	 * Redrive the device initialization. This is a bit of an abuse of
	 * the specification, but VirtualBox, QEMU/KVM, and BHyVe seem to
	 * play nice.
	 *
	 * We do not allow the host device to change from what was originally
	 * negotiated beyond what the guest driver changed. MSIX state should
	 * not change, number of virtqueues and their size remain the same, etc.
	 * This will need to be rethought when we want to support migration.
	 */

	if (vtpci_get_status(dev) != VIRTIO_CONFIG_STATUS_RESET)
		vtpci_stop(dev);

	/*
	 * Quickly drive the status through ACK and DRIVER. The device
	 * does not become usable again until vtpci_reinit_complete().
	 */
	vtpci_set_status(dev, VIRTIO_CONFIG_STATUS_ACK);
	vtpci_set_status(dev, VIRTIO_CONFIG_STATUS_DRIVER);

	vtpci_negotiate_features(dev, features);

	for (idx = 0; idx < sc->vtpci_nvqs; idx++) {
		error = vtpci_reinit_virtqueue(sc, idx);
		if (error)
			return (error);
	}

	if (sc->vtpci_flags & VTPCI_FLAG_MSIX) {
		error = vtpci_set_host_msix_vectors(sc);
		if (error)
			return (error);
	}

	return (0);
}