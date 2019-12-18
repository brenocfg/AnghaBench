#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct scsi_device {size_t id; int /*<<< orphan*/  queue_depth; scalar_t__ lun; scalar_t__ channel; int /*<<< orphan*/  host; } ;
struct pci_dev {scalar_t__ device; } ;
struct TYPE_4__ {struct ata_device* device; } ;
struct ata_port {int flags; TYPE_2__ link; TYPE_1__* host; } ;
struct ata_device {scalar_t__ class; int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  model_num ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ ATA_DEV_ATAPI ; 
 int ATA_FLAG_NCQ ; 
 int /*<<< orphan*/  ATA_ID_PROD ; 
 int /*<<< orphan*/  ATA_ID_PROD_LEN ; 
 size_t ATA_MAX_DEVICES ; 
 scalar_t__ PCI_DEVICE_ID_NVIDIA_NFORCE_MCP51_SATA ; 
 scalar_t__ PCI_DEVICE_ID_NVIDIA_NFORCE_MCP51_SATA2 ; 
 scalar_t__ PCI_DEVICE_ID_NVIDIA_NFORCE_MCP55_SATA ; 
 scalar_t__ PCI_DEVICE_ID_NVIDIA_NFORCE_MCP55_SATA2 ; 
 int /*<<< orphan*/  ata_dev_notice (struct ata_device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_id_c_string (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ata_scsi_change_queue_depth (struct scsi_device*,int) ; 
 int ata_scsi_slave_config (struct scsi_device*) ; 
 struct ata_port* ata_shost_to_port (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int,int*) ; 
 scalar_t__ strncmp (unsigned char*,char*,int) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nv_swncq_slave_config(struct scsi_device *sdev)
{
	struct ata_port *ap = ata_shost_to_port(sdev->host);
	struct pci_dev *pdev = to_pci_dev(ap->host->dev);
	struct ata_device *dev;
	int rc;
	u8 rev;
	u8 check_maxtor = 0;
	unsigned char model_num[ATA_ID_PROD_LEN + 1];

	rc = ata_scsi_slave_config(sdev);
	if (sdev->id >= ATA_MAX_DEVICES || sdev->channel || sdev->lun)
		/* Not a proper libata device, ignore */
		return rc;

	dev = &ap->link.device[sdev->id];
	if (!(ap->flags & ATA_FLAG_NCQ) || dev->class == ATA_DEV_ATAPI)
		return rc;

	/* if MCP51 and Maxtor, then disable ncq */
	if (pdev->device == PCI_DEVICE_ID_NVIDIA_NFORCE_MCP51_SATA ||
		pdev->device == PCI_DEVICE_ID_NVIDIA_NFORCE_MCP51_SATA2)
		check_maxtor = 1;

	/* if MCP55 and rev <= a2 and Maxtor, then disable ncq */
	if (pdev->device == PCI_DEVICE_ID_NVIDIA_NFORCE_MCP55_SATA ||
		pdev->device == PCI_DEVICE_ID_NVIDIA_NFORCE_MCP55_SATA2) {
		pci_read_config_byte(pdev, 0x8, &rev);
		if (rev <= 0xa2)
			check_maxtor = 1;
	}

	if (!check_maxtor)
		return rc;

	ata_id_c_string(dev->id, model_num, ATA_ID_PROD, sizeof(model_num));

	if (strncmp(model_num, "Maxtor", 6) == 0) {
		ata_scsi_change_queue_depth(sdev, 1);
		ata_dev_notice(dev, "Disabling SWNCQ mode (depth %x)\n",
			       sdev->queue_depth);
	}

	return rc;
}