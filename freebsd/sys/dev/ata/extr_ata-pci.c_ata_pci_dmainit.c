#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  reset; int /*<<< orphan*/  stop; int /*<<< orphan*/  start; } ;
struct ata_channel {TYPE_1__ dma; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ata_dmainit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_pci_dmareset ; 
 int /*<<< orphan*/  ata_pci_dmastart ; 
 int /*<<< orphan*/  ata_pci_dmastop ; 
 struct ata_channel* device_get_softc (int /*<<< orphan*/ ) ; 

void
ata_pci_dmainit(device_t dev)
{
    struct ata_channel *ch = device_get_softc(dev);

    ata_dmainit(dev);
    ch->dma.start = ata_pci_dmastart;
    ch->dma.stop = ata_pci_dmastop;
    ch->dma.reset = ata_pci_dmareset;
}