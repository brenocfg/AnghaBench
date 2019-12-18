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
typedef  int /*<<< orphan*/  u_int16_t ;
struct ccb_scsiio {int dummy; } ;

/* Variables and functions */
 int AP_EXTEND ; 
 int AP_FLAG_BYT_BLOK_BLOCKS ; 
 int AP_FLAG_TLEN_SECT_CNT ; 
 int AP_PROTO_DMA ; 
 int /*<<< orphan*/  ATA_DATA_SET_MANAGEMENT ; 
 int /*<<< orphan*/  ATA_DSM_TRIM ; 
 int /*<<< orphan*/  CAM_DIR_OUT ; 
 int /*<<< orphan*/  scsi_ata_pass_16 (struct ccb_scsiio*,int /*<<< orphan*/ ,void (*) (struct cam_periph*,union ccb*),int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
scsi_ata_trim(struct ccb_scsiio *csio, u_int32_t retries,
	      void (*cbfcnp)(struct cam_periph *, union ccb *),
	      u_int8_t tag_action, u_int16_t block_count,
	      u_int8_t *data_ptr, u_int16_t dxfer_len, u_int8_t sense_len,
	      u_int32_t timeout)
{
	scsi_ata_pass_16(csio,
			 retries,
			 cbfcnp,
			 /*flags*/CAM_DIR_OUT,
			 tag_action,
			 /*protocol*/AP_EXTEND|AP_PROTO_DMA,
			 /*ata_flags*/AP_FLAG_TLEN_SECT_CNT|AP_FLAG_BYT_BLOK_BLOCKS,
			 /*features*/ATA_DSM_TRIM,
			 /*sector_count*/block_count,
			 /*lba*/0,
			 /*command*/ATA_DATA_SET_MANAGEMENT,
			 /*control*/0,
			 data_ptr,
			 dxfer_len,
			 sense_len,
			 timeout);
}