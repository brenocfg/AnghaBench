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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_2__ {int flags; } ;
struct ccb_ataio {int aux; int /*<<< orphan*/  ata_flags; TYPE_1__ cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_FLAG_AUX ; 
 int ATA_RECV_FPDMA_QUEUED ; 
 int ATA_RFPDMA_ZAC_MGMT_IN ; 
 int ATA_ZAC_MANAGEMENT_IN ; 
 int CAM_ATAIO_DMA ; 
 int CAM_ATAIO_FPDMA ; 
 int /*<<< orphan*/  CAM_DIR_IN ; 
 int /*<<< orphan*/  ata_48bit_cmd (struct ccb_ataio*,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cam_fill_ataio (struct ccb_ataio*,int,void (*) (struct cam_periph*,union ccb*),int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int) ; 

void
ata_zac_mgmt_in(struct ccb_ataio *ataio, uint32_t retries, 
		void (*cbfcnp)(struct cam_periph *, union ccb *),
		int use_ncq, uint8_t zm_action, uint64_t zone_id,
		uint8_t zone_flags, uint8_t *data_ptr, uint32_t dxfer_len,
		uint32_t timeout)
{
	uint8_t command_out, ata_flags;
	uint16_t features_out, sectors_out;
	uint32_t auxiliary;

	if (use_ncq == 0) {
		command_out = ATA_ZAC_MANAGEMENT_IN;
		/* XXX KDM put a macro here */
		features_out = (zm_action & 0xf) | (zone_flags << 8);
		ata_flags = CAM_ATAIO_DMA;
		sectors_out = ((dxfer_len >> 9) & 0xffff);
		auxiliary = 0;
	} else {
		command_out = ATA_RECV_FPDMA_QUEUED;
		sectors_out = ATA_RFPDMA_ZAC_MGMT_IN << 8;
		auxiliary = (zm_action & 0xf) | (zone_flags << 8);
		ata_flags = CAM_ATAIO_FPDMA;
		/*
		 * For RECEIVE FPDMA QUEUED, the transfer length is
		 * encoded in the FEATURE register, and 0 means
		 * that 65536 512 byte blocks are to be tranferred.
		 * In practice, it is unlikely we will see a transfer that
		 * large.
		 */
		if (dxfer_len == (65536 * 512)) {
			features_out = 0;
		} else {
			/*
			 * Yes, the caller can theoretically request a
			 * transfer larger than we can handle.
			 * Anyone using this function needs enough
			 * knowledge to avoid doing that.
			 */
			features_out = ((dxfer_len >> 9) & 0xffff);
		}
	}

	cam_fill_ataio(ataio,
	    /*retries*/ retries,
	    /*cbfcnp*/ cbfcnp,
	    /*flags*/ CAM_DIR_IN,
	    /*tag_action*/ 0,
	    /*data_ptr*/ data_ptr,
	    /*dxfer_len*/ dxfer_len,
	    /*timeout*/ timeout);

	ata_48bit_cmd(ataio,
	    /*cmd*/ command_out,
	    /*features*/ features_out,
	    /*lba*/ zone_id,
	    /*sector_count*/ sectors_out);

	ataio->cmd.flags |= ata_flags;
	if (auxiliary != 0) {
		ataio->ata_flags |= ATA_FLAG_AUX;
		ataio->aux = auxiliary;
	}
}