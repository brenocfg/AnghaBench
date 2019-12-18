#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  int u_int16_t ;
struct ccb_scsiio {int dummy; } ;

/* Variables and functions */
 int AP_FLAG_BYT_BLOK_BLOCKS ; 
 int AP_FLAG_TDIR_FROM_DEV ; 
 int AP_FLAG_TLEN_SECT_CNT ; 
 int /*<<< orphan*/  AP_PROTO_PIO_IN ; 
 int /*<<< orphan*/  ATA_ATA_IDENTIFY ; 
 int /*<<< orphan*/  CAM_DIR_IN ; 
 int /*<<< orphan*/  scsi_ata_pass (struct ccb_scsiio*,int /*<<< orphan*/ ,void (*) (struct cam_periph*,union ccb*),int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
scsi_ata_identify(struct ccb_scsiio *csio, u_int32_t retries,
		  void (*cbfcnp)(struct cam_periph *, union ccb *),
		  u_int8_t tag_action, u_int8_t *data_ptr,
		  u_int16_t dxfer_len, u_int8_t sense_len,
		  u_int32_t timeout)
{
	scsi_ata_pass(csio,
		      retries,
		      cbfcnp,
		      /*flags*/CAM_DIR_IN,
		      tag_action,
		      /*protocol*/AP_PROTO_PIO_IN,
		      /*ata_flags*/AP_FLAG_TDIR_FROM_DEV |
				   AP_FLAG_BYT_BLOK_BLOCKS |
				   AP_FLAG_TLEN_SECT_CNT,
		      /*features*/0,
		      /*sector_count*/dxfer_len / 512,
		      /*lba*/0,
		      /*command*/ATA_ATA_IDENTIFY,
		      /*device*/ 0,
		      /*icc*/ 0,
		      /*auxiliary*/ 0,
		      /*control*/0,
		      data_ptr,
		      dxfer_len,
		      /*cdb_storage*/ NULL,
		      /*cdb_storage_len*/ 0,
		      /*minimum_cmd_size*/ 0,
		      sense_len,
		      timeout);
}