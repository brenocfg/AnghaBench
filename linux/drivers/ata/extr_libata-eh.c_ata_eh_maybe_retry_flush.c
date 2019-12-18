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
struct ata_taskfile {scalar_t__ command; int /*<<< orphan*/  protocol; int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {scalar_t__ command; } ;
struct ata_queued_cmd {int err_mask; struct ata_taskfile result_tf; TYPE_2__* scsicmd; TYPE_1__ tf; struct ata_device* dev; } ;
struct ata_port {int pflags; } ;
struct ata_link {int /*<<< orphan*/  active_tag; struct ata_port* ap; } ;
struct ata_device {struct ata_link* link; } ;
struct TYPE_4__ {int /*<<< orphan*/  allowed; } ;

/* Variables and functions */
 int AC_ERR_DEV ; 
 scalar_t__ ATA_CMD_FLUSH ; 
 scalar_t__ ATA_CMD_FLUSH_EXT ; 
 int ATA_PFLAG_FROZEN ; 
 int /*<<< orphan*/  ATA_PROT_NODATA ; 
 int /*<<< orphan*/  ATA_TFLAG_DEVICE ; 
 int /*<<< orphan*/  DMA_NONE ; 
 int EIO ; 
 struct ata_queued_cmd* __ata_qc_from_tag (struct ata_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_dev_warn (struct ata_device*,char*,unsigned int,...) ; 
 unsigned int ata_exec_internal (struct ata_device*,struct ata_taskfile*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_tag_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_tf_init (struct ata_device*,struct ata_taskfile*) ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ata_eh_maybe_retry_flush(struct ata_device *dev)
{
	struct ata_link *link = dev->link;
	struct ata_port *ap = link->ap;
	struct ata_queued_cmd *qc;
	struct ata_taskfile tf;
	unsigned int err_mask;
	int rc = 0;

	/* did flush fail for this device? */
	if (!ata_tag_valid(link->active_tag))
		return 0;

	qc = __ata_qc_from_tag(ap, link->active_tag);
	if (qc->dev != dev || (qc->tf.command != ATA_CMD_FLUSH_EXT &&
			       qc->tf.command != ATA_CMD_FLUSH))
		return 0;

	/* if the device failed it, it should be reported to upper layers */
	if (qc->err_mask & AC_ERR_DEV)
		return 0;

	/* flush failed for some other reason, give it another shot */
	ata_tf_init(dev, &tf);

	tf.command = qc->tf.command;
	tf.flags |= ATA_TFLAG_DEVICE;
	tf.protocol = ATA_PROT_NODATA;

	ata_dev_warn(dev, "retrying FLUSH 0x%x Emask 0x%x\n",
		       tf.command, qc->err_mask);

	err_mask = ata_exec_internal(dev, &tf, NULL, DMA_NONE, NULL, 0, 0);
	if (!err_mask) {
		/*
		 * FLUSH is complete but there's no way to
		 * successfully complete a failed command from EH.
		 * Making sure retry is allowed at least once and
		 * retrying it should do the trick - whatever was in
		 * the cache is already on the platter and this won't
		 * cause infinite loop.
		 */
		qc->scsicmd->allowed = max(qc->scsicmd->allowed, 1);
	} else {
		ata_dev_warn(dev, "FLUSH failed Emask 0x%x\n",
			       err_mask);
		rc = -EIO;

		/* if device failed it, report it to upper layers */
		if (err_mask & AC_ERR_DEV) {
			qc->err_mask |= AC_ERR_DEV;
			qc->result_tf = tf;
			if (!(ap->pflags & ATA_PFLAG_FROZEN))
				rc = 0;
		}
	}
	return rc;
}