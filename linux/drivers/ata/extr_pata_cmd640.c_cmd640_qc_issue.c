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
struct pci_dev {int dummy; } ;
struct cmd640_reg {size_t last; int /*<<< orphan*/ * reg58; } ;
struct ata_queued_cmd {struct ata_device* dev; struct ata_port* ap; } ;
struct ata_port {scalar_t__ port_no; struct cmd640_reg* private_data; TYPE_1__* host; } ;
struct ata_device {size_t devno; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRWTIM23 ; 
 unsigned int ata_sff_qc_issue (struct ata_queued_cmd*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int cmd640_qc_issue(struct ata_queued_cmd *qc)
{
	struct ata_port *ap = qc->ap;
	struct ata_device *adev = qc->dev;
	struct pci_dev *pdev = to_pci_dev(ap->host->dev);
	struct cmd640_reg *timing = ap->private_data;

	if (ap->port_no != 0 && adev->devno != timing->last) {
		pci_write_config_byte(pdev, DRWTIM23, timing->reg58[adev->devno]);
		timing->last = adev->devno;
	}
	return ata_sff_qc_issue(qc);
}