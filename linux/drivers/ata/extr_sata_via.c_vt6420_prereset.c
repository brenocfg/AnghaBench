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
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  action; } ;
struct ata_eh_context {TYPE_2__ i; } ;
struct TYPE_3__ {struct ata_eh_context eh_context; } ;
struct ata_port {int pflags; TYPE_1__ link; } ;
struct ata_link {struct ata_port* ap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_EH_RESET ; 
 int ATA_PFLAG_LOADING ; 
 int HZ ; 
 int /*<<< orphan*/  SCR_CONTROL ; 
 int /*<<< orphan*/  SCR_STATUS ; 
 int /*<<< orphan*/  ata_msleep (struct ata_port*,int) ; 
 int /*<<< orphan*/  ata_port_info (struct ata_port*,char*,char*,int,int) ; 
 int /*<<< orphan*/  ata_sff_wait_ready (struct ata_link*,unsigned long) ; 
 int jiffies ; 
 int /*<<< orphan*/  svia_scr_read (struct ata_link*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  svia_scr_write (struct ata_link*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ time_before (int,unsigned long) ; 

__attribute__((used)) static int vt6420_prereset(struct ata_link *link, unsigned long deadline)
{
	struct ata_port *ap = link->ap;
	struct ata_eh_context *ehc = &ap->link.eh_context;
	unsigned long timeout = jiffies + (HZ * 5);
	u32 sstatus, scontrol;
	int online;

	/* don't do any SCR stuff if we're not loading */
	if (!(ap->pflags & ATA_PFLAG_LOADING))
		goto skip_scr;

	/* Resume phy.  This is the old SATA resume sequence */
	svia_scr_write(link, SCR_CONTROL, 0x300);
	svia_scr_read(link, SCR_CONTROL, &scontrol); /* flush */

	/* wait for phy to become ready, if necessary */
	do {
		ata_msleep(link->ap, 200);
		svia_scr_read(link, SCR_STATUS, &sstatus);
		if ((sstatus & 0xf) != 1)
			break;
	} while (time_before(jiffies, timeout));

	/* open code sata_print_link_status() */
	svia_scr_read(link, SCR_STATUS, &sstatus);
	svia_scr_read(link, SCR_CONTROL, &scontrol);

	online = (sstatus & 0xf) == 0x3;

	ata_port_info(ap,
		      "SATA link %s 1.5 Gbps (SStatus %X SControl %X)\n",
		      online ? "up" : "down", sstatus, scontrol);

	/* SStatus is read one more time */
	svia_scr_read(link, SCR_STATUS, &sstatus);

	if (!online) {
		/* tell EH to bail */
		ehc->i.action &= ~ATA_EH_RESET;
		return 0;
	}

 skip_scr:
	/* wait for !BSY */
	ata_sff_wait_ready(link, deadline);

	return 0;
}