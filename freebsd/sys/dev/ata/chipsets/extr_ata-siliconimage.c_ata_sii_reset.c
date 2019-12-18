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
typedef  int uint32_t ;
struct ata_pci_controller {int /*<<< orphan*/  r_res2; } ;
struct ata_channel {int unit; scalar_t__ devices; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ATA_INL (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ATA_OUTL (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ata_generic_reset (int /*<<< orphan*/ ) ; 
 scalar_t__ ata_sata_phy_reset (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ata_sii_reset(device_t dev)
{
    struct ata_pci_controller *ctlr = device_get_softc(device_get_parent(dev));
    struct ata_channel *ch = device_get_softc(dev);
    int offset = ((ch->unit & 1) << 7) + ((ch->unit & 2) << 8);
    uint32_t val;

    /* Apply R_ERR on DMA activate FIS errata workaround. */
    val = ATA_INL(ctlr->r_res2, 0x14c + offset);
    if ((val & 0x3) == 0x1)
	ATA_OUTL(ctlr->r_res2, 0x14c + offset, val & ~0x3);

    if (ata_sata_phy_reset(dev, -1, 1))
	ata_generic_reset(dev);
    else
	ch->devices = 0;
}