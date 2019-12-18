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
typedef  void* uint8_t ;
typedef  scalar_t__ uint32_t ;
struct scsi_read_defect_data_hdr_12 {int /*<<< orphan*/  length; int /*<<< orphan*/  generation; void* format; } ;
struct scsi_read_defect_data_hdr_10 {int /*<<< orphan*/  length; void* format; } ;
struct scsi_read_defect_data_12 {int /*<<< orphan*/  alloc_length; void* format; } ;
struct scsi_read_defect_data_10 {int /*<<< orphan*/  alloc_length; void* format; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;
struct ctl_scsiio {scalar_t__* cdb; int /*<<< orphan*/  be_move_done; TYPE_1__ io_hdr; scalar_t__ kern_data_ptr; int /*<<< orphan*/  kern_data_len; int /*<<< orphan*/  kern_total_len; scalar_t__ kern_sg_entries; scalar_t__ kern_rel_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_DEBUG_PRINT (char*) ; 
 int /*<<< orphan*/  CTL_FLAG_ALLOCATED ; 
 int CTL_RETVAL_COMPLETE ; 
 int /*<<< orphan*/  M_CTL ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 scalar_t__ READ_DEFECT_DATA_10 ; 
 int /*<<< orphan*/  ctl_config_move_done ; 
 int /*<<< orphan*/  ctl_datamove (union ctl_io*) ; 
 int /*<<< orphan*/  ctl_done (union ctl_io*) ; 
 int /*<<< orphan*/  ctl_set_success (struct ctl_scsiio*) ; 
 scalar_t__ malloc (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  min (scalar_t__,scalar_t__) ; 
 scalar_t__ scsi_2btoul (int /*<<< orphan*/ ) ; 
 scalar_t__ scsi_4btoul (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_ulto2b (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_ulto4b (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
ctl_read_defect(struct ctl_scsiio *ctsio)
{
	struct scsi_read_defect_data_10 *ccb10;
	struct scsi_read_defect_data_12 *ccb12;
	struct scsi_read_defect_data_hdr_10 *data10;
	struct scsi_read_defect_data_hdr_12 *data12;
	uint32_t alloc_len, data_len;
	uint8_t format;

	CTL_DEBUG_PRINT(("ctl_read_defect\n"));

	if (ctsio->cdb[0] == READ_DEFECT_DATA_10) {
		ccb10 = (struct scsi_read_defect_data_10 *)&ctsio->cdb;
		format = ccb10->format;
		alloc_len = scsi_2btoul(ccb10->alloc_length);
		data_len = sizeof(*data10);
	} else {
		ccb12 = (struct scsi_read_defect_data_12 *)&ctsio->cdb;
		format = ccb12->format;
		alloc_len = scsi_4btoul(ccb12->alloc_length);
		data_len = sizeof(*data12);
	}
	if (alloc_len == 0) {
		ctl_set_success(ctsio);
		ctl_done((union ctl_io *)ctsio);
		return (CTL_RETVAL_COMPLETE);
	}

	ctsio->kern_data_ptr = malloc(data_len, M_CTL, M_WAITOK | M_ZERO);
	ctsio->kern_rel_offset = 0;
	ctsio->kern_sg_entries = 0;
	ctsio->kern_data_len = min(data_len, alloc_len);
	ctsio->kern_total_len = ctsio->kern_data_len;

	if (ctsio->cdb[0] == READ_DEFECT_DATA_10) {
		data10 = (struct scsi_read_defect_data_hdr_10 *)
		    ctsio->kern_data_ptr;
		data10->format = format;
		scsi_ulto2b(0, data10->length);
	} else {
		data12 = (struct scsi_read_defect_data_hdr_12 *)
		    ctsio->kern_data_ptr;
		data12->format = format;
		scsi_ulto2b(0, data12->generation);
		scsi_ulto4b(0, data12->length);
	}

	ctl_set_success(ctsio);
	ctsio->io_hdr.flags |= CTL_FLAG_ALLOCATED;
	ctsio->be_move_done = ctl_config_move_done;
	ctl_datamove((union ctl_io *)ctsio);
	return (CTL_RETVAL_COMPLETE);
}