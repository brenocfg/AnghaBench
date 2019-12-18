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
 int /*<<< orphan*/  VIRTIO_PCI_STATUS ; 
 struct vtpci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtpci_read_config_1 (struct vtpci_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint8_t
vtpci_get_status(device_t dev)
{
	struct vtpci_softc *sc;

	sc = device_get_softc(dev);

	return (vtpci_read_config_1(sc, VIRTIO_PCI_STATUS));
}