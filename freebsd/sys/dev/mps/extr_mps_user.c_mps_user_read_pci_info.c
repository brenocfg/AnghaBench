#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mps_softc {int /*<<< orphan*/  mps_dev; } ;
struct TYPE_3__ {int /*<<< orphan*/ * PciHeader; scalar_t__ InterruptVector; int /*<<< orphan*/  FunctionNumber; int /*<<< orphan*/  DeviceNumber; int /*<<< orphan*/  BusNumber; } ;
typedef  TYPE_1__ mps_pci_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  pci_get_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_function (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_slot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
mps_user_read_pci_info(struct mps_softc *sc, mps_pci_info_t *data)
{
	int	i;

	/*
	 * Use the PCI interface functions to get the Bus, Device, and Function
	 * information.
	 */
	data->BusNumber = pci_get_bus(sc->mps_dev);
	data->DeviceNumber = pci_get_slot(sc->mps_dev);
	data->FunctionNumber = pci_get_function(sc->mps_dev);

	/*
	 * Now get the interrupt vector and the pci header.  The vector can
	 * only be 0 right now.  The header is the first 256 bytes of config
	 * space.
	 */
	data->InterruptVector = 0;
	for (i = 0; i < sizeof (data->PciHeader); i++) {
		data->PciHeader[i] = pci_read_config(sc->mps_dev, i, 1);
	}
}