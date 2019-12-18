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
typedef  int u8 ;
struct pci_dev {int dummy; } ;
struct ata_port {scalar_t__ port_no; TYPE_1__* host; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ARTIM23 ; 
 int CFR ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int,int*) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool cmd640_sff_irq_check(struct ata_port *ap)
{
	struct pci_dev *pdev	= to_pci_dev(ap->host->dev);
	int irq_reg		= ap->port_no ? ARTIM23 : CFR;
	u8  irq_stat, irq_mask	= ap->port_no ? 0x10 : 0x04;

	pci_read_config_byte(pdev, irq_reg, &irq_stat);

	return irq_stat & irq_mask;
}