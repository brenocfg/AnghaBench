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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  u_int32_t ;
struct ccb_ataio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_SEP_ATTN ; 
 int /*<<< orphan*/  CAM_DIR_NONE ; 
 int /*<<< orphan*/  CAM_DIR_OUT ; 
 int /*<<< orphan*/  ata_28bit_cmd (struct ccb_ataio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cam_fill_ataio (struct ccb_ataio*,int /*<<< orphan*/ ,void (*) (struct cam_periph*,union ccb*),int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int min (int,int) ; 

void
semb_send_diagnostic(struct ccb_ataio *ataio,
    u_int32_t retries, void (*cbfcnp)(struct cam_periph *, union ccb *),
    uint8_t tag_action, uint8_t *data_ptr, uint16_t length, uint32_t timeout)
{

	length = min(length, 1020);
	length = (length + 3) & ~3;
	cam_fill_ataio(ataio,
		      retries,
		      cbfcnp,
		      /*flags*/length ? CAM_DIR_OUT : CAM_DIR_NONE,
		      tag_action,
		      data_ptr,
		      length,
		      timeout);
	ata_28bit_cmd(ataio, ATA_SEP_ATTN,
	    length > 0 ? data_ptr[0] : 0, 0x82, length / 4);
}