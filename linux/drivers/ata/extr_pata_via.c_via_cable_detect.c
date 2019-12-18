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
typedef  int u32 ;
struct via_isa_bridge {int flags; scalar_t__ udma_mask; } ;
struct pci_dev {int dummy; } ;
struct ata_port {int port_no; TYPE_1__* host; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; struct via_isa_bridge* private_data; } ;

/* Variables and functions */
 int ATA_CBL_PATA40 ; 
 int ATA_CBL_PATA40_SHORT ; 
 int ATA_CBL_PATA80 ; 
 int ATA_CBL_PATA_UNK ; 
 int ATA_CBL_SATA ; 
 scalar_t__ ATA_UDMA4 ; 
 scalar_t__ ATA_UDMA5 ; 
 int VIA_SATA_PATA ; 
 scalar_t__ ata_acpi_cbl_80wire (struct ata_port*,scalar_t__) ; 
 scalar_t__ ata_acpi_init_gtm (struct ata_port*) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int,int*) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 
 scalar_t__ via_cable_override (struct pci_dev*) ; 

__attribute__((used)) static int via_cable_detect(struct ata_port *ap) {
	const struct via_isa_bridge *config = ap->host->private_data;
	struct pci_dev *pdev = to_pci_dev(ap->host->dev);
	u32 ata66;

	if (via_cable_override(pdev))
		return ATA_CBL_PATA40_SHORT;

	if ((config->flags & VIA_SATA_PATA) && ap->port_no == 0)
		return ATA_CBL_SATA;

	/* Early chips are 40 wire */
	if (config->udma_mask < ATA_UDMA4)
		return ATA_CBL_PATA40;
	/* UDMA 66 chips have only drive side logic */
	else if (config->udma_mask < ATA_UDMA5)
		return ATA_CBL_PATA_UNK;
	/* UDMA 100 or later */
	pci_read_config_dword(pdev, 0x50, &ata66);
	/* Check both the drive cable reporting bits, we might not have
	   two drives */
	if (ata66 & (0x10100000 >> (16 * ap->port_no)))
		return ATA_CBL_PATA80;
	/* Check with ACPI so we can spot BIOS reported SATA bridges */
	if (ata_acpi_init_gtm(ap) &&
	    ata_acpi_cbl_80wire(ap, ata_acpi_init_gtm(ap)))
		return ATA_CBL_PATA80;
	return ATA_CBL_PATA40;
}