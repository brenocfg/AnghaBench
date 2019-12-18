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
struct ecore_ptt {int dummy; } ;
struct ecore_mdump_cmd_params {int /*<<< orphan*/  cmd; } ;
struct ecore_hwfn {int dummy; } ;
typedef  int /*<<< orphan*/  mdump_cmd_params ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_MSG_CODE_MDUMP_TRIGGER ; 
 int /*<<< orphan*/  OSAL_MEM_ZERO (struct ecore_mdump_cmd_params*,int) ; 
 int ecore_mcp_mdump_cmd (struct ecore_hwfn*,struct ecore_ptt*,struct ecore_mdump_cmd_params*) ; 

enum _ecore_status_t ecore_mcp_mdump_trigger(struct ecore_hwfn *p_hwfn,
					     struct ecore_ptt *p_ptt)
{
	struct ecore_mdump_cmd_params mdump_cmd_params;

	OSAL_MEM_ZERO(&mdump_cmd_params, sizeof(mdump_cmd_params));
	mdump_cmd_params.cmd = DRV_MSG_CODE_MDUMP_TRIGGER;

	return ecore_mcp_mdump_cmd(p_hwfn, p_ptt, &mdump_cmd_params);
}