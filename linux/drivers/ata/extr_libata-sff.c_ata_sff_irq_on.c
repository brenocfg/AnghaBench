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
struct ata_ioports {scalar_t__ ctl_addr; } ;
struct ata_port {TYPE_1__* ops; int /*<<< orphan*/  ctl; int /*<<< orphan*/  last_ctl; struct ata_ioports ioaddr; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* sff_irq_clear ) (struct ata_port*) ;scalar_t__ sff_set_devctl; int /*<<< orphan*/  (* sff_irq_on ) (struct ata_port*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_NIEN ; 
 int /*<<< orphan*/  ata_sff_set_devctl (struct ata_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_wait_idle (struct ata_port*) ; 
 int /*<<< orphan*/  stub1 (struct ata_port*) ; 
 int /*<<< orphan*/  stub2 (struct ata_port*) ; 

void ata_sff_irq_on(struct ata_port *ap)
{
	struct ata_ioports *ioaddr = &ap->ioaddr;

	if (ap->ops->sff_irq_on) {
		ap->ops->sff_irq_on(ap);
		return;
	}

	ap->ctl &= ~ATA_NIEN;
	ap->last_ctl = ap->ctl;

	if (ap->ops->sff_set_devctl || ioaddr->ctl_addr)
		ata_sff_set_devctl(ap, ap->ctl);
	ata_wait_idle(ap);

	if (ap->ops->sff_irq_clear)
		ap->ops->sff_irq_clear(ap);
}