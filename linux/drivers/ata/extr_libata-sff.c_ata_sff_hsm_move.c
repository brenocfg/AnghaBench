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
struct TYPE_3__ {int flags; int /*<<< orphan*/  protocol; } ;
struct ata_queued_cmd {int flags; int err_mask; TYPE_2__* dev; TYPE_1__ tf; } ;
struct ata_port {int hsm_task_state; int /*<<< orphan*/  print_id; int /*<<< orphan*/  lock; } ;
struct ata_eh_info {int dummy; } ;
struct ata_link {struct ata_eh_info eh_info; } ;
struct TYPE_4__ {int horkage; int /*<<< orphan*/  devno; struct ata_link* link; } ;

/* Variables and functions */
 int AC_ERR_DEV ; 
 int AC_ERR_HSM ; 
 int AC_ERR_NODEV_HINT ; 
 int /*<<< orphan*/  ATAPI_PROT_PIO ; 
 int ATA_BUSY ; 
 int ATA_DF ; 
 int ATA_DRQ ; 
 int ATA_ERR ; 
 int ATA_HORKAGE_DIAGNOSTIC ; 
 int ATA_HORKAGE_STUCK_ERR ; 
 int /*<<< orphan*/  ATA_PROT_PIO ; 
 int ATA_QCFLAG_ACTIVE ; 
 int ATA_TFLAG_POLLING ; 
 int ATA_TFLAG_WRITE ; 
 int /*<<< orphan*/  DPRINTK (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,...) ; 
#define  HSM_ST 131 
#define  HSM_ST_ERR 130 
#define  HSM_ST_FIRST 129 
 void* HSM_ST_IDLE ; 
