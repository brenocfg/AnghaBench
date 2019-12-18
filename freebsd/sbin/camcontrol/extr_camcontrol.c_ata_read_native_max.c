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
typedef  union ccb {int dummy; } ccb ;
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  int /*<<< orphan*/  u_int64_t ;
typedef  int u_int32_t ;
typedef  int u_int ;
struct cam_device {int dummy; } ;
struct TYPE_2__ {int command2; } ;
struct ata_params {TYPE_1__ support; } ;

/* Variables and functions */
 int /*<<< orphan*/  AP_EXTEND ; 
 int /*<<< orphan*/  AP_FLAG_CHK_COND ; 
 int /*<<< orphan*/  AP_PROTO_NON_DATA ; 
 int ATA_READ_NATIVE_MAX_ADDRESS ; 
 int ATA_READ_NATIVE_MAX_ADDRESS48 ; 
 int ATA_SUPPORT_ADDRESS48 ; 
 int /*<<< orphan*/  CAM_DIR_NONE ; 
 int /*<<< orphan*/  MSG_SIMPLE_Q_TAG ; 
 int ata_do_cmd (struct cam_device*,union ccb*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int atahpa_proc_resp (struct cam_device*,union ccb*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ata_read_native_max(struct cam_device *device, int retry_count,
		      u_int32_t timeout, union ccb *ccb,
		      struct ata_params *parm, u_int64_t *hpasize)
{
	int error;
	u_int cmd, is48bit;
	u_int8_t protocol;

	is48bit = parm->support.command2 & ATA_SUPPORT_ADDRESS48;
	protocol = AP_PROTO_NON_DATA;

	if (is48bit) {
		cmd = ATA_READ_NATIVE_MAX_ADDRESS48;
		protocol |= AP_EXTEND;
	} else {
		cmd = ATA_READ_NATIVE_MAX_ADDRESS;
	}

	error = ata_do_cmd(device,
			   ccb,
			   retry_count,
			   /*flags*/CAM_DIR_NONE,
			   /*protocol*/protocol,
			   /*ata_flags*/AP_FLAG_CHK_COND,
			   /*tag_action*/MSG_SIMPLE_Q_TAG,
			   /*command*/cmd,
			   /*features*/0,
			   /*lba*/0,
			   /*sector_count*/0,
			   /*data_ptr*/NULL,
			   /*dxfer_len*/0,
			   timeout ? timeout : 5000,
			   is48bit);

	if (error)
		return (error);

	return atahpa_proc_resp(device, ccb, hpasize);
}