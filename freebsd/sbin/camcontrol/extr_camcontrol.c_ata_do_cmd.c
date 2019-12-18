#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  flags; } ;
struct TYPE_7__ {TYPE_1__ cmd; } ;
union ccb {TYPE_2__ ataio; } ;
typedef  int u_int8_t ;
typedef  scalar_t__ u_int64_t ;
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  int /*<<< orphan*/  u_int16_t ;
struct cam_device {int dummy; } ;

/* Variables and functions */
 int AP_FLAG_CHK_COND ; 
 scalar_t__ ATA_MAX_28BIT_LBA ; 
 int /*<<< orphan*/  CAM_ATAIO_NEEDRESULT ; 
 int /*<<< orphan*/  CCB_CLEAR_ALL_EXCEPT_HDR (TYPE_2__*) ; 
 int /*<<< orphan*/  ata_28bit_cmd (TYPE_2__*,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_48bit_cmd (TYPE_2__*,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int ata_cam_send (struct cam_device*,union ccb*) ; 
 int ata_do_pass_16 (struct cam_device*,union ccb*,int,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int) ; 
 int ata_try_pass_16 (struct cam_device*) ; 
 int /*<<< orphan*/  cam_fill_ataio (TYPE_2__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ata_do_cmd(struct cam_device *device, union ccb *ccb, int retries,
	   u_int32_t flags, u_int8_t protocol, u_int8_t ata_flags,
	   u_int8_t tag_action, u_int8_t command, u_int16_t features,
	   u_int64_t lba, u_int16_t sector_count, u_int8_t *data_ptr,
	   u_int16_t dxfer_len, int timeout, int force48bit)
{
	int retval;

	retval = ata_try_pass_16(device);
	if (retval == -1)
		return (1);

	if (retval == 1) {
		return (ata_do_pass_16(device, ccb, retries, flags, protocol,
				      ata_flags, tag_action, command, features,
				      lba, sector_count, data_ptr, dxfer_len,
				      timeout));
	}

	CCB_CLEAR_ALL_EXCEPT_HDR(&ccb->ataio);
	cam_fill_ataio(&ccb->ataio,
		       retries,
		       NULL,
		       flags,
		       tag_action,
		       data_ptr,
		       dxfer_len,
		       timeout);

	if (force48bit || lba > ATA_MAX_28BIT_LBA)
		ata_48bit_cmd(&ccb->ataio, command, features, lba, sector_count);
	else
		ata_28bit_cmd(&ccb->ataio, command, features, lba, sector_count);

	if (ata_flags & AP_FLAG_CHK_COND)
		ccb->ataio.cmd.flags |= CAM_ATAIO_NEEDRESULT;

	return ata_cam_send(device, ccb);
}