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
typedef  union ccb {int dummy; } ccb ;
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  scalar_t__ u_int64_t ;
typedef  int u_int32_t ;
typedef  int /*<<< orphan*/  u_int ;
struct cam_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AP_EXTEND ; 
 int /*<<< orphan*/  AP_FLAG_CHK_COND ; 
 int /*<<< orphan*/  AP_PROTO_NON_DATA ; 
 int /*<<< orphan*/  ATA_HPA_FEAT_MAX_ADDR ; 
 int /*<<< orphan*/  ATA_SET_MAX_ADDRESS ; 
 int /*<<< orphan*/  ATA_SET_MAX_ADDRESS48 ; 
 int /*<<< orphan*/  CAM_DIR_NONE ; 
 int /*<<< orphan*/  MSG_SIMPLE_Q_TAG ; 
 int ata_do_cmd (struct cam_device*,union ccb*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int atahpa_proc_resp (struct cam_device*,union ccb*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
atahpa_set_max(struct cam_device *device, int retry_count,
	      u_int32_t timeout, union ccb *ccb,
	      int is48bit, u_int64_t maxsize, int persist)
{
	int error;
	u_int cmd;
	u_int8_t protocol;

	protocol = AP_PROTO_NON_DATA;

	if (is48bit) {
		cmd = ATA_SET_MAX_ADDRESS48;
		protocol |= AP_EXTEND;
	} else {
		cmd = ATA_SET_MAX_ADDRESS;
	}

	/* lba's are zero indexed so the max lba is requested max - 1 */
	if (maxsize)
		maxsize--;

	error = ata_do_cmd(device,
			   ccb,
			   retry_count,
			   /*flags*/CAM_DIR_NONE,
			   /*protocol*/protocol,
			   /*ata_flags*/AP_FLAG_CHK_COND,
			   /*tag_action*/MSG_SIMPLE_Q_TAG,
			   /*command*/cmd,
			   /*features*/ATA_HPA_FEAT_MAX_ADDR,
			   /*lba*/maxsize,
			   /*sector_count*/persist,
			   /*data_ptr*/NULL,
			   /*dxfer_len*/0,
			   timeout ? timeout : 1000,
			   is48bit);

	if (error)
		return (error);

	return atahpa_proc_resp(device, ccb, NULL);
}