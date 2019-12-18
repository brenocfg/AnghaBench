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
typedef  int uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
struct scsi_write_same_16 {int byte2; int /*<<< orphan*/  length; int /*<<< orphan*/  addr; } ;
struct scsi_write_same_10 {int byte2; int /*<<< orphan*/  length; int /*<<< orphan*/  addr; } ;
struct TYPE_5__ {int flags; int /*<<< orphan*/ * ctl_private; } ;
struct ctl_scsiio {int* cdb; int kern_data_len; int kern_total_len; TYPE_2__ io_hdr; int /*<<< orphan*/  be_move_done; scalar_t__ kern_sg_entries; scalar_t__ kern_rel_offset; int /*<<< orphan*/  kern_data_ptr; int /*<<< orphan*/  io_cont; } ;
struct ctl_lun {TYPE_3__* backend; TYPE_1__* be_lun; } ;
struct ctl_lba_len_flags {int len; int flags; scalar_t__ lba; } ;
struct TYPE_6__ {int (* config_write ) (union ctl_io*) ;} ;
struct TYPE_4__ {scalar_t__ maxlba; int blocksize; int /*<<< orphan*/  options; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_DEBUG_PRINT (char*) ; 
 int CTL_FLAG_ALLOCATED ; 
 int CTL_FLAG_IO_CONT ; 
 struct ctl_lun* CTL_LUN (struct ctl_scsiio*) ; 
 size_t CTL_PRIV_LBA_LEN ; 
 int CTL_RETVAL_COMPLETE ; 
 int /*<<< orphan*/  MAX (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  M_CTL ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int SWS_ANCHOR ; 
 int SWS_NDOB ; 
 int SWS_UNMAP ; 
 scalar_t__ UINT32_MAX ; 
 scalar_t__ UINT64_MAX ; 
#define  WRITE_SAME_10 129 
#define  WRITE_SAME_16 128 
 int /*<<< orphan*/  ctl_config_move_done ; 
 int /*<<< orphan*/  ctl_datamove (union ctl_io*) ; 
 int /*<<< orphan*/  ctl_done (union ctl_io*) ; 
 int /*<<< orphan*/  ctl_expand_number (char const*,scalar_t__*) ; 
 int /*<<< orphan*/  ctl_set_invalid_field (struct ctl_scsiio*,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_set_invalid_opcode (struct ctl_scsiio*) ; 
 int /*<<< orphan*/  ctl_set_lba_out_of_range (struct ctl_scsiio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_write_same_cont ; 
 char* dnvlist_get_string (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int scsi_2btoul (int /*<<< orphan*/ ) ; 
 void* scsi_4btoul (int /*<<< orphan*/ ) ; 
 scalar_t__ scsi_8btou64 (int /*<<< orphan*/ ) ; 
 int stub1 (union ctl_io*) ; 

int
ctl_write_same(struct ctl_scsiio *ctsio)
{
	struct ctl_lun *lun = CTL_LUN(ctsio);
	struct ctl_lba_len_flags *lbalen;
	const char *val;
	uint64_t lba, ival;
	uint32_t num_blocks;
	int len, retval;
	uint8_t byte2;

	CTL_DEBUG_PRINT(("ctl_write_same\n"));

	switch (ctsio->cdb[0]) {
	case WRITE_SAME_10: {
		struct scsi_write_same_10 *cdb;

		cdb = (struct scsi_write_same_10 *)ctsio->cdb;

		lba = scsi_4btoul(cdb->addr);
		num_blocks = scsi_2btoul(cdb->length);
		byte2 = cdb->byte2;
		break;
	}
	case WRITE_SAME_16: {
		struct scsi_write_same_16 *cdb;

		cdb = (struct scsi_write_same_16 *)ctsio->cdb;

		lba = scsi_8btou64(cdb->addr);
		num_blocks = scsi_4btoul(cdb->length);
		byte2 = cdb->byte2;
		break;
	}
	default:
		/*
		 * We got a command we don't support.  This shouldn't
		 * happen, commands should be filtered out above us.
		 */
		ctl_set_invalid_opcode(ctsio);
		ctl_done((union ctl_io *)ctsio);

		return (CTL_RETVAL_COMPLETE);
		break; /* NOTREACHED */
	}

	/* ANCHOR flag can be used only together with UNMAP */
	if ((byte2 & SWS_UNMAP) == 0 && (byte2 & SWS_ANCHOR) != 0) {
		ctl_set_invalid_field(ctsio, /*sks_valid*/ 1,
		    /*command*/ 1, /*field*/ 1, /*bit_valid*/ 1, /*bit*/ 0);
		ctl_done((union ctl_io *)ctsio);
		return (CTL_RETVAL_COMPLETE);
	}

	/*
	 * The first check is to make sure we're in bounds, the second
	 * check is to catch wrap-around problems.  If the lba + num blocks
	 * is less than the lba, then we've wrapped around and the block
	 * range is invalid anyway.
	 */
	if (((lba + num_blocks) > (lun->be_lun->maxlba + 1))
	 || ((lba + num_blocks) < lba)) {
		ctl_set_lba_out_of_range(ctsio,
		    MAX(lba, lun->be_lun->maxlba + 1));
		ctl_done((union ctl_io *)ctsio);
		return (CTL_RETVAL_COMPLETE);
	}

	/* Zero number of blocks means "to the last logical block" */
	if (num_blocks == 0) {
		ival = UINT64_MAX;
		val = dnvlist_get_string(lun->be_lun->options,
		    "write_same_max_lba", NULL);
		if (val != NULL)
			ctl_expand_number(val, &ival);
		if ((lun->be_lun->maxlba + 1) - lba > ival) {
			ctl_set_invalid_field(ctsio,
			    /*sks_valid*/ 1, /*command*/ 1,
			    /*field*/ ctsio->cdb[0] == WRITE_SAME_10 ? 7 : 10,
			    /*bit_valid*/ 0, /*bit*/ 0);
			ctl_done((union ctl_io *)ctsio);
			return (CTL_RETVAL_COMPLETE);
		}
		if ((lun->be_lun->maxlba + 1) - lba > UINT32_MAX) {
			ctsio->io_hdr.flags |= CTL_FLAG_IO_CONT;
			ctsio->io_cont = ctl_write_same_cont;
			num_blocks = 1 << 31;
		} else
			num_blocks = (lun->be_lun->maxlba + 1) - lba;
	}

	len = lun->be_lun->blocksize;

	/*
	 * If we've got a kernel request that hasn't been malloced yet,
	 * malloc it and tell the caller the data buffer is here.
	 */
	if ((byte2 & SWS_NDOB) == 0 &&
	    (ctsio->io_hdr.flags & CTL_FLAG_ALLOCATED) == 0) {
		ctsio->kern_data_ptr = malloc(len, M_CTL, M_WAITOK);
		ctsio->kern_data_len = len;
		ctsio->kern_total_len = len;
		ctsio->kern_rel_offset = 0;
		ctsio->kern_sg_entries = 0;
		ctsio->io_hdr.flags |= CTL_FLAG_ALLOCATED;
		ctsio->be_move_done = ctl_config_move_done;
		ctl_datamove((union ctl_io *)ctsio);

		return (CTL_RETVAL_COMPLETE);
	}

	lbalen = (struct ctl_lba_len_flags *)&ctsio->io_hdr.ctl_private[CTL_PRIV_LBA_LEN];
	lbalen->lba = lba;
	lbalen->len = num_blocks;
	lbalen->flags = byte2;
	retval = lun->backend->config_write((union ctl_io *)ctsio);

	return (retval);
}