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
struct scsi_host_template {int dummy; } ;
struct resource {scalar_t__ flags; int start; } ;
struct device {int dummy; } ;
struct TYPE_3__ {void* ctl_addr; void* altstatus_addr; void* cmd_addr; } ;
struct ata_port {int pio_mask; TYPE_1__ ioaddr; int /*<<< orphan*/  flags; TYPE_2__* ops; } ;
struct ata_host {struct ata_port** ports; } ;
struct TYPE_4__ {int /*<<< orphan*/  sff_data_xfer; int /*<<< orphan*/  set_mode; int /*<<< orphan*/  cable_detect; int /*<<< orphan*/ * inherits; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_FLAG_PIO_POLLING ; 
 int /*<<< orphan*/  ATA_FLAG_SLAVE_POSS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IORESOURCE_MEM ; 
 int IRQF_SHARED ; 
 int IRQF_TRIGGER_MASK ; 
 int /*<<< orphan*/  ata_cable_unknown ; 
 int ata_host_activate (struct ata_host*,int,int /*<<< orphan*/ *,int,struct scsi_host_template*) ; 
 struct ata_host* ata_host_alloc (struct device*,int) ; 
 int /*<<< orphan*/  ata_port_desc (struct ata_port*,char*,...) ; 
 int /*<<< orphan*/  ata_sff_data_xfer ; 
 int /*<<< orphan*/  ata_sff_data_xfer32 ; 
 int /*<<< orphan*/ * ata_sff_interrupt ; 
 int /*<<< orphan*/  ata_sff_port_ops ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 void* devm_ioport_map (struct device*,int,int /*<<< orphan*/ ) ; 
 void* devm_ioremap (struct device*,int,int /*<<< orphan*/ ) ; 
 TYPE_2__* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pata_platform_set_mode ; 
 int /*<<< orphan*/  pata_platform_setup_port (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 

int __pata_platform_probe(struct device *dev, struct resource *io_res,
			  struct resource *ctl_res, struct resource *irq_res,
			  unsigned int ioport_shift, int __pio_mask,
			  struct scsi_host_template *sht, bool use16bit)
{
	struct ata_host *host;
	struct ata_port *ap;
	unsigned int mmio;
	int irq = 0;
	int irq_flags = 0;

	/*
	 * Check for MMIO
	 */
	mmio = (( io_res->flags == IORESOURCE_MEM) &&
		(ctl_res->flags == IORESOURCE_MEM));

	/*
	 * And the IRQ
	 */
	if (irq_res && irq_res->start > 0) {
		irq = irq_res->start;
		irq_flags = (irq_res->flags & IRQF_TRIGGER_MASK) | IRQF_SHARED;
	}

	/*
	 * Now that that's out of the way, wire up the port..
	 */
	host = ata_host_alloc(dev, 1);
	if (!host)
		return -ENOMEM;
	ap = host->ports[0];

	ap->ops = devm_kzalloc(dev, sizeof(*ap->ops), GFP_KERNEL);
	ap->ops->inherits = &ata_sff_port_ops;
	ap->ops->cable_detect = ata_cable_unknown;
	ap->ops->set_mode = pata_platform_set_mode;
	if (use16bit)
		ap->ops->sff_data_xfer = ata_sff_data_xfer;
	else
		ap->ops->sff_data_xfer = ata_sff_data_xfer32;

	ap->pio_mask = __pio_mask;
	ap->flags |= ATA_FLAG_SLAVE_POSS;

	/*
	 * Use polling mode if there's no IRQ
	 */
	if (!irq) {
		ap->flags |= ATA_FLAG_PIO_POLLING;
		ata_port_desc(ap, "no IRQ, using PIO polling");
	}

	/*
	 * Handle the MMIO case
	 */
	if (mmio) {
		ap->ioaddr.cmd_addr = devm_ioremap(dev, io_res->start,
				resource_size(io_res));
		ap->ioaddr.ctl_addr = devm_ioremap(dev, ctl_res->start,
				resource_size(ctl_res));
	} else {
		ap->ioaddr.cmd_addr = devm_ioport_map(dev, io_res->start,
				resource_size(io_res));
		ap->ioaddr.ctl_addr = devm_ioport_map(dev, ctl_res->start,
				resource_size(ctl_res));
	}
	if (!ap->ioaddr.cmd_addr || !ap->ioaddr.ctl_addr) {
		dev_err(dev, "failed to map IO/CTL base\n");
		return -ENOMEM;
	}

	ap->ioaddr.altstatus_addr = ap->ioaddr.ctl_addr;

	pata_platform_setup_port(&ap->ioaddr, ioport_shift);

	ata_port_desc(ap, "%s cmd 0x%llx ctl 0x%llx", mmio ? "mmio" : "ioport",
		      (unsigned long long)io_res->start,
		      (unsigned long long)ctl_res->start);

	/* activate */
	return ata_host_activate(host, irq, irq ? ata_sff_interrupt : NULL,
				 irq_flags, sht);
}