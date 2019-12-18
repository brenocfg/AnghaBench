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
typedef  union ctl_io {int dummy; } ctl_io ;
typedef  scalar_t__ uint32_t ;
struct scsi_read_capacity_data {int /*<<< orphan*/  length; int /*<<< orphan*/  addr; } ;
struct scsi_read_capacity {int pmi; int /*<<< orphan*/  addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
struct ctl_scsiio {int kern_data_len; int kern_total_len; int /*<<< orphan*/  be_move_done; TYPE_2__ io_hdr; scalar_t__ kern_sg_entries; scalar_t__ kern_rel_offset; scalar_t__ kern_data_ptr; scalar_t__ cdb; } ;
struct ctl_lun {TYPE_1__* be_lun; } ;
struct TYPE_3__ {int maxlba; int blocksize; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_DEBUG_PRINT (char*) ; 
 int /*<<< orphan*/  CTL_FLAG_ALLOCATED ; 
 struct ctl_lun* CTL_LUN (struct ctl_scsiio*) ; 
 int CTL_RETVAL_COMPLETE ; 
 int /*<<< orphan*/  M_CTL ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int SRC_PMI ; 
 int /*<<< orphan*/  ctl_config_move_done ; 
 int /*<<< orphan*/  ctl_datamove (union ctl_io*) ; 
 int /*<<< orphan*/  ctl_done (union ctl_io*) ; 
 int /*<<< orphan*/  ctl_set_invalid_field (struct ctl_scsiio*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_set_success (struct ctl_scsiio*) ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ scsi_4btoul (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_ulto4b (int,int /*<<< orphan*/ ) ; 

int
ctl_read_capacity(struct ctl_scsiio *ctsio)
{
	struct ctl_lun *lun = CTL_LUN(ctsio);
	struct scsi_read_capacity *cdb;
	struct scsi_read_capacity_data *data;
	uint32_t lba;

	CTL_DEBUG_PRINT(("ctl_read_capacity\n"));

	cdb = (struct scsi_read_capacity *)ctsio->cdb;

	lba = scsi_4btoul(cdb->addr);
	if (((cdb->pmi & SRC_PMI) == 0)
	 && (lba != 0)) {
		ctl_set_invalid_field(/*ctsio*/ ctsio,
				      /*sks_valid*/ 1,
				      /*command*/ 1,
				      /*field*/ 2,
				      /*bit_valid*/ 0,
				      /*bit*/ 0);
		ctl_done((union ctl_io *)ctsio);
		return (CTL_RETVAL_COMPLETE);
	}

	ctsio->kern_data_ptr = malloc(sizeof(*data), M_CTL, M_WAITOK | M_ZERO);
	data = (struct scsi_read_capacity_data *)ctsio->kern_data_ptr;
	ctsio->kern_data_len = sizeof(*data);
	ctsio->kern_total_len = sizeof(*data);
	ctsio->kern_rel_offset = 0;
	ctsio->kern_sg_entries = 0;

	/*
	 * If the maximum LBA is greater than 0xfffffffe, the user must
	 * issue a SERVICE ACTION IN (16) command, with the read capacity
	 * serivce action set.
	 */
	if (lun->be_lun->maxlba > 0xfffffffe)
		scsi_ulto4b(0xffffffff, data->addr);
	else
		scsi_ulto4b(lun->be_lun->maxlba, data->addr);

	/*
	 * XXX KDM this may not be 512 bytes...
	 */
	scsi_ulto4b(lun->be_lun->blocksize, data->length);

	ctl_set_success(ctsio);
	ctsio->io_hdr.flags |= CTL_FLAG_ALLOCATED;
	ctsio->be_move_done = ctl_config_move_done;
	ctl_datamove((union ctl_io *)ctsio);
	return (CTL_RETVAL_COMPLETE);
}