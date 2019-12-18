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
typedef  union ctl_io {int dummy; } ctl_io ;
struct scsi_write_buffer {int /*<<< orphan*/  offset; int /*<<< orphan*/  length; } ;
struct TYPE_2__ {int flags; } ;
struct ctl_scsiio {int kern_data_len; int kern_total_len; int /*<<< orphan*/  be_move_done; TYPE_1__ io_hdr; scalar_t__ kern_sg_entries; scalar_t__ kern_rel_offset; int /*<<< orphan*/ * kern_data_ptr; scalar_t__ cdb; } ;
struct ctl_lun {int /*<<< orphan*/ * write_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_DEBUG_PRINT (char*) ; 
 int CTL_FLAG_ALLOCATED ; 
 struct ctl_lun* CTL_LUN (struct ctl_scsiio*) ; 
 int CTL_RETVAL_COMPLETE ; 
 int CTL_WRITE_BUFFER_SIZE ; 
 int /*<<< orphan*/  M_CTL ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  ctl_config_move_done ; 
 int /*<<< orphan*/  ctl_datamove (union ctl_io*) ; 
 int /*<<< orphan*/  ctl_done (union ctl_io*) ; 
 int /*<<< orphan*/  ctl_set_invalid_field (struct ctl_scsiio*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_set_success (struct ctl_scsiio*) ; 
 int /*<<< orphan*/ * malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int scsi_3btoul (int /*<<< orphan*/ ) ; 

int
ctl_write_buffer(struct ctl_scsiio *ctsio)
{
	struct ctl_lun *lun = CTL_LUN(ctsio);
	struct scsi_write_buffer *cdb;
	int buffer_offset, len;

	CTL_DEBUG_PRINT(("ctl_write_buffer\n"));

	cdb = (struct scsi_write_buffer *)ctsio->cdb;

	len = scsi_3btoul(cdb->length);
	buffer_offset = scsi_3btoul(cdb->offset);

	if (buffer_offset + len > CTL_WRITE_BUFFER_SIZE) {
		ctl_set_invalid_field(ctsio,
				      /*sks_valid*/ 1,
				      /*command*/ 1,
				      /*field*/ 6,
				      /*bit_valid*/ 0,
				      /*bit*/ 0);
		ctl_done((union ctl_io *)ctsio);
		return (CTL_RETVAL_COMPLETE);
	}

	/*
	 * If we've got a kernel request that hasn't been malloced yet,
	 * malloc it and tell the caller the data buffer is here.
	 */
	if ((ctsio->io_hdr.flags & CTL_FLAG_ALLOCATED) == 0) {
		if (lun->write_buffer == NULL) {
			lun->write_buffer = malloc(CTL_WRITE_BUFFER_SIZE,
			    M_CTL, M_WAITOK);
		}
		ctsio->kern_data_ptr = lun->write_buffer + buffer_offset;
		ctsio->kern_data_len = len;
		ctsio->kern_total_len = len;
		ctsio->kern_rel_offset = 0;
		ctsio->kern_sg_entries = 0;
		ctsio->io_hdr.flags |= CTL_FLAG_ALLOCATED;
		ctsio->be_move_done = ctl_config_move_done;
		ctl_datamove((union ctl_io *)ctsio);

		return (CTL_RETVAL_COMPLETE);
	}

	ctl_set_success(ctsio);
	ctl_done((union ctl_io *)ctsio);
	return (CTL_RETVAL_COMPLETE);
}