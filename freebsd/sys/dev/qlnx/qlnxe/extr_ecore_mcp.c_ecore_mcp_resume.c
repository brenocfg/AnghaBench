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
typedef  int u32 ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int dummy; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*,int,int) ; 
 int ECORE_BUSY ; 
 int /*<<< orphan*/  ECORE_MCP_RESUME_SLEEP_MS ; 
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  MCP_REG_CPU_MODE ; 
 int MCP_REG_CPU_MODE_SOFT_HALT ; 
 int /*<<< orphan*/  MCP_REG_CPU_STATE ; 
 int MCP_REG_CPU_STATE_SOFT_HALTED ; 
 int /*<<< orphan*/  OSAL_MSLEEP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_mcp_cmd_set_blocking (struct ecore_hwfn*,int) ; 
 int ecore_rd (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_wr (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int) ; 

enum _ecore_status_t ecore_mcp_resume(struct ecore_hwfn *p_hwfn,
				      struct ecore_ptt *p_ptt)
{
	u32 cpu_mode, cpu_state;

	ecore_wr(p_hwfn, p_ptt, MCP_REG_CPU_STATE, 0xffffffff);

	cpu_mode = ecore_rd(p_hwfn, p_ptt, MCP_REG_CPU_MODE);
	cpu_mode &= ~MCP_REG_CPU_MODE_SOFT_HALT;
	ecore_wr(p_hwfn, p_ptt, MCP_REG_CPU_MODE, cpu_mode);

	OSAL_MSLEEP(ECORE_MCP_RESUME_SLEEP_MS);
	cpu_state = ecore_rd(p_hwfn, p_ptt, MCP_REG_CPU_STATE);

	if (cpu_state & MCP_REG_CPU_STATE_SOFT_HALTED) {
		DP_NOTICE(p_hwfn, false,
			  "Failed to resume the MCP [CPU_MODE = 0x%08x, CPU_STATE = 0x%08x]\n",
			  cpu_mode, cpu_state);
		return ECORE_BUSY;
	}

	ecore_mcp_cmd_set_blocking(p_hwfn, false);

	return ECORE_SUCCESS;
}