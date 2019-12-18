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
typedef  int u_int32_t ;
typedef  int /*<<< orphan*/  u_int ;
struct cam_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AP_PROTO_NON_DATA ; 
 int /*<<< orphan*/  ATA_HPA_FEAT_LOCK ; 
 int /*<<< orphan*/  ATA_SET_MAX_ADDRESS ; 
 int /*<<< orphan*/  ATA_SET_MAX_ADDRESS48 ; 
 int /*<<< orphan*/  CAM_DIR_NONE ; 
 int /*<<< orphan*/  MSG_SIMPLE_Q_TAG ; 
 int ata_do_cmd (struct cam_device*,union ccb*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
atahpa_lock(struct cam_device *device, int retry_count,
	    u_int32_t timeout, union ccb *ccb, int is48bit)
{
	u_int cmd;
	u_int8_t protocol;

	protocol = AP_PROTO_NON_DATA;
	cmd = (is48bit) ? ATA_SET_MAX_ADDRESS48 : ATA_SET_MAX_ADDRESS;

	return (ata_do_cmd(device,
			   ccb,
			   retry_count,
			   /*flags*/CAM_DIR_NONE,
			   /*protocol*/protocol,
			   /*ata_flags*/0,
			   /*tag_action*/MSG_SIMPLE_Q_TAG,
			   /*command*/cmd,
			   /*features*/ATA_HPA_FEAT_LOCK,
			   /*lba*/0,
			   /*sector_count*/0,
			   /*data_ptr*/NULL,
			   /*dxfer_len*/0,
			   timeout ? timeout : 1000,
			   is48bit));
}