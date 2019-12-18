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
struct ata_ioports {int /*<<< orphan*/  ctl_addr; } ;
struct ata_port {int ctl; int last_ctl; int /*<<< orphan*/  link; int /*<<< orphan*/  print_id; struct ata_ioports ioaddr; } ;

/* Variables and functions */
 int ATA_SRST ; 
 int /*<<< orphan*/  DPRINTK (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite32 (int,int /*<<< orphan*/ ) ; 
 int sata_rcar_wait_after_reset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int sata_rcar_bus_softreset(struct ata_port *ap, unsigned long deadline)
{
	struct ata_ioports *ioaddr = &ap->ioaddr;

	DPRINTK("ata%u: bus reset via SRST\n", ap->print_id);

	/* software reset.  causes dev0 to be selected */
	iowrite32(ap->ctl, ioaddr->ctl_addr);
	udelay(20);
	iowrite32(ap->ctl | ATA_SRST, ioaddr->ctl_addr);
	udelay(20);
	iowrite32(ap->ctl, ioaddr->ctl_addr);
	ap->last_ctl = ap->ctl;

	/* wait the port to become ready */
	return sata_rcar_wait_after_reset(&ap->link, deadline);
}