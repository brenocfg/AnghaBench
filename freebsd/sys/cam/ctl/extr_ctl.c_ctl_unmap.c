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
struct scsi_unmap_header {int /*<<< orphan*/  desc_length; int /*<<< orphan*/  length; } ;
struct scsi_unmap_desc {int /*<<< orphan*/  length; int /*<<< orphan*/  lba; } ;
struct scsi_unmap {int /*<<< orphan*/  byte2; int /*<<< orphan*/  length; } ;
struct TYPE_6__ {int flags; int /*<<< orphan*/ * ctl_private; } ;
struct ctl_scsiio {int kern_data_len; int kern_total_len; int kern_data_resid; TYPE_3__ io_hdr; scalar_t__ kern_data_ptr; int /*<<< orphan*/  be_move_done; scalar_t__ kern_sg_entries; scalar_t__ kern_rel_offset; scalar_t__ cdb; } ;
struct ctl_ptr_len_flags {int len; int /*<<< orphan*/  flags; void* ptr; } ;
struct ctl_lun {TYPE_2__* backend; int /*<<< orphan*/  lun_lock; TYPE_1__* be_lun; } ;
struct TYPE_5__ {int (* config_write ) (union ctl_io*) ;} ;
struct TYPE_4__ {scalar_t__ maxlba; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_DEBUG_PRINT (char*) ; 
 int CTL_FLAG_ALLOCATED ; 
 struct ctl_lun* CTL_LUN (struct ctl_scsiio*) ; 
 size_t CTL_PRIV_LBA_LEN ; 
 int CTL_RETVAL_COMPLETE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MAX (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  M_CTL ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  ctl_config_move_done ; 
 int /*<<< orphan*/  ctl_datamove (union ctl_io*) ; 
 int /*<<< orphan*/  ctl_done (union ctl_io*) ; 
 int /*<<< orphan*/  ctl_set_invalid_field (struct ctl_scsiio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_set_lba_out_of_range (struct ctl_scsiio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_set_success (struct ctl_scsiio*) ; 
 int /*<<< orphan*/  ctl_try_unblock_others (struct ctl_lun*,union ctl_io*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int scsi_2btoul (int /*<<< orphan*/ ) ; 
 scalar_t__ scsi_4btoul (int /*<<< orphan*/ ) ; 
 scalar_t__ scsi_8btou64 (int /*<<< orphan*/ ) ; 
 int stub1 (union ctl_io*) ; 

int
ctl_unmap(struct ctl_scsiio *ctsio)
{
	struct ctl_lun *lun = CTL_LUN(ctsio);
	struct scsi_unmap *cdb;
	struct ctl_ptr_len_flags *ptrlen;
	struct scsi_unmap_header *hdr;
	struct scsi_unmap_desc *buf, *end, *endnz, *range;
	uint64_t lba;
	uint32_t num_blocks;
	int len, retval;
	uint8_t byte2;

	CTL_DEBUG_PRINT(("ctl_unmap\n"));

	cdb = (struct scsi_unmap *)ctsio->cdb;
	len = scsi_2btoul(cdb->length);
	byte2 = cdb->byte2;

	/*
	 * If we've got a kernel request that hasn't been malloced yet,
	 * malloc it and tell the caller the data buffer is here.
	 */
	if ((ctsio->io_hdr.flags & CTL_FLAG_ALLOCATED) == 0) {
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

	len = ctsio->kern_total_len - ctsio->kern_data_resid;
	hdr = (struct scsi_unmap_header *)ctsio->kern_data_ptr;
	if (len < sizeof (*hdr) ||
	    len < (scsi_2btoul(hdr->length) + sizeof(hdr->length)) ||
	    len < (scsi_2btoul(hdr->desc_length) + sizeof (*hdr)) ||
	    scsi_2btoul(hdr->desc_length) % sizeof(*buf) != 0) {
		ctl_set_invalid_field(ctsio,
				      /*sks_valid*/ 0,
				      /*command*/ 0,
				      /*field*/ 0,
				      /*bit_valid*/ 0,
				      /*bit*/ 0);
		goto done;
	}
	len = scsi_2btoul(hdr->desc_length);
	buf = (struct scsi_unmap_desc *)(hdr + 1);
	end = buf + len / sizeof(*buf);

	endnz = buf;
	for (range = buf; range < end; range++) {
		lba = scsi_8btou64(range->lba);
		num_blocks = scsi_4btoul(range->length);
		if (((lba + num_blocks) > (lun->be_lun->maxlba + 1))
		 || ((lba + num_blocks) < lba)) {
			ctl_set_lba_out_of_range(ctsio,
			    MAX(lba, lun->be_lun->maxlba + 1));
			ctl_done((union ctl_io *)ctsio);
			return (CTL_RETVAL_COMPLETE);
		}
		if (num_blocks != 0)
			endnz = range + 1;
	}

	/*
	 * Block backend can not handle zero last range.
	 * Filter it out and return if there is nothing left.
	 */
	len = (uint8_t *)endnz - (uint8_t *)buf;
	if (len == 0) {
		ctl_set_success(ctsio);
		goto done;
	}

	mtx_lock(&lun->lun_lock);
	ptrlen = (struct ctl_ptr_len_flags *)
	    &ctsio->io_hdr.ctl_private[CTL_PRIV_LBA_LEN];
	ptrlen->ptr = (void *)buf;
	ptrlen->len = len;
	ptrlen->flags = byte2;
	ctl_try_unblock_others(lun, (union ctl_io *)ctsio, FALSE);
	mtx_unlock(&lun->lun_lock);

	retval = lun->backend->config_write((union ctl_io *)ctsio);
	return (retval);

done:
	if (ctsio->io_hdr.flags & CTL_FLAG_ALLOCATED) {
		free(ctsio->kern_data_ptr, M_CTL);
		ctsio->io_hdr.flags &= ~CTL_FLAG_ALLOCATED;
	}
	ctl_done((union ctl_io *)ctsio);
	return (CTL_RETVAL_COMPLETE);
}