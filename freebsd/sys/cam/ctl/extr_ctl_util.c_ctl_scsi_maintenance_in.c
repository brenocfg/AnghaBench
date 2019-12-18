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
struct TYPE_4__ {void** ext_data_ptr; int /*<<< orphan*/  sense_len; scalar_t__ ext_data_filled; scalar_t__ ext_sg_entries; int /*<<< orphan*/  ext_data_len; int /*<<< orphan*/  tag_type; scalar_t__ cdb; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  io_type; } ;
union ctl_io {TYPE_2__ scsiio; TYPE_1__ io_hdr; } ;
typedef  void* uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct scsi_maintenance_in {void* control; int /*<<< orphan*/  length; void* byte2; int /*<<< orphan*/  opcode; } ;
typedef  int /*<<< orphan*/  ctl_tag_type ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_FLAG_DATA_IN ; 
 int /*<<< orphan*/  CTL_IO_SCSI ; 
 int /*<<< orphan*/  MAINTENANCE_IN ; 
 int /*<<< orphan*/  SSD_FULL_SIZE ; 
 int /*<<< orphan*/  ctl_scsi_zero_io (union ctl_io*) ; 
 int /*<<< orphan*/  scsi_ulto4b (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ctl_scsi_maintenance_in(union ctl_io *io, uint8_t *data_ptr, uint32_t data_len, 
			uint8_t action, ctl_tag_type tag_type, uint8_t control)
{
	struct scsi_maintenance_in *cdb;

	ctl_scsi_zero_io(io);

	cdb = (struct scsi_maintenance_in *)io->scsiio.cdb;
	cdb->opcode = MAINTENANCE_IN;
	cdb->byte2 = action;
	scsi_ulto4b(data_len, cdb->length);
	cdb->control = control;

	io->io_hdr.io_type = CTL_IO_SCSI;
	io->io_hdr.flags = CTL_FLAG_DATA_IN;
	io->scsiio.tag_type = tag_type;
	io->scsiio.ext_data_ptr = data_ptr;
	io->scsiio.ext_data_len = data_len;
	io->scsiio.ext_sg_entries = 0;
	io->scsiio.ext_data_filled = 0;
	io->scsiio.sense_len = SSD_FULL_SIZE;
}