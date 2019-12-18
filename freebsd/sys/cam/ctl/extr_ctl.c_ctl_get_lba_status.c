#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  union ctl_io {int dummy; } ctl_io ;
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
struct scsi_get_lba_status_data {TYPE_2__* descr; int /*<<< orphan*/  length; } ;
struct scsi_get_lba_status {int /*<<< orphan*/  alloc_len; int /*<<< orphan*/  addr; } ;
struct TYPE_7__ {int /*<<< orphan*/ * ctl_private; int /*<<< orphan*/  flags; } ;
struct ctl_scsiio {TYPE_3__ io_hdr; int /*<<< orphan*/  be_move_done; int /*<<< orphan*/  kern_data_len; int /*<<< orphan*/  kern_total_len; scalar_t__ kern_sg_entries; scalar_t__ kern_rel_offset; scalar_t__ kern_data_ptr; scalar_t__ cdb; } ;
struct ctl_lun {TYPE_4__* backend; TYPE_1__* be_lun; } ;
struct ctl_lba_len_flags {int len; scalar_t__ flags; scalar_t__ lba; } ;
struct TYPE_8__ {int (* config_read ) (union ctl_io*) ;} ;
struct TYPE_6__ {scalar_t__ status; int /*<<< orphan*/  length; int /*<<< orphan*/  addr; } ;
struct TYPE_5__ {scalar_t__ maxlba; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_DEBUG_PRINT (char*) ; 
 int /*<<< orphan*/  CTL_FLAG_ALLOCATED ; 
 struct ctl_lun* CTL_LUN (struct ctl_scsiio*) ; 
 size_t CTL_PRIV_LBA_LEN ; 
 int CTL_RETVAL_COMPLETE ; 
 int MIN (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  M_CTL ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  UINT32_MAX ; 
 int /*<<< orphan*/  ctl_config_move_done ; 
 int /*<<< orphan*/  ctl_done (union ctl_io*) ; 
 int /*<<< orphan*/  ctl_set_lba_out_of_range (struct ctl_scsiio*,scalar_t__) ; 
 int /*<<< orphan*/  ctl_set_success (struct ctl_scsiio*) ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  min (int,int) ; 
 int scsi_4btoul (int /*<<< orphan*/ ) ; 
 scalar_t__ scsi_8btou64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_u64to8b (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_ulto4b (int,int /*<<< orphan*/ ) ; 
 int stub1 (union ctl_io*) ; 

int
ctl_get_lba_status(struct ctl_scsiio *ctsio)
{
	struct ctl_lun *lun = CTL_LUN(ctsio);
	struct scsi_get_lba_status *cdb;
	struct scsi_get_lba_status_data *data;
	struct ctl_lba_len_flags *lbalen;
	uint64_t lba;
	uint32_t alloc_len, total_len;
	int retval;

	CTL_DEBUG_PRINT(("ctl_get_lba_status\n"));

	cdb = (struct scsi_get_lba_status *)ctsio->cdb;
	lba = scsi_8btou64(cdb->addr);
	alloc_len = scsi_4btoul(cdb->alloc_len);

	if (lba > lun->be_lun->maxlba) {
		ctl_set_lba_out_of_range(ctsio, lba);
		ctl_done((union ctl_io *)ctsio);
		return (CTL_RETVAL_COMPLETE);
	}

	total_len = sizeof(*data) + sizeof(data->descr[0]);
	ctsio->kern_data_ptr = malloc(total_len, M_CTL, M_WAITOK | M_ZERO);
	data = (struct scsi_get_lba_status_data *)ctsio->kern_data_ptr;
	ctsio->kern_rel_offset = 0;
	ctsio->kern_sg_entries = 0;
	ctsio->kern_data_len = min(total_len, alloc_len);
	ctsio->kern_total_len = ctsio->kern_data_len;

	/* Fill dummy data in case backend can't tell anything. */
	scsi_ulto4b(4 + sizeof(data->descr[0]), data->length);
	scsi_u64to8b(lba, data->descr[0].addr);
	scsi_ulto4b(MIN(UINT32_MAX, lun->be_lun->maxlba + 1 - lba),
	    data->descr[0].length);
	data->descr[0].status = 0; /* Mapped or unknown. */

	ctl_set_success(ctsio);
	ctsio->io_hdr.flags |= CTL_FLAG_ALLOCATED;
	ctsio->be_move_done = ctl_config_move_done;

	lbalen = (struct ctl_lba_len_flags *)&ctsio->io_hdr.ctl_private[CTL_PRIV_LBA_LEN];
	lbalen->lba = lba;
	lbalen->len = total_len;
	lbalen->flags = 0;
	retval = lun->backend->config_read((union ctl_io *)ctsio);
	return (retval);
}