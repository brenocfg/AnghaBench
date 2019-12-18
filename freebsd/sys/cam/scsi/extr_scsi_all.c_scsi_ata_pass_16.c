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
typedef  int uint64_t ;
typedef  int u_int8_t ;
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  int u_int16_t ;
struct TYPE_2__ {int /*<<< orphan*/  cdb_bytes; } ;
struct ccb_scsiio {TYPE_1__ cdb_io; } ;
struct ata_pass_16 {int protocol; int flags; int features_ext; int features; int sector_count_ext; int sector_count; int lba_low; int lba_mid; int lba_high; int device; int lba_low_ext; int lba_mid_ext; int lba_high_ext; int command; int control; int /*<<< orphan*/  opcode; } ;

/* Variables and functions */
 int AP_EXTEND ; 
 int ATA_DEV_LBA ; 
 int /*<<< orphan*/  ATA_PASS_16 ; 
 int /*<<< orphan*/  cam_fill_csio (struct ccb_scsiio*,int /*<<< orphan*/ ,void (*) (struct cam_periph*,union ccb*),int /*<<< orphan*/ ,int,int*,int,int,int,int /*<<< orphan*/ ) ; 

void
scsi_ata_pass_16(struct ccb_scsiio *csio, u_int32_t retries,
		 void (*cbfcnp)(struct cam_periph *, union ccb *),
		 u_int32_t flags, u_int8_t tag_action,
		 u_int8_t protocol, u_int8_t ata_flags, u_int16_t features,
		 u_int16_t sector_count, uint64_t lba, u_int8_t command,
		 u_int8_t control, u_int8_t *data_ptr, u_int16_t dxfer_len,
		 u_int8_t sense_len, u_int32_t timeout)
{
	struct ata_pass_16 *ata_cmd;

	ata_cmd = (struct ata_pass_16 *)&csio->cdb_io.cdb_bytes;
	ata_cmd->opcode = ATA_PASS_16;
	ata_cmd->protocol = protocol;
	ata_cmd->flags = ata_flags;
	ata_cmd->features_ext = features >> 8;
	ata_cmd->features = features;
	ata_cmd->sector_count_ext = sector_count >> 8;
	ata_cmd->sector_count = sector_count;
	ata_cmd->lba_low = lba;
	ata_cmd->lba_mid = lba >> 8;
	ata_cmd->lba_high = lba >> 16;
	ata_cmd->device = ATA_DEV_LBA;
	if (protocol & AP_EXTEND) {
		ata_cmd->lba_low_ext = lba >> 24;
		ata_cmd->lba_mid_ext = lba >> 32;
		ata_cmd->lba_high_ext = lba >> 40;
	} else
		ata_cmd->device |= (lba >> 24) & 0x0f;
	ata_cmd->command = command;
	ata_cmd->control = control;

	cam_fill_csio(csio,
		      retries,
		      cbfcnp,
		      flags,
		      tag_action,
		      data_ptr,
		      dxfer_len,
		      sense_len,
		      sizeof(*ata_cmd),
		      timeout);
}