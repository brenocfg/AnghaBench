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
struct TYPE_3__ {int flags; scalar_t__ protocol; } ;
struct ata_queued_cmd {TYPE_2__* dev; TYPE_1__ tf; } ;
struct ata_port {scalar_t__ hsm_task_state; } ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 int ATA_DFLAG_CDB_INTR ; 
 scalar_t__ ATA_PROT_PIO ; 
 int ATA_TFLAG_POLLING ; 
 int ATA_TFLAG_WRITE ; 
 scalar_t__ HSM_ST_FIRST ; 
 scalar_t__ ata_is_atapi (scalar_t__) ; 

__attribute__((used)) static inline int ata_hsm_ok_in_wq(struct ata_port *ap,
						struct ata_queued_cmd *qc)
{
	if (qc->tf.flags & ATA_TFLAG_POLLING)
		return 1;

	if (ap->hsm_task_state == HSM_ST_FIRST) {
		if (qc->tf.protocol == ATA_PROT_PIO &&
		   (qc->tf.flags & ATA_TFLAG_WRITE))
		    return 1;

		if (ata_is_atapi(qc->tf.protocol) &&
		   !(qc->dev->flags & ATA_DFLAG_CDB_INTR))
			return 1;
	}

	return 0;
}