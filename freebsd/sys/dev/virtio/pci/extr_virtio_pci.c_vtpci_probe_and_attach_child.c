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
struct vtpci_softc {int /*<<< orphan*/ * vtpci_child_dev; int /*<<< orphan*/ * vtpci_dev; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 scalar_t__ DS_NOTPRESENT ; 
 int /*<<< orphan*/  VIRTIO_ATTACH_COMPLETED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VIRTIO_CONFIG_STATUS_ACK ; 
 int /*<<< orphan*/  VIRTIO_CONFIG_STATUS_DRIVER ; 
 int /*<<< orphan*/  VIRTIO_CONFIG_STATUS_DRIVER_OK ; 
 int /*<<< orphan*/  VIRTIO_CONFIG_STATUS_FAILED ; 
 scalar_t__ device_attach (int /*<<< orphan*/ *) ; 
 scalar_t__ device_get_state (int /*<<< orphan*/ *) ; 
 scalar_t__ device_probe (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vtpci_release_child_resources (struct vtpci_softc*) ; 
 int /*<<< orphan*/  vtpci_reset (struct vtpci_softc*) ; 
 int /*<<< orphan*/  vtpci_set_status (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vtpci_probe_and_attach_child(struct vtpci_softc *sc)
{
	device_t dev, child;

	dev = sc->vtpci_dev;
	child = sc->vtpci_child_dev;

	if (child == NULL)
		return;

	if (device_get_state(child) != DS_NOTPRESENT)
		return;

	if (device_probe(child) != 0)
		return;

	vtpci_set_status(dev, VIRTIO_CONFIG_STATUS_DRIVER);
	if (device_attach(child) != 0) {
		vtpci_set_status(dev, VIRTIO_CONFIG_STATUS_FAILED);
		vtpci_reset(sc);
		vtpci_release_child_resources(sc);
		/* Reset status for future attempt. */
		vtpci_set_status(dev, VIRTIO_CONFIG_STATUS_ACK);
	} else {
		vtpci_set_status(dev, VIRTIO_CONFIG_STATUS_DRIVER_OK);
		VIRTIO_ATTACH_COMPLETED(child);
	}
}