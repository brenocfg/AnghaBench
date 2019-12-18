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
typedef  int /*<<< orphan*/  u_int32_t ;
struct cam_device {int dummy; } ;
struct ata_security_password {int dummy; } ;

/* Variables and functions */
 int AP_FLAG_BYT_BLOK_BLOCKS ; 
 int AP_FLAG_TLEN_SECT_CNT ; 
 int /*<<< orphan*/  AP_PROTO_PIO_OUT ; 
 int /*<<< orphan*/  ATA_SECURITY_UNLOCK ; 
 int /*<<< orphan*/  CAM_DIR_OUT ; 
 int /*<<< orphan*/  MSG_SIMPLE_Q_TAG ; 
 int ata_do_cmd (struct cam_device*,union ccb*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atasecurity_notify (int /*<<< orphan*/ ,struct ata_security_password*) ; 

__attribute__((used)) static int
atasecurity_unlock(struct cam_device *device, union ccb *ccb,
		   int retry_count, u_int32_t timeout,
		   struct ata_security_password *pwd, int quiet)
{

	if (quiet == 0)
		atasecurity_notify(ATA_SECURITY_UNLOCK, pwd);

	return ata_do_cmd(device,
			  ccb,
			  retry_count,
			  /*flags*/CAM_DIR_OUT,
			  /*protocol*/AP_PROTO_PIO_OUT,
			  /*ata_flags*/AP_FLAG_BYT_BLOK_BLOCKS |
			    AP_FLAG_TLEN_SECT_CNT,
			  /*tag_action*/MSG_SIMPLE_Q_TAG,
			  /*command*/ATA_SECURITY_UNLOCK,
			  /*features*/0,
			  /*lba*/0,
			  /*sector_count*/sizeof(*pwd) / 512,
			  /*data_ptr*/(u_int8_t *)pwd,
			  /*dxfer_len*/sizeof(*pwd),
			  /*timeout*/timeout,
			  /*force48bit*/0);
}