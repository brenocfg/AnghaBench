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
struct TYPE_4__ {int flags; } ;
struct ata_queued_cmd {TYPE_2__ tf; } ;
struct TYPE_3__ {int /*<<< orphan*/  active_tag; } ;
struct ata_port {TYPE_1__ link; } ;

/* Variables and functions */
 int ATA_TFLAG_POLLING ; 
 int NV_INT_ADDED ; 
 int NV_INT_DEV ; 
 int NV_INT_REMOVED ; 
 int ata_bmdma_port_intr (struct ata_port*,struct ata_queued_cmd*) ; 
 int /*<<< orphan*/  ata_port_freeze (struct ata_port*) ; 
 struct ata_queued_cmd* ata_qc_from_tag (struct ata_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_sff_check_status (struct ata_port*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int nv_host_intr(struct ata_port *ap, u8 irq_stat)
{
	struct ata_queued_cmd *qc = ata_qc_from_tag(ap, ap->link.active_tag);

	/* freeze if hotplugged */
	if (unlikely(irq_stat & (NV_INT_ADDED | NV_INT_REMOVED))) {
		ata_port_freeze(ap);
		return 1;
	}

	/* bail out if not our interrupt */
	if (!(irq_stat & NV_INT_DEV))
		return 0;

	/* DEV interrupt w/ no active qc? */
	if (unlikely(!qc || (qc->tf.flags & ATA_TFLAG_POLLING))) {
		ata_sff_check_status(ap);
		return 1;
	}

	/* handle interrupt */
	return ata_bmdma_port_intr(ap, qc);
}