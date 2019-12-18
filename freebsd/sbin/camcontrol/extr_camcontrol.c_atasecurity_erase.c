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
 int /*<<< orphan*/  AP_PROTO_NON_DATA ; 
 int /*<<< orphan*/  AP_PROTO_PIO_OUT ; 
 int /*<<< orphan*/  ATA_SECURITY_ERASE_PREPARE ; 
 int /*<<< orphan*/  ATA_SECURITY_ERASE_UNIT ; 
 int /*<<< orphan*/  CAM_DIR_NONE ; 
 int /*<<< orphan*/  CAM_DIR_OUT ; 
 int /*<<< orphan*/  MSG_SIMPLE_Q_TAG ; 
 int ata_do_cmd (struct cam_device*,union ccb*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atasecurity_notify (int /*<<< orphan*/ ,struct ata_security_password*) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
atasecurity_erase(struct cam_device *device, union ccb *ccb,
		  int retry_count, u_int32_t timeout,
		  u_int32_t erase_timeout,
		  struct ata_security_password *pwd, int quiet)
{
	int error;

	if (quiet == 0)
		atasecurity_notify(ATA_SECURITY_ERASE_PREPARE, NULL);

	error = ata_do_cmd(device,
			   ccb,
			   retry_count,
			   /*flags*/CAM_DIR_NONE,
			   /*protocol*/AP_PROTO_NON_DATA,
			   /*ata_flags*/0,
			   /*tag_action*/MSG_SIMPLE_Q_TAG,
			   /*command*/ATA_SECURITY_ERASE_PREPARE,
			   /*features*/0,
			   /*lba*/0,
			   /*sector_count*/0,
			   /*data_ptr*/NULL,
			   /*dxfer_len*/0,
			   /*timeout*/timeout,
			   /*force48bit*/0);

	if (error != 0)
		return error;

	if (quiet == 0)
		atasecurity_notify(ATA_SECURITY_ERASE_UNIT, pwd);

	error = ata_do_cmd(device,
			   ccb,
			   retry_count,
			   /*flags*/CAM_DIR_OUT,
			   /*protocol*/AP_PROTO_PIO_OUT,
			   /*ata_flags*/AP_FLAG_BYT_BLOK_BLOCKS |
			    AP_FLAG_TLEN_SECT_CNT,
			   /*tag_action*/MSG_SIMPLE_Q_TAG,
			   /*command*/ATA_SECURITY_ERASE_UNIT,
			   /*features*/0,
			   /*lba*/0,
			   /*sector_count*/sizeof(*pwd) / 512,
			   /*data_ptr*/(u_int8_t *)pwd,
			   /*dxfer_len*/sizeof(*pwd),
			   /*timeout*/erase_timeout,
			   /*force48bit*/0);

	if (error == 0 && quiet == 0)
		printf("\nErase Complete\n");

	return error;
}