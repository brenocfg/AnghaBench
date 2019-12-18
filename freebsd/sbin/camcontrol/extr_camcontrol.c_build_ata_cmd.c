#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;
struct TYPE_6__ {TYPE_1__ cmd; scalar_t__ aux; int /*<<< orphan*/  ata_flags; } ;
union ccb {int /*<<< orphan*/  csio; TYPE_2__ ataio; } ;
typedef  int uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  scalar_t__ camcontrol_devtype ;

/* Variables and functions */
 int AP_EXTEND ; 
 int AP_FLAG_CHK_COND ; 
 int AP_PROTO_DMA ; 
 int AP_PROTO_FPDMA ; 
 int AP_PROTO_MASK ; 
 int /*<<< orphan*/  ATA_FLAG_AUX ; 
 scalar_t__ ATA_MAX_28BIT_LBA ; 
 int /*<<< orphan*/  CAM_ATAIO_DMA ; 
 int /*<<< orphan*/  CAM_ATAIO_FPDMA ; 
 int /*<<< orphan*/  CAM_ATAIO_NEEDRESULT ; 
 scalar_t__ CC_DT_ATA ; 
 int /*<<< orphan*/  ata_28bit_cmd (TYPE_2__*,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_48bit_cmd (TYPE_2__*,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_fill_ataio (TYPE_2__*,scalar_t__,int /*<<< orphan*/ *,scalar_t__,int,int*,scalar_t__,scalar_t__) ; 
 int scsi_ata_pass (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,scalar_t__,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int*,scalar_t__,int*,size_t,int /*<<< orphan*/ ,int,scalar_t__) ; 

int
build_ata_cmd(union ccb *ccb, uint32_t retry_count, uint32_t flags,
    uint8_t tag_action, uint8_t protocol, uint8_t ata_flags, uint16_t features,
    uint16_t sector_count, uint64_t lba, uint8_t command, uint32_t auxiliary,
    uint8_t *data_ptr, uint32_t dxfer_len, uint8_t *cdb_storage,
    size_t cdb_storage_len, uint8_t sense_len, uint32_t timeout,
    int is48bit, camcontrol_devtype devtype)
{
	int retval = 0;

	if (devtype == CC_DT_ATA) {
		cam_fill_ataio(&ccb->ataio,
		    /*retries*/ retry_count,
		    /*cbfcnp*/ NULL,
		    /*flags*/ flags,
		    /*tag_action*/ tag_action,
		    /*data_ptr*/ data_ptr,
		    /*dxfer_len*/ dxfer_len,
		    /*timeout*/ timeout);
		if (is48bit || lba > ATA_MAX_28BIT_LBA)
			ata_48bit_cmd(&ccb->ataio, command, features, lba,
			    sector_count);
		else
			ata_28bit_cmd(&ccb->ataio, command, features, lba,
			    sector_count);

		if (auxiliary != 0) {
			ccb->ataio.ata_flags |= ATA_FLAG_AUX;
			ccb->ataio.aux = auxiliary;
		}

		if (ata_flags & AP_FLAG_CHK_COND)
			ccb->ataio.cmd.flags |= CAM_ATAIO_NEEDRESULT;

		if ((protocol & AP_PROTO_MASK) == AP_PROTO_DMA)
			ccb->ataio.cmd.flags |= CAM_ATAIO_DMA;
		else if ((protocol & AP_PROTO_MASK) == AP_PROTO_FPDMA)
			ccb->ataio.cmd.flags |= CAM_ATAIO_FPDMA;
	} else {
		if (is48bit || lba > ATA_MAX_28BIT_LBA)
			protocol |= AP_EXTEND;

		retval = scsi_ata_pass(&ccb->csio,
		    /*retries*/ retry_count,
		    /*cbfcnp*/ NULL,
		    /*flags*/ flags,
		    /*tag_action*/ tag_action,
		    /*protocol*/ protocol,
		    /*ata_flags*/ ata_flags,
		    /*features*/ features,
		    /*sector_count*/ sector_count,
		    /*lba*/ lba,
		    /*command*/ command,
		    /*device*/ 0,
		    /*icc*/ 0,
		    /*auxiliary*/ auxiliary,
		    /*control*/ 0,
		    /*data_ptr*/ data_ptr,
		    /*dxfer_len*/ dxfer_len,
		    /*cdb_storage*/ cdb_storage,
		    /*cdb_storage_len*/ cdb_storage_len,
		    /*minimum_cmd_size*/ 0,
		    /*sense_len*/ sense_len,
		    /*timeout*/ timeout);
	}

	return (retval);
}