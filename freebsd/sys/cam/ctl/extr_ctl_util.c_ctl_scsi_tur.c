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
struct TYPE_2__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  io_type; } ;
struct ctl_scsiio {int cdb_len; int /*<<< orphan*/  sense_len; scalar_t__ ext_data_filled; scalar_t__ ext_sg_entries; int /*<<< orphan*/ * ext_data_ptr; scalar_t__ ext_data_len; int /*<<< orphan*/  tag_type; scalar_t__ cdb; } ;
union ctl_io {TYPE_1__ io_hdr; struct ctl_scsiio scsiio; } ;
typedef  int /*<<< orphan*/  uint8_t ;
struct scsi_test_unit_ready {int /*<<< orphan*/  control; int /*<<< orphan*/  opcode; } ;
typedef  int /*<<< orphan*/  ctl_tag_type ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_FLAG_DATA_NONE ; 
 int /*<<< orphan*/  CTL_IO_SCSI ; 
 int /*<<< orphan*/  SSD_FULL_SIZE ; 
 int /*<<< orphan*/  TEST_UNIT_READY ; 
 int /*<<< orphan*/  ctl_scsi_zero_io (union ctl_io*) ; 

void
ctl_scsi_tur(union ctl_io *io, ctl_tag_type tag_type, uint8_t control)
{
	struct ctl_scsiio *ctsio;
	struct scsi_test_unit_ready *cdb;

	ctl_scsi_zero_io(io);

	io->io_hdr.io_type = CTL_IO_SCSI;
	ctsio = &io->scsiio;
	cdb = (struct scsi_test_unit_ready *)ctsio->cdb;

	cdb->opcode = TEST_UNIT_READY;
	cdb->control = control;
	io->io_hdr.flags = CTL_FLAG_DATA_NONE;
	ctsio->tag_type = tag_type;
	ctsio->cdb_len = sizeof(*cdb);
	ctsio->ext_data_len = 0;
	ctsio->ext_data_ptr = NULL;
	ctsio->ext_sg_entries = 0;
	ctsio->ext_data_filled = 0;
	ctsio->sense_len = SSD_FULL_SIZE;
}