#define  HSM_ST_LAST 128 
 int /*<<< orphan*/  WARN (int,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int __ac_err_mask (int) ; 
 int /*<<< orphan*/  ata_ehi_push_desc (struct ata_eh_info*,char*,...) ; 
 int ata_hsm_ok_in_wq (struct ata_port*,struct ata_queued_cmd*) ; 
 int /*<<< orphan*/  ata_hsm_qc_complete (struct ata_queued_cmd*,int) ; 
 int /*<<< orphan*/  ata_ok (int) ; 
 int /*<<< orphan*/  ata_pio_sectors (struct ata_queued_cmd*) ; 
 int ata_wait_idle (struct ata_port*) ; 
 int /*<<< orphan*/  atapi_pio_bytes (struct ata_queued_cmd*) ; 
 int /*<<< orphan*/  atapi_send_cdb (struct ata_port*,struct ata_queued_cmd*) ; 
 int /*<<< orphan*/  likely (int) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlikely (int) ; 

int ata_sff_hsm_move(struct ata_port *ap, struct ata_queued_cmd *qc,
		     u8 status, int in_wq)
{
	struct ata_link *link = qc->dev->link;
	struct ata_eh_info *ehi = &link->eh_info;
	int poll_next;

	lockdep_assert_held(ap->lock);

	WARN_ON_ONCE((qc->flags & ATA_QCFLAG_ACTIVE) == 0);

	/* Make sure ata_sff_qc_issue() does not throw things
	 * like DMA polling into the workqueue. Notice that
	 * in_wq is not equivalent to (qc->tf.flags & ATA_TFLAG_POLLING).
	 */
	WARN_ON_ONCE(in_wq != ata_hsm_ok_in_wq(ap, qc));

fsm_start:
	DPRINTK("ata%u: protocol %d task_state %d (dev_stat 0x%X)\n",
		ap->print_id, qc->tf.protocol, ap->hsm_task_state, status);

	switch (ap->hsm_task_state) {
	case HSM_ST_FIRST:
		/* Send first data block or PACKET CDB */

		/* If polling, we will stay in the work queue after
		 * sending the data. Otherwise, interrupt handler
		 * takes over after sending the data.
		 */
		poll_next = (qc->tf.flags & ATA_TFLAG_POLLING);

		/* check device status */
		if (unlikely((status & ATA_DRQ) == 0)) {
			/* handle BSY=0, DRQ=0 as error */
			if (likely(status & (ATA_ERR | ATA_DF)))
				/* device stops HSM for abort/error */
				qc->err_mask |= AC_ERR_DEV;
			else {
				/* HSM violation. Let EH handle this */
				ata_ehi_push_desc(ehi,
					"ST_FIRST: !(DRQ|ERR|DF)");
				qc->err_mask |= AC_ERR_HSM;
			}

			ap->hsm_task_state = HSM_ST_ERR;
			goto fsm_start;
		}

		/* Device should not ask for data transfer (DRQ=1)
		 * when it finds something wrong.
		 * We ignore DRQ here and stop the HSM by
		 * changing hsm_task_state to HSM_ST_ERR and
		 * let the EH abort the command or reset the device.
		 */
		if (unlikely(status & (ATA_ERR | ATA_DF))) {
			/* Some ATAPI tape drives forget to clear the ERR bit
			 * when doing the next command (mostly request sense).
			 * We ignore ERR here to workaround and proceed sending
			 * the CDB.
			 */
			if (!(qc->dev->horkage & ATA_HORKAGE_STUCK_ERR)) {
				ata_ehi_push_desc(ehi, "ST_FIRST: "
					"DRQ=1 with device error, "
					"dev_stat 0x%X", status);
				qc->err_mask |= AC_ERR_HSM;
				ap->hsm_task_state = HSM_ST_ERR;
				goto fsm_start;
			}
		}

		if (qc->tf.protocol == ATA_PROT_PIO) {
			/* PIO data out protocol.
			 * send first data block.
			 */

			/* ata_pio_sectors() might change the state
			 * to HSM_ST_LAST. so, the state is changed here
			 * before ata_pio_sectors().
			 */
			ap->hsm_task_state = HSM_ST;
			ata_pio_sectors(qc);
		} else
			/* send CDB */
			atapi_send_cdb(ap, qc);

		/* if polling, ata_sff_pio_task() handles the rest.
		 * otherwise, interrupt handler takes over from here.
		 */
		break;

	case HSM_ST:
		/* complete command or read/write the data register */
		if (qc->tf.protocol == ATAPI_PROT_PIO) {
			/* ATAPI PIO protocol */
			if ((status & ATA_DRQ) == 0) {
				/* No more data to transfer or device error.
				 * Device error will be tagged in HSM_ST_LAST.
				 */
				ap->hsm_task_state = HSM_ST_LAST;
				goto fsm_start;
			}

			/* Device should not ask for data transfer (DRQ=1)
			 * when it finds something wrong.
			 * We ignore DRQ here and stop the HSM by
			 * changing hsm_task_state to HSM_ST_ERR and
			 * let the EH abort the command or reset the device.
			 */
			if (unlikely(status & (ATA_ERR | ATA_DF))) {
				ata_ehi_push_desc(ehi, "ST-ATAPI: "
					"DRQ=1 with device error, "
					"dev_stat 0x%X", status);
				qc->err_mask |= AC_ERR_HSM;
				ap->hsm_task_state = HSM_ST_ERR;
				goto fsm_start;
			}

			atapi_pio_bytes(qc);

			if (unlikely(ap->hsm_task_state == HSM_ST_ERR))
				/* bad ireason reported by device */
				goto fsm_start;

		} else {
			/* ATA PIO protocol */
			if (unlikely((status & ATA_DRQ) == 0)) {
				/* handle BSY=0, DRQ=0 as error */
				if (likely(status & (ATA_ERR | ATA_DF))) {
					/* device stops HSM for abort/error */
					qc->err_mask |= AC_ERR_DEV;

					/* If diagnostic failed and this is
					 * IDENTIFY, it's likely a phantom
					 * device.  Mark hint.
					 */
					if (qc->dev->horkage &
					    ATA_HORKAGE_DIAGNOSTIC)
						qc->err_mask |=
							AC_ERR_NODEV_HINT;
				} else {
					/* HSM violation. Let EH handle this.
					 * Phantom devices also trigger this
					 * condition.  Mark hint.
					 */
					ata_ehi_push_desc(ehi, "ST-ATA: "
						"DRQ=0 without device error, "
						"dev_stat 0x%X", status);
					qc->err_mask |= AC_ERR_HSM |
							AC_ERR_NODEV_HINT;
				}

				ap->hsm_task_state = HSM_ST_ERR;
				goto fsm_start;
			}

			/* For PIO reads, some devices may ask for
			 * data transfer (DRQ=1) alone with ERR=1.
			 * We respect DRQ here and transfer one
			 * block of junk data before changing the
			 * hsm_task_state to HSM_ST_ERR.
			 *
			 * For PIO writes, ERR=1 DRQ=1 doesn't make
			 * sense since the data block has been
			 * transferred to the device.
			 */
			if (unlikely(status & (ATA_ERR | ATA_DF))) {
				/* data might be corrputed */
				qc->err_mask |= AC_ERR_DEV;

				if (!(qc->tf.flags & ATA_TFLAG_WRITE)) {
					ata_pio_sectors(qc);
					status = ata_wait_idle(ap);
				}

				if (status & (ATA_BUSY | ATA_DRQ)) {
					ata_ehi_push_desc(ehi, "ST-ATA: "
						"BUSY|DRQ persists on ERR|DF, "
						"dev_stat 0x%X", status);
					qc->err_mask |= AC_ERR_HSM;
				}

				/* There are oddball controllers with
				 * status register stuck at 0x7f and
				 * lbal/m/h at zero which makes it
				 * pass all other presence detection
				 * mechanisms we have.  Set NODEV_HINT
				 * for it.  Kernel bz#7241.
				 */
				if (status == 0x7f)
					qc->err_mask |= AC_ERR_NODEV_HINT;

				/* ata_pio_sectors() might change the
				 * state to HSM_ST_LAST. so, the state
				 * is changed after ata_pio_sectors().
				 */
				ap->hsm_task_state = HSM_ST_ERR;
				goto fsm_start;
			}

			ata_pio_sectors(qc);

			if (ap->hsm_task_state == HSM_ST_LAST &&
			    (!(qc->tf.flags & ATA_TFLAG_WRITE))) {
				/* all data read */
				status = ata_wait_idle(ap);
				goto fsm_start;
			}
		}

		poll_next = 1;
		break;

	case HSM_ST_LAST:
		if (unlikely(!ata_ok(status))) {
			qc->err_mask |= __ac_err_mask(status);
			ap->hsm_task_state = HSM_ST_ERR;
			goto fsm_start;
		}

		/* no more data to transfer */
		DPRINTK("ata%u: dev %u command complete, drv_stat 0x%x\n",
			ap->print_id, qc->dev->devno, status);

		WARN_ON_ONCE(qc->err_mask & (AC_ERR_DEV | AC_ERR_HSM));

		ap->hsm_task_state = HSM_ST_IDLE;

		/* complete taskfile transaction */
		ata_hsm_qc_complete(qc, in_wq);

		poll_next = 0;
		break;

	case HSM_ST_ERR:
		ap->hsm_task_state = HSM_ST_IDLE;

		/* complete taskfile transaction */
		ata_hsm_qc_complete(qc, in_wq);

		poll_next = 0;
		break;
	default:
		poll_next = 0;
		WARN(true, "ata%d: SFF host state machine in invalid state %d",
		     ap->print_id, ap->hsm_task_state);
	}

	return poll_next;
}