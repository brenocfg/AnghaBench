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
struct TYPE_4__ {scalar_t__ altstatus_addr; } ;
struct ata_port {TYPE_2__ ioaddr; TYPE_1__* ops; } ;
struct TYPE_3__ {scalar_t__ sff_check_altstatus; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  ata_sff_altstatus (struct ata_port*) ; 

void ata_sff_dma_pause(struct ata_port *ap)
{
	if (ap->ops->sff_check_altstatus || ap->ioaddr.altstatus_addr) {
		/* An altstatus read will cause the needed delay without
		   messing up the IRQ status */
		ata_sff_altstatus(ap);
		return;
	}
	/* There are no DMA controllers without ctl. BUG here to ensure
	   we never violate the HDMA1:0 transition timing and risk
	   corruption. */
	BUG();
}