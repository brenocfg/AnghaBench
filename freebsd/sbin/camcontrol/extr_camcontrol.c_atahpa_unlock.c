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
struct ata_set_max_pwd {int dummy; } ;

/* Variables and functions */
 int AP_FLAG_BYT_BLOK_BLOCKS ; 
 int AP_FLAG_TLEN_SECT_CNT ; 
 int /*<<< orphan*/  AP_PROTO_PIO_OUT ; 
 int /*<<< orphan*/  ATA_HPA_FEAT_UNLOCK ; 
 int /*<<< orphan*/  ATA_SET_MAX_ADDRESS ; 
 int /*<<< orphan*/  ATA_SET_MAX_ADDRESS48 ; 
 int /*<<< orphan*/  CAM_DIR_OUT ; 
 int /*<<< orphan*/  MSG_SIMPLE_Q_TAG ; 
 int ata_do_cmd (struct cam_device*,union ccb*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int,int) ; 

__attribute__((used)) static int
atahpa_unlock(struct cam_device *device, int retry_count,
	      u_int32_t timeout, union ccb *ccb,
	      int is48bit, struct ata_set_max_pwd *pwd)
{
	u_int cmd;
	u_int8_t protocol;

	protocol = AP_PROTO_PIO_OUT;
	cmd = (is48bit) ? ATA_SET_MAX_ADDRESS48 : ATA_SET_MAX_ADDRESS;

	return (ata_do_cmd(device,
			   ccb,
			   retry_count,
			   /*flags*/CAM_DIR_OUT,
			   /*protocol*/protocol,
			   /*ata_flags*/AP_FLAG_BYT_BLOK_BLOCKS |
			    AP_FLAG_TLEN_SECT_CNT,
			   /*tag_action*/MSG_SIMPLE_Q_TAG,
			   /*command*/cmd,
			   /*features*/ATA_HPA_FEAT_UNLOCK,
			   /*lba*/0,
			   /*sector_count*/sizeof(*pwd) / 512,
			   /*data_ptr*/(u_int8_t*)pwd,
			   /*dxfer_len*/sizeof(*pwd),
			   timeout ? timeout : 1000,
			   is48bit));
}