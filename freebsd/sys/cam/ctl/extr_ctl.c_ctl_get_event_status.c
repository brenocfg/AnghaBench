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
typedef  int uint32_t ;
struct scsi_get_event_status_header {scalar_t__ supported_class; int /*<<< orphan*/  nea_class; int /*<<< orphan*/  descr_length; } ;
struct scsi_get_event_status {int byte2; int /*<<< orphan*/  length; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;
struct ctl_scsiio {int /*<<< orphan*/  be_move_done; TYPE_1__ io_hdr; scalar_t__ kern_data_ptr; int /*<<< orphan*/  kern_data_len; int /*<<< orphan*/  kern_total_len; scalar_t__ kern_rel_offset; scalar_t__ kern_sg_entries; scalar_t__ cdb; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_FLAG_ALLOCATED ; 
 int CTL_RETVAL_COMPLETE ; 
 int /*<<< orphan*/  M_CTL ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  SGESN_NEA ; 
 int SGESN_POLLED ; 
 int /*<<< orphan*/  ctl_config_move_done ; 
 int /*<<< orphan*/  ctl_datamove (union ctl_io*) ; 
 int /*<<< orphan*/  ctl_done (union ctl_io*) ; 
 int /*<<< orphan*/  ctl_set_invalid_field (struct ctl_scsiio*,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_set_success (struct ctl_scsiio*) ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  min (int,int) ; 
 int scsi_2btoul (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_ulto2b (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
ctl_get_event_status(struct ctl_scsiio *ctsio)
{
	struct scsi_get_event_status_header *hdr;
	struct scsi_get_event_status *cdb;
	uint32_t alloc_len, data_len;

	cdb = (struct scsi_get_event_status *)ctsio->cdb;
	if ((cdb->byte2 & SGESN_POLLED) == 0) {
		ctl_set_invalid_field(ctsio, /*sks_valid*/ 1, /*command*/ 1,
		    /*field*/ 1, /*bit_valid*/ 1, /*bit*/ 0);
		ctl_done((union ctl_io *)ctsio);
		return (CTL_RETVAL_COMPLETE);
	}
	alloc_len = scsi_2btoul(cdb->length);

	data_len = sizeof(struct scsi_get_event_status_header);
	ctsio->kern_data_ptr = malloc(data_len, M_CTL, M_WAITOK | M_ZERO);
	ctsio->kern_sg_entries = 0;
	ctsio->kern_rel_offset = 0;
	ctsio->kern_data_len = min(data_len, alloc_len);
	ctsio->kern_total_len = ctsio->kern_data_len;

	hdr = (struct scsi_get_event_status_header *)ctsio->kern_data_ptr;
	scsi_ulto2b(0, hdr->descr_length);
	hdr->nea_class = SGESN_NEA;
	hdr->supported_class = 0;

	ctl_set_success(ctsio);
	ctsio->io_hdr.flags |= CTL_FLAG_ALLOCATED;
	ctsio->be_move_done = ctl_config_move_done;
	ctl_datamove((union ctl_io *)ctsio);
	return (CTL_RETVAL_COMPLETE);
}