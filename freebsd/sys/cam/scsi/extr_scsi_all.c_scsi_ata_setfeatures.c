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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct ccb_scsiio {int dummy; } ;

/* Variables and functions */
 int AP_FLAG_BYT_BLOK_BYTES ; 
 int AP_FLAG_TDIR_FROM_DEV ; 
 int AP_FLAG_TLEN_SECT_CNT ; 
 int /*<<< orphan*/  AP_PROTO_PIO_IN ; 
 int /*<<< orphan*/  ATA_SETFEATURES ; 
 int /*<<< orphan*/  CAM_DIR_NONE ; 
 int scsi_ata_pass (struct ccb_scsiio*,int /*<<< orphan*/ ,void (*) (struct cam_periph*,union ccb*),int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int scsi_ata_setfeatures(struct ccb_scsiio *csio, uint32_t retries,
			 void (*cbfcnp)(struct cam_periph *, union ccb *),
			 uint8_t tag_action, uint8_t feature,
			 uint64_t lba, uint32_t count,
			 uint8_t sense_len, uint32_t timeout)
{
	return (scsi_ata_pass(csio,
		retries,
		cbfcnp,
		/*flags*/CAM_DIR_NONE,
		tag_action,
		/*protocol*/AP_PROTO_PIO_IN,
		/*ata_flags*/AP_FLAG_TDIR_FROM_DEV |
			     AP_FLAG_BYT_BLOK_BYTES |
			     AP_FLAG_TLEN_SECT_CNT,
		/*features*/feature,
		/*sector_count*/count,
		/*lba*/lba,
		/*command*/ATA_SETFEATURES,
		/*device*/ 0,
		/*icc*/ 0,
		/*auxiliary*/0,
		/*control*/0,
		/*data_ptr*/NULL,
		/*dxfer_len*/0,
		/*cdb_storage*/NULL,
		/*cdb_storage_len*/0,
		/*minimum_cmd_size*/0,
		sense_len,
		timeout));
}