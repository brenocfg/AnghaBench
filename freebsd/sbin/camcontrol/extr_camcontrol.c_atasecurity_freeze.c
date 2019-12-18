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
typedef  int /*<<< orphan*/  u_int32_t ;
struct cam_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AP_PROTO_NON_DATA ; 
 int /*<<< orphan*/  ATA_SECURITY_FREEZE_LOCK ; 
 int /*<<< orphan*/  CAM_DIR_NONE ; 
 int /*<<< orphan*/  MSG_SIMPLE_Q_TAG ; 
 int ata_do_cmd (struct cam_device*,union ccb*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atasecurity_notify (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
atasecurity_freeze(struct cam_device *device, union ccb *ccb,
		   int retry_count, u_int32_t timeout, int quiet)
{

	if (quiet == 0)
		atasecurity_notify(ATA_SECURITY_FREEZE_LOCK, NULL);

	return ata_do_cmd(device,
			  ccb,
			  retry_count,
			  /*flags*/CAM_DIR_NONE,
			  /*protocol*/AP_PROTO_NON_DATA,
			  /*ata_flags*/0,
			  /*tag_action*/MSG_SIMPLE_Q_TAG,
			  /*command*/ATA_SECURITY_FREEZE_LOCK,
			  /*features*/0,
			  /*lba*/0,
			  /*sector_count*/0,
			  /*data_ptr*/NULL,
			  /*dxfer_len*/0,
			  /*timeout*/timeout,
			  /*force48bit*/0);
}