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
typedef  scalar_t__ u32 ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int dummy; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct ecore_hwfn*,char*) ; 
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  DRV_MSG_CODE_MCP_HALT ; 
 int ECORE_BUSY ; 
 scalar_t__ ECORE_MCP_HALT_MAX_RETRIES ; 
 int /*<<< orphan*/  ECORE_MCP_HALT_SLEEP_MS ; 
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  MCP_REG_CPU_MODE ; 
 int /*<<< orphan*/  MCP_REG_CPU_STATE ; 
 scalar_t__ MCP_REG_CPU_STATE_SOFT_HALTED ; 
 int /*<<< orphan*/  OSAL_MSLEEP (int /*<<< orphan*/ ) ; 
 int ecore_mcp_cmd (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  ecore_mcp_cmd_set_blocking (struct ecore_hwfn*,int) ; 
 scalar_t__ ecore_rd (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ) ; 

enum _ecore_status_t ecore_mcp_halt(struct ecore_hwfn *p_hwfn,
				    struct ecore_ptt *p_ptt)
{
	u32 resp = 0, param = 0, cpu_state, cnt = 0;
	enum _ecore_status_t rc;

	rc = ecore_mcp_cmd(p_hwfn, p_ptt, DRV_MSG_CODE_MCP_HALT, 0, &resp,
			   &param);
	if (rc != ECORE_SUCCESS) {
		DP_ERR(p_hwfn, "MCP response failure, aborting\n");
		return rc;
	}

	do {
		OSAL_MSLEEP(ECORE_MCP_HALT_SLEEP_MS);
		cpu_state = ecore_rd(p_hwfn, p_ptt, MCP_REG_CPU_STATE);
		if (cpu_state & MCP_REG_CPU_STATE_SOFT_HALTED)
			break;
	} while (++cnt < ECORE_MCP_HALT_MAX_RETRIES);

	if (cnt == ECORE_MCP_HALT_MAX_RETRIES) {
		DP_NOTICE(p_hwfn, false,
			  "Failed to halt the MCP [CPU_MODE = 0x%08x, CPU_STATE = 0x%08x]\n",
			  ecore_rd(p_hwfn, p_ptt, MCP_REG_CPU_MODE), cpu_state);
		return ECORE_BUSY;
	}

	ecore_mcp_cmd_set_blocking(p_hwfn, true);

	return ECORE_SUCCESS;
}