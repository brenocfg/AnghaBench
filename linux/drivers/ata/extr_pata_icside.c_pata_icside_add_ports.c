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
struct pata_icside_info {int nr_ports; int /*<<< orphan*/ * port; int /*<<< orphan*/  base; int /*<<< orphan*/  mwdma_mask; int /*<<< orphan*/  state; int /*<<< orphan*/  irqops; int /*<<< orphan*/  irqmask; scalar_t__ irqaddr; struct expansion_card* ec; } ;
struct expansion_card {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; TYPE_1__* ops; int /*<<< orphan*/  irqmask; scalar_t__ irqaddr; } ;
struct ata_port {int /*<<< orphan*/ * ops; int /*<<< orphan*/  flags; int /*<<< orphan*/  mwdma_mask; int /*<<< orphan*/  pio_mask; } ;
struct ata_host {struct ata_port** ports; int /*<<< orphan*/  flags; int /*<<< orphan*/  private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* irqdisable ) (struct expansion_card*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_FLAG_SLAVE_POSS ; 
 int /*<<< orphan*/  ATA_HOST_SIMPLEX ; 
 int /*<<< orphan*/  ATA_PIO4 ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ata_bmdma_interrupt ; 
 int ata_host_activate (struct ata_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ata_host* ata_host_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ecard_setirq (struct expansion_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pata_icside_port_ops ; 
 int /*<<< orphan*/  pata_icside_setup_ioaddr (struct ata_port*,int /*<<< orphan*/ ,struct pata_icside_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pata_icside_sht ; 
 int /*<<< orphan*/  stub1 (struct expansion_card*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pata_icside_add_ports(struct pata_icside_info *info)
{
	struct expansion_card *ec = info->ec;
	struct ata_host *host;
	int i;

	if (info->irqaddr) {
		ec->irqaddr = info->irqaddr;
		ec->irqmask = info->irqmask;
	}
	if (info->irqops)
		ecard_setirq(ec, info->irqops, info->state);

	/*
	 * Be on the safe side - disable interrupts
	 */
	ec->ops->irqdisable(ec, ec->irq);

	host = ata_host_alloc(&ec->dev, info->nr_ports);
	if (!host)
		return -ENOMEM;

	host->private_data = info->state;
	host->flags = ATA_HOST_SIMPLEX;

	for (i = 0; i < info->nr_ports; i++) {
		struct ata_port *ap = host->ports[i];

		ap->pio_mask = ATA_PIO4;
		ap->mwdma_mask = info->mwdma_mask;
		ap->flags |= ATA_FLAG_SLAVE_POSS;
		ap->ops = &pata_icside_port_ops;

		pata_icside_setup_ioaddr(ap, info->base, info, info->port[i]);
	}

	return ata_host_activate(host, ec->irq, ata_bmdma_interrupt, 0,
				 &pata_icside_sht);
}