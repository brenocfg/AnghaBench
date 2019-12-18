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
struct ata_pci_controller {int /*<<< orphan*/  r_res2; TYPE_1__* chip; } ;
struct ata_channel {int unit; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {scalar_t__ max_dma; } ;

/* Variables and functions */
 int ATA_INL (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ATA_SA150 ; 
 int ata_pci_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_sata_phy_check_events (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ata_sii_status(device_t dev)
{
    struct ata_pci_controller *ctlr = device_get_softc(device_get_parent(dev));
    struct ata_channel *ch = device_get_softc(dev);
    int offset0 = ((ch->unit & 1) << 3) + ((ch->unit & 2) << 8);
    int offset1 = ((ch->unit & 1) << 6) + ((ch->unit & 2) << 8);

    /* do we have any PHY events ? */
    if (ctlr->chip->max_dma >= ATA_SA150 &&
	(ATA_INL(ctlr->r_res2, 0x10 + offset0) & 0x00000010))
	ata_sata_phy_check_events(dev, -1);

    if (ATA_INL(ctlr->r_res2, 0xa0 + offset1) & 0x00000800)
	return ata_pci_status(dev);
    else
	return 0;
}