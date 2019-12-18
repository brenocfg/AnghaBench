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
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct ccb_ataio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_READ_LOG_DMA_EXT ; 
 int /*<<< orphan*/  ATA_READ_LOG_EXT ; 
 int CAM_ATAIO_DMA ; 
 int /*<<< orphan*/  CAM_DIR_IN ; 
 int /*<<< orphan*/  ata_48bit_cmd (struct ccb_ataio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_fill_ataio (struct ccb_ataio*,int,void (*) (struct cam_periph*,union ccb*),int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 

void
ata_read_log(struct ccb_ataio *ataio, uint32_t retries,
	     void (*cbfcnp)(struct cam_periph *, union ccb *),
	     uint32_t log_address, uint32_t page_number, uint16_t block_count,
	     uint32_t protocol, uint8_t *data_ptr, uint32_t dxfer_len,
	     uint32_t timeout)
{
	uint64_t lba;

	cam_fill_ataio(ataio,
	    /*retries*/ 1,
	    /*cbfcnp*/ cbfcnp,
	    /*flags*/ CAM_DIR_IN,
	    /*tag_action*/ 0,
	    /*data_ptr*/ data_ptr,
	    /*dxfer_len*/ dxfer_len,
	    /*timeout*/ timeout);

	lba = (((uint64_t)page_number & 0xff00) << 32) |
	      ((page_number & 0x00ff) << 8) |
	      (log_address & 0xff);

	ata_48bit_cmd(ataio,
	    /*cmd*/ (protocol & CAM_ATAIO_DMA) ? ATA_READ_LOG_DMA_EXT :
		     ATA_READ_LOG_EXT,
	    /*features*/ 0,
	    /*lba*/ lba,
	    /*sector_count*/ block_count);
}