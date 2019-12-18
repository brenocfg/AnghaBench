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
struct ata_queued_cmd {int tag; int hw_tag; struct ata_device* dev; struct ata_port* ap; int /*<<< orphan*/ * scsicmd; } ;
struct ata_port {int pflags; int flags; } ;
struct ata_device {TYPE_1__* link; } ;
struct TYPE_2__ {struct ata_port* ap; } ;

/* Variables and functions */
 int ATA_FLAG_SAS_HOST ; 
 int ATA_PFLAG_FROZEN ; 
 struct ata_queued_cmd* __ata_qc_from_tag (struct ata_port*,int) ; 
 int /*<<< orphan*/  ata_qc_reinit (struct ata_queued_cmd*) ; 
 int ata_sas_allocate_tag (struct ata_port*) ; 
 scalar_t__ unlikely (int) ; 

struct ata_queued_cmd *ata_qc_new_init(struct ata_device *dev, int tag)
{
	struct ata_port *ap = dev->link->ap;
	struct ata_queued_cmd *qc;

	/* no command while frozen */
	if (unlikely(ap->pflags & ATA_PFLAG_FROZEN))
		return NULL;

	/* libsas case */
	if (ap->flags & ATA_FLAG_SAS_HOST) {
		tag = ata_sas_allocate_tag(ap);
		if (tag < 0)
			return NULL;
	}

	qc = __ata_qc_from_tag(ap, tag);
	qc->tag = qc->hw_tag = tag;
	qc->scsicmd = NULL;
	qc->ap = ap;
	qc->dev = dev;

	ata_qc_reinit(qc);

	return qc;
}