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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct ccb_scsiio {int dummy; } ;

/* Variables and functions */
 int AP_EXTEND ; 
 int AP_FLAG_BYT_BLOK_BLOCKS ; 
 int AP_FLAG_TDIR_FROM_DEV ; 
 int AP_FLAG_TLEN_FEAT ; 
 int AP_FLAG_TLEN_SECT_CNT ; 
 int AP_PROTO_DMA ; 
 int AP_PROTO_FPDMA ; 
 int ATA_RECV_FPDMA_QUEUED ; 
 int ATA_RFPDMA_ZAC_MGMT_IN ; 
 int ATA_ZAC_MANAGEMENT_IN ; 
 int /*<<< orphan*/  CAM_DIR_IN ; 
 int /*<<< orphan*/  SSD_FULL_SIZE ; 
 int scsi_ata_pass (struct ccb_scsiio*,int,void (*) (struct cam_periph*,union ccb*),int /*<<< orphan*/ ,int,int,int,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*,int,int*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
scsi_ata_zac_mgmt_in(struct ccb_scsiio *csio, uint32_t retries,
		     void (*cbfcnp)(struct cam_periph *, union ccb *),
		     uint8_t tag_action, int use_ncq,
		     uint8_t zm_action, uint64_t zone_id, uint8_t zone_flags,
		     uint8_t *data_ptr, uint32_t dxfer_len,
		     uint8_t *cdb_storage, size_t cdb_storage_len,
		     uint8_t sense_len, uint32_t timeout)
{
	uint8_t command_out, protocol;
	uint16_t features_out, sectors_out;
	uint32_t auxiliary;
	int ata_flags;
	int retval;

	retval = 0;
	ata_flags = AP_FLAG_TDIR_FROM_DEV | AP_FLAG_BYT_BLOK_BLOCKS;

	if (use_ncq == 0) {
		command_out = ATA_ZAC_MANAGEMENT_IN;
		/* XXX KDM put a macro here */
		features_out = (zm_action & 0xf) | (zone_flags << 8);
		sectors_out = dxfer_len >> 9; /* XXX KDM macro */
		protocol = AP_PROTO_DMA;
		ata_flags |= AP_FLAG_TLEN_SECT_CNT;
		auxiliary = 0;
	} else {
		ata_flags |= AP_FLAG_TLEN_FEAT;

		command_out = ATA_RECV_FPDMA_QUEUED;
		sectors_out = ATA_RFPDMA_ZAC_MGMT_IN << 8;

		/*
		 * For RECEIVE FPDMA QUEUED, the transfer length is
		 * encoded in the FEATURE register, and 0 means
		 * that 65536 512 byte blocks are to be tranferred.
		 * In practice, it seems unlikely that we'll see
		 * a transfer that large, and it may confuse the
		 * the SAT layer, because generally that means that
		 * 0 bytes should be transferred.
		 */
		if (dxfer_len == (65536 * 512)) {
			features_out = 0;
		} else if (dxfer_len <= (65535 * 512)) {
			features_out = ((dxfer_len >> 9) & 0xffff);
		} else {
			/* The transfer is too big. */
			retval = 1;
			goto bailout;
		}
		auxiliary = (zm_action & 0xf) | (zone_flags << 8),
		protocol = AP_PROTO_FPDMA;
	}

	protocol |= AP_EXTEND;

	retval = scsi_ata_pass(csio,
	    retries,
	    cbfcnp,
	    /*flags*/ CAM_DIR_IN,
	    tag_action,
	    /*protocol*/ protocol,
	    /*ata_flags*/ ata_flags,
	    /*features*/ features_out,
	    /*sector_count*/ sectors_out,
	    /*lba*/ zone_id,
	    /*command*/ command_out,
	    /*device*/ 0,
	    /*icc*/ 0,
	    /*auxiliary*/ auxiliary,
	    /*control*/ 0,
	    /*data_ptr*/ data_ptr,
	    /*dxfer_len*/ (dxfer_len >> 9) * 512, /* XXX KDM */
	    /*cdb_storage*/ cdb_storage,
	    /*cdb_storage_len*/ cdb_storage_len,
	    /*minimum_cmd_size*/ 0,
	    /*sense_len*/ SSD_FULL_SIZE,
	    /*timeout*/ timeout);

bailout:
	return (retval);
}