#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_6__ {int /*<<< orphan*/  protocol; } ;
struct ata_queued_cmd {int /*<<< orphan*/  err_mask; TYPE_1__* dev; TYPE_3__ tf; } ;
struct ata_port {int hsm_task_state; TYPE_2__* ops; int /*<<< orphan*/  print_id; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* sff_irq_clear ) (struct ata_port*) ;} ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_ERR_HSM ; 
 int ATA_BUSY ; 
 int ATA_DFLAG_CDB_INTR ; 
 int HSM_ST_ERR ; 
#define  HSM_ST_FIRST 129 
#define  HSM_ST_IDLE 128 
 int /*<<< orphan*/  VPRINTK (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ata_sff_hsm_move (struct ata_port*,struct ata_queued_cmd*,int,int /*<<< orphan*/ ) ; 
 unsigned int ata_sff_idle_irq (struct ata_port*) ; 
 int ata_sff_irq_status (struct ata_port*) ; 
 int /*<<< orphan*/  stub1 (struct ata_port*) ; 

__attribute__((used)) static unsigned int __ata_sff_port_intr(struct ata_port *ap,
					struct ata_queued_cmd *qc,
					bool hsmv_on_idle)
{
	u8 status;

	VPRINTK("ata%u: protocol %d task_state %d\n",
		ap->print_id, qc->tf.protocol, ap->hsm_task_state);

	/* Check whether we are expecting interrupt in this state */
	switch (ap->hsm_task_state) {
	case HSM_ST_FIRST:
		/* Some pre-ATAPI-4 devices assert INTRQ
		 * at this state when ready to receive CDB.
		 */

		/* Check the ATA_DFLAG_CDB_INTR flag is enough here.
		 * The flag was turned on only for atapi devices.  No
		 * need to check ata_is_atapi(qc->tf.protocol) again.
		 */
		if (!(qc->dev->flags & ATA_DFLAG_CDB_INTR))
			return ata_sff_idle_irq(ap);
		break;
	case HSM_ST_IDLE:
		return ata_sff_idle_irq(ap);
	default:
		break;
	}

	/* check main status, clearing INTRQ if needed */
	status = ata_sff_irq_status(ap);
	if (status & ATA_BUSY) {
		if (hsmv_on_idle) {
			/* BMDMA engine is already stopped, we're screwed */
			qc->err_mask |= AC_ERR_HSM;
			ap->hsm_task_state = HSM_ST_ERR;
		} else
			return ata_sff_idle_irq(ap);
	}

	/* clear irq events */
	if (ap->ops->sff_irq_clear)
		ap->ops->sff_irq_clear(ap);

	ata_sff_hsm_move(ap, qc, status, 0);

	return 1;	/* irq handled */
}