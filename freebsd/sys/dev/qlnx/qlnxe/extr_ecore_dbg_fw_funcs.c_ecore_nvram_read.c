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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int dummy; } ;
typedef  scalar_t__ s32 ;
typedef  enum dbg_status { ____Placeholder_dbg_status } dbg_status ;

/* Variables and functions */
 int DBG_STATUS_NVRAM_READ_FAILED ; 
 int DBG_STATUS_OK ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int) ; 
 int DRV_MB_PARAM_NVM_LEN_OFFSET ; 
 int /*<<< orphan*/  DRV_MSG_CODE_NVM_READ_NVRAM ; 
 int /*<<< orphan*/  ECORE_MSG_DEBUG ; 
 int FW_MSG_CODE_MASK ; 
 int FW_MSG_CODE_NVM_OK ; 
 scalar_t__ MCP_DRV_NVM_BUF_LEN ; 
 scalar_t__ ecore_mcp_nvm_rd_cmd (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int,int*,int*,int*,int*) ; 

__attribute__((used)) static enum dbg_status ecore_nvram_read(struct ecore_hwfn *p_hwfn,
										struct ecore_ptt *p_ptt,
										u32 nvram_offset_bytes,
										u32 nvram_size_bytes,
										u32 *ret_buf)
{
	u32 ret_mcp_resp, ret_mcp_param, ret_read_size, bytes_to_copy;
	s32 bytes_left = nvram_size_bytes;
	u32 read_offset = 0;

	DP_VERBOSE(p_hwfn, ECORE_MSG_DEBUG, "nvram_read: reading image of size %d bytes from NVRAM\n", nvram_size_bytes);

	do {
		bytes_to_copy = (bytes_left > MCP_DRV_NVM_BUF_LEN) ? MCP_DRV_NVM_BUF_LEN : bytes_left;

		/* Call NVRAM read command */
		if (ecore_mcp_nvm_rd_cmd(p_hwfn, p_ptt, DRV_MSG_CODE_NVM_READ_NVRAM, (nvram_offset_bytes + read_offset) | (bytes_to_copy << DRV_MB_PARAM_NVM_LEN_OFFSET), &ret_mcp_resp, &ret_mcp_param, &ret_read_size, (u32 *)((u8 *)ret_buf + read_offset)))
			return DBG_STATUS_NVRAM_READ_FAILED;

		/* Check response */
		if ((ret_mcp_resp  & FW_MSG_CODE_MASK) != FW_MSG_CODE_NVM_OK)
			return DBG_STATUS_NVRAM_READ_FAILED;

		/* Update read offset */
		read_offset += ret_read_size;
		bytes_left -= ret_read_size;
	} while (bytes_left > 0);

	return DBG_STATUS_OK;
}