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
typedef  scalar_t__ u8 ;
struct scsi_cmnd {scalar_t__* cmnd; int cmd_len; int result; int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;} ;
struct ata_device {scalar_t__ class; int cdb_len; } ;
typedef  int /*<<< orphan*/ * ata_xlat_func_t ;

/* Variables and functions */
 int ATAPI_CDB_LEN ; 
 scalar_t__ ATA_16 ; 
 scalar_t__ ATA_DEV_ATA ; 
 scalar_t__ ATA_DEV_ZAC ; 
 int COMMAND_SIZE (scalar_t__) ; 
 int DID_ERROR ; 
 int /*<<< orphan*/  DPRINTK (char*,int,scalar_t__,int) ; 
 int /*<<< orphan*/ * ata_get_xlat_func (struct ata_device*,scalar_t__) ; 
 int /*<<< orphan*/  ata_scsi_simulate (struct ata_device*,struct scsi_cmnd*) ; 
 int ata_scsi_translate (struct ata_device*,struct scsi_cmnd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atapi_passthru16 ; 
 int /*<<< orphan*/ * atapi_xlat ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline int __ata_scsi_queuecmd(struct scsi_cmnd *scmd,
				      struct ata_device *dev)
{
	u8 scsi_op = scmd->cmnd[0];
	ata_xlat_func_t xlat_func;
	int rc = 0;

	if (dev->class == ATA_DEV_ATA || dev->class == ATA_DEV_ZAC) {
		if (unlikely(!scmd->cmd_len || scmd->cmd_len > dev->cdb_len))
			goto bad_cdb_len;

		xlat_func = ata_get_xlat_func(dev, scsi_op);
	} else {
		if (unlikely(!scmd->cmd_len))
			goto bad_cdb_len;

		xlat_func = NULL;
		if (likely((scsi_op != ATA_16) || !atapi_passthru16)) {
			/* relay SCSI command to ATAPI device */
			int len = COMMAND_SIZE(scsi_op);
			if (unlikely(len > scmd->cmd_len ||
				     len > dev->cdb_len ||
				     scmd->cmd_len > ATAPI_CDB_LEN))
				goto bad_cdb_len;

			xlat_func = atapi_xlat;
		} else {
			/* ATA_16 passthru, treat as an ATA command */
			if (unlikely(scmd->cmd_len > 16))
				goto bad_cdb_len;

			xlat_func = ata_get_xlat_func(dev, scsi_op);
		}
	}

	if (xlat_func)
		rc = ata_scsi_translate(dev, scmd, xlat_func);
	else
		ata_scsi_simulate(dev, scmd);

	return rc;

 bad_cdb_len:
	DPRINTK("bad CDB len=%u, scsi_op=0x%02x, max=%u\n",
		scmd->cmd_len, scsi_op, dev->cdb_len);
	scmd->result = DID_ERROR << 16;
	scmd->scsi_done(scmd);
	return 0;
}