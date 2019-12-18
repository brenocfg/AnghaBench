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
typedef  union ctl_io {int dummy; } ctl_io ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;
struct scsi_sync_cache_16 {int /*<<< orphan*/  byte2; int /*<<< orphan*/  lb_count; int /*<<< orphan*/  begin_lba; } ;
struct scsi_sync_cache {int /*<<< orphan*/  byte2; int /*<<< orphan*/  lb_count; int /*<<< orphan*/  begin_lba; } ;
struct TYPE_5__ {int /*<<< orphan*/ * ctl_private; } ;
struct ctl_scsiio {int* cdb; TYPE_2__ io_hdr; } ;
struct ctl_lun {TYPE_3__* backend; TYPE_1__* be_lun; } ;
struct ctl_lba_len_flags {int /*<<< orphan*/  flags; scalar_t__ len; scalar_t__ lba; } ;
struct TYPE_6__ {int (* config_write ) (union ctl_io*) ;} ;
struct TYPE_4__ {scalar_t__ maxlba; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_DEBUG_PRINT (char*) ; 
 struct ctl_lun* CTL_LUN (struct ctl_scsiio*) ; 
 size_t CTL_PRIV_LBA_LEN ; 
 int /*<<< orphan*/  MAX (scalar_t__,scalar_t__) ; 
#define  SYNCHRONIZE_CACHE 129 
#define  SYNCHRONIZE_CACHE_16 128 
 int /*<<< orphan*/  ctl_done (union ctl_io*) ; 
 int /*<<< orphan*/  ctl_set_invalid_opcode (struct ctl_scsiio*) ; 
 int /*<<< orphan*/  ctl_set_lba_out_of_range (struct ctl_scsiio*,int /*<<< orphan*/ ) ; 
 scalar_t__ scsi_2btoul (int /*<<< orphan*/ ) ; 
 scalar_t__ scsi_4btoul (int /*<<< orphan*/ ) ; 
 scalar_t__ scsi_8btou64 (int /*<<< orphan*/ ) ; 
 int stub1 (union ctl_io*) ; 

int
ctl_sync_cache(struct ctl_scsiio *ctsio)
{
	struct ctl_lun *lun = CTL_LUN(ctsio);
	struct ctl_lba_len_flags *lbalen;
	uint64_t starting_lba;
	uint32_t block_count;
	int retval;
	uint8_t byte2;

	CTL_DEBUG_PRINT(("ctl_sync_cache\n"));

	retval = 0;

	switch (ctsio->cdb[0]) {
	case SYNCHRONIZE_CACHE: {
		struct scsi_sync_cache *cdb;
		cdb = (struct scsi_sync_cache *)ctsio->cdb;

		starting_lba = scsi_4btoul(cdb->begin_lba);
		block_count = scsi_2btoul(cdb->lb_count);
		byte2 = cdb->byte2;
		break;
	}
	case SYNCHRONIZE_CACHE_16: {
		struct scsi_sync_cache_16 *cdb;
		cdb = (struct scsi_sync_cache_16 *)ctsio->cdb;

		starting_lba = scsi_8btou64(cdb->begin_lba);
		block_count = scsi_4btoul(cdb->lb_count);
		byte2 = cdb->byte2;
		break;
	}
	default:
		ctl_set_invalid_opcode(ctsio);
		ctl_done((union ctl_io *)ctsio);
		goto bailout;
		break; /* NOTREACHED */
	}

	/*
	 * We check the LBA and length, but don't do anything with them.
	 * A SYNCHRONIZE CACHE will cause the entire cache for this lun to
	 * get flushed.  This check will just help satisfy anyone who wants
	 * to see an error for an out of range LBA.
	 */
	if ((starting_lba + block_count) > (lun->be_lun->maxlba + 1)) {
		ctl_set_lba_out_of_range(ctsio,
		    MAX(starting_lba, lun->be_lun->maxlba + 1));
		ctl_done((union ctl_io *)ctsio);
		goto bailout;
	}

	lbalen = (struct ctl_lba_len_flags *)&ctsio->io_hdr.ctl_private[CTL_PRIV_LBA_LEN];
	lbalen->lba = starting_lba;
	lbalen->len = block_count;
	lbalen->flags = byte2;
	retval = lun->backend->config_write((union ctl_io *)ctsio);

bailout:
	return (retval);
}