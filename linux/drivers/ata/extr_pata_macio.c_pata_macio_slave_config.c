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
typedef  int u16 ;
struct scsi_device {size_t id; int /*<<< orphan*/  request_queue; int /*<<< orphan*/  host; } ;
struct pata_macio_priv {scalar_t__ kind; int /*<<< orphan*/  pdev; } ;
struct TYPE_2__ {struct ata_device* device; } ;
struct ata_port {TYPE_1__ link; struct pata_macio_priv* private_data; } ;
struct ata_device {scalar_t__ class; } ;

/* Variables and functions */
 scalar_t__ ATA_DEV_ATAPI ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  PCI_CACHE_LINE_SIZE ; 
 int /*<<< orphan*/  PCI_COMMAND ; 
 int PCI_COMMAND_INVALIDATE ; 
 int /*<<< orphan*/  ata_dev_info (struct ata_device*,char*) ; 
 int ata_scsi_slave_config (struct scsi_device*) ; 
 struct ata_port* ata_shost_to_port (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_update_dma_alignment (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  blk_queue_update_dma_pad (int /*<<< orphan*/ ,int) ; 
 scalar_t__ controller_k2_ata6 ; 
 scalar_t__ controller_ohare ; 
 scalar_t__ controller_sh_ata6 ; 
 int /*<<< orphan*/  pci_read_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pata_macio_slave_config(struct scsi_device *sdev)
{
	struct ata_port *ap = ata_shost_to_port(sdev->host);
	struct pata_macio_priv *priv = ap->private_data;
	struct ata_device *dev;
	u16 cmd;
	int rc;

	/* First call original */
	rc = ata_scsi_slave_config(sdev);
	if (rc)
		return rc;

	/* This is lifted from sata_nv */
	dev = &ap->link.device[sdev->id];

	/* OHare has issues with non cache aligned DMA on some chipsets */
	if (priv->kind == controller_ohare) {
		blk_queue_update_dma_alignment(sdev->request_queue, 31);
		blk_queue_update_dma_pad(sdev->request_queue, 31);

		/* Tell the world about it */
		ata_dev_info(dev, "OHare alignment limits applied\n");
		return 0;
	}

	/* We only have issues with ATAPI */
	if (dev->class != ATA_DEV_ATAPI)
		return 0;

	/* Shasta and K2 seem to have "issues" with reads ... */
	if (priv->kind == controller_sh_ata6 || priv->kind == controller_k2_ata6) {
		/* Allright these are bad, apply restrictions */
		blk_queue_update_dma_alignment(sdev->request_queue, 15);
		blk_queue_update_dma_pad(sdev->request_queue, 15);

		/* We enable MWI and hack cache line size directly here, this
		 * is specific to this chipset and not normal values, we happen
		 * to somewhat know what we are doing here (which is basically
		 * to do the same Apple does and pray they did not get it wrong :-)
		 */
		BUG_ON(!priv->pdev);
		pci_write_config_byte(priv->pdev, PCI_CACHE_LINE_SIZE, 0x08);
		pci_read_config_word(priv->pdev, PCI_COMMAND, &cmd);
		pci_write_config_word(priv->pdev, PCI_COMMAND,
				      cmd | PCI_COMMAND_INVALIDATE);

		/* Tell the world about it */
		ata_dev_info(dev, "K2/Shasta alignment limits applied\n");
	}

	return 0;
}