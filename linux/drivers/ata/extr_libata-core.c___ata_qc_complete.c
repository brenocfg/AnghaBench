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
struct TYPE_4__ {int /*<<< orphan*/  protocol; } ;
struct ata_queued_cmd {int flags; int hw_tag; unsigned long long tag; int /*<<< orphan*/  (* complete_fn ) (struct ata_queued_cmd*) ;TYPE_2__ tf; TYPE_1__* dev; struct ata_port* ap; } ;
struct ata_port {unsigned long long qc_active; struct ata_link* excl_link; int /*<<< orphan*/  nr_active_links; } ;
struct ata_link {int sactive; int /*<<< orphan*/  active_tag; } ;
struct TYPE_3__ {struct ata_link* link; } ;

/* Variables and functions */
 int ATA_QCFLAG_ACTIVE ; 
 int ATA_QCFLAG_CLEAR_EXCL ; 
 int ATA_QCFLAG_DMAMAP ; 
 int /*<<< orphan*/  ATA_TAG_POISON ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 scalar_t__ ata_is_ncq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_sg_clean (struct ata_queued_cmd*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  stub1 (struct ata_queued_cmd*) ; 
 scalar_t__ unlikely (int) ; 

void __ata_qc_complete(struct ata_queued_cmd *qc)
{
	struct ata_port *ap;
	struct ata_link *link;

	WARN_ON_ONCE(qc == NULL); /* ata_qc_from_tag _might_ return NULL */
	WARN_ON_ONCE(!(qc->flags & ATA_QCFLAG_ACTIVE));
	ap = qc->ap;
	link = qc->dev->link;

	if (likely(qc->flags & ATA_QCFLAG_DMAMAP))
		ata_sg_clean(qc);

	/* command should be marked inactive atomically with qc completion */
	if (ata_is_ncq(qc->tf.protocol)) {
		link->sactive &= ~(1 << qc->hw_tag);
		if (!link->sactive)
			ap->nr_active_links--;
	} else {
		link->active_tag = ATA_TAG_POISON;
		ap->nr_active_links--;
	}

	/* clear exclusive status */
	if (unlikely(qc->flags & ATA_QCFLAG_CLEAR_EXCL &&
		     ap->excl_link == link))
		ap->excl_link = NULL;

	/* atapi: mark qc as inactive to prevent the interrupt handler
	 * from completing the command twice later, before the error handler
	 * is called. (when rc != 0 and atapi request sense is needed)
	 */
	qc->flags &= ~ATA_QCFLAG_ACTIVE;
	ap->qc_active &= ~(1ULL << qc->tag);

	/* call completion callback */
	qc->complete_fn(qc);
}