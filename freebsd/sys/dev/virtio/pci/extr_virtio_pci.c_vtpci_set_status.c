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
typedef  int /*<<< orphan*/  uint8_t ;
struct vtpci_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  VIRTIO_CONFIG_STATUS_RESET ; 
 int /*<<< orphan*/  VIRTIO_PCI_STATUS ; 
 struct vtpci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtpci_get_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtpci_write_config_1 (struct vtpci_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vtpci_set_status(device_t dev, uint8_t status)
{
	struct vtpci_softc *sc;

	sc = device_get_softc(dev);

	if (status != VIRTIO_CONFIG_STATUS_RESET)
		status |= vtpci_get_status(dev);

	vtpci_write_config_1(sc, VIRTIO_PCI_STATUS, status);
}