#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct TYPE_4__ {scalar_t__ func; } ;
struct ixgbe_hw {TYPE_1__ bus; } ;
struct TYPE_5__ {scalar_t__ ret_status; int /*<<< orphan*/  cmd_resv; } ;
struct TYPE_6__ {TYPE_2__ cmd_or_resp; scalar_t__ buf_len; scalar_t__ checksum; int /*<<< orphan*/  cmd; } ;
struct ixgbe_hic_drv_info2 {TYPE_3__ hdr; int /*<<< orphan*/  driver_string; void* ver_sub; void* ver_build; void* ver_min; void* ver_maj; void* port_num; } ;
typedef  scalar_t__ s32 ;
typedef  int /*<<< orphan*/  fw_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  FW_CEM_CMD_DRIVER_INFO ; 
 scalar_t__ FW_CEM_CMD_DRIVER_INFO_LEN ; 
 int /*<<< orphan*/  FW_CEM_CMD_RESERVED ; 
 scalar_t__ FW_CEM_HDR_LEN ; 
 int FW_CEM_MAX_RETRIES ; 
 scalar_t__ FW_CEM_RESP_STATUS_SUCCESS ; 
 scalar_t__ IXGBE_ERR_HOST_INTERFACE_COMMAND ; 
 scalar_t__ IXGBE_ERR_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  IXGBE_HI_COMMAND_TIMEOUT ; 
 scalar_t__ IXGBE_SUCCESS ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ ixgbe_calculate_checksum (void**,scalar_t__) ; 
 scalar_t__ ixgbe_host_interface_command (struct ixgbe_hw*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int) ; 

s32 ixgbe_set_fw_drv_ver_x550(struct ixgbe_hw *hw, u8 maj, u8 min,
			      u8 build, u8 sub, u16 len, const char *driver_ver)
{
	struct ixgbe_hic_drv_info2 fw_cmd;
	s32 ret_val = IXGBE_SUCCESS;
	int i;

	DEBUGFUNC("ixgbe_set_fw_drv_ver_x550");

	if ((len == 0) || (driver_ver == NULL) ||
	   (len > sizeof(fw_cmd.driver_string)))
		return IXGBE_ERR_INVALID_ARGUMENT;

	fw_cmd.hdr.cmd = FW_CEM_CMD_DRIVER_INFO;
	fw_cmd.hdr.buf_len = FW_CEM_CMD_DRIVER_INFO_LEN + len;
	fw_cmd.hdr.cmd_or_resp.cmd_resv = FW_CEM_CMD_RESERVED;
	fw_cmd.port_num = (u8)hw->bus.func;
	fw_cmd.ver_maj = maj;
	fw_cmd.ver_min = min;
	fw_cmd.ver_build = build;
	fw_cmd.ver_sub = sub;
	fw_cmd.hdr.checksum = 0;
	memcpy(fw_cmd.driver_string, driver_ver, len);
	fw_cmd.hdr.checksum = ixgbe_calculate_checksum((u8 *)&fw_cmd,
				(FW_CEM_HDR_LEN + fw_cmd.hdr.buf_len));

	for (i = 0; i <= FW_CEM_MAX_RETRIES; i++) {
		ret_val = ixgbe_host_interface_command(hw, (u32 *)&fw_cmd,
						       sizeof(fw_cmd),
						       IXGBE_HI_COMMAND_TIMEOUT,
						       TRUE);
		if (ret_val != IXGBE_SUCCESS)
			continue;

		if (fw_cmd.hdr.cmd_or_resp.ret_status ==
		    FW_CEM_RESP_STATUS_SUCCESS)
			ret_val = IXGBE_SUCCESS;
		else
			ret_val = IXGBE_ERR_HOST_INTERFACE_COMMAND;

		break;
	}

	return ret_val;
}