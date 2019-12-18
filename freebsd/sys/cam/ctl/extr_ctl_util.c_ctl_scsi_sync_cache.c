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
struct TYPE_4__ {int /*<<< orphan*/  sense_len; scalar_t__ ext_data_filled; scalar_t__ ext_sg_entries; scalar_t__ ext_data_len; int /*<<< orphan*/ * ext_data_ptr; int /*<<< orphan*/  tag_type; scalar_t__ cdb; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  io_type; } ;
union ctl_io {TYPE_2__ scsiio; TYPE_1__ io_hdr; } ;
typedef  void* uint8_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;
struct scsi_sync_cache_16 {void* control; int /*<<< orphan*/  lb_count; int /*<<< orphan*/  begin_lba; int /*<<< orphan*/  byte2; int /*<<< orphan*/  opcode; } ;
struct scsi_sync_cache {void* control; int /*<<< orphan*/  lb_count; int /*<<< orphan*/  begin_lba; int /*<<< orphan*/  byte2; int /*<<< orphan*/  opcode; } ;
typedef  int /*<<< orphan*/  ctl_tag_type ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_FLAG_DATA_NONE ; 
 int /*<<< orphan*/  CTL_IO_SCSI ; 
 int /*<<< orphan*/  SSC_IMMED ; 
 int /*<<< orphan*/  SSC_RELADR ; 
 int /*<<< orphan*/  SSD_FULL_SIZE ; 
 int /*<<< orphan*/  SYNCHRONIZE_CACHE ; 
 int /*<<< orphan*/  SYNCHRONIZE_CACHE_16 ; 
 int /*<<< orphan*/  ctl_scsi_zero_io (union ctl_io*) ; 
 int /*<<< orphan*/  scsi_u64to8b (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_ulto2b (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_ulto4b (int,int /*<<< orphan*/ ) ; 

void
ctl_scsi_sync_cache(union ctl_io *io, int immed, int reladr,
		    int minimum_cdb_size, uint64_t starting_lba,
		    uint32_t block_count, ctl_tag_type tag_type,
		    uint8_t control)
{
	ctl_scsi_zero_io(io);

	if ((minimum_cdb_size < 16)
	 && ((block_count & 0xffff) == block_count)
	 && ((starting_lba & 0xffffffff) == starting_lba)) {
		struct scsi_sync_cache *cdb;

		cdb = (struct scsi_sync_cache *)io->scsiio.cdb;

		cdb->opcode = SYNCHRONIZE_CACHE;
		if (reladr)
			cdb->byte2 |= SSC_RELADR;

		if (immed)
			cdb->byte2 |= SSC_IMMED;

		scsi_ulto4b(starting_lba, cdb->begin_lba);
		scsi_ulto2b(block_count, cdb->lb_count);
		cdb->control = control;
	} else {
		struct scsi_sync_cache_16 *cdb;

		cdb = (struct scsi_sync_cache_16 *)io->scsiio.cdb;

		cdb->opcode = SYNCHRONIZE_CACHE_16;
		if (reladr)
			cdb->byte2 |= SSC_RELADR;

		if (immed)
			cdb->byte2 |= SSC_IMMED;

		scsi_u64to8b(starting_lba, cdb->begin_lba);
		scsi_ulto4b(block_count, cdb->lb_count);
		cdb->control = control;
	}
	io->io_hdr.io_type = CTL_IO_SCSI;
	io->io_hdr.flags = CTL_FLAG_DATA_NONE;
	io->scsiio.tag_type = tag_type;
	io->scsiio.ext_data_ptr = NULL;
	io->scsiio.ext_data_len = 0;
	io->scsiio.ext_sg_entries = 0;
	io->scsiio.ext_data_filled = 0;
	io->scsiio.sense_len = SSD_FULL_SIZE;
}