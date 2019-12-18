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
struct ata_pci_controller {scalar_t__ channels; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct ata_pci_controller* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ata_marvell_dummy_chipinit(device_t dev)
{
	struct ata_pci_controller *ctlr = device_get_softc(dev);

        ctlr->channels = 0;
        return (0);
}