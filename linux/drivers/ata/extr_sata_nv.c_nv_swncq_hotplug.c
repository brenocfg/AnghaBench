#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct ata_eh_info {int serror; } ;
struct TYPE_3__ {struct ata_eh_info eh_info; } ;
struct ata_port {TYPE_1__ link; } ;

/* Variables and functions */
 int NV_SWNCQ_IRQ_ADDED ; 
 int NV_SWNCQ_IRQ_REMOVED ; 
 int /*<<< orphan*/  SCR_ERROR ; 
 int /*<<< orphan*/  ata_ehi_clear_desc (struct ata_eh_info*) ; 
 int /*<<< orphan*/  ata_ehi_hotplugged (struct ata_eh_info*) ; 
 int /*<<< orphan*/  ata_ehi_push_desc (struct ata_eh_info*,char*) ; 
 int /*<<< orphan*/  ata_port_freeze (struct ata_port*) ; 
 int /*<<< orphan*/  sata_scr_read (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  sata_scr_write (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void nv_swncq_hotplug(struct ata_port *ap, u32 fis)
{
	u32 serror;
	struct ata_eh_info *ehi = &ap->link.eh_info;

	ata_ehi_clear_desc(ehi);

	/* AHCI needs SError cleared; otherwise, it might lock up */
	sata_scr_read(&ap->link, SCR_ERROR, &serror);
	sata_scr_write(&ap->link, SCR_ERROR, serror);

	/* analyze @irq_stat */
	if (fis & NV_SWNCQ_IRQ_ADDED)
		ata_ehi_push_desc(ehi, "hot plug");
	else if (fis & NV_SWNCQ_IRQ_REMOVED)
		ata_ehi_push_desc(ehi, "hot unplug");

	ata_ehi_hotplugged(ehi);

	/* okay, let's hand over to EH */
	ehi->serror |= serror;

	ata_port_freeze(ap);
}