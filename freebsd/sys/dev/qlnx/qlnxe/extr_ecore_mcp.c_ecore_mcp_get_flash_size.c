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
struct ecore_hwfn {int /*<<< orphan*/  p_dev; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 scalar_t__ CHIP_REV_IS_EMUL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*) ; 
 int ECORE_INVAL ; 
 int ECORE_SUCCESS ; 
 scalar_t__ IS_VF (int /*<<< orphan*/ ) ; 
 int MCP_BYTES_PER_MBIT_OFFSET ; 
 int /*<<< orphan*/  MCP_REG_NVM_CFG4 ; 
 int MCP_REG_NVM_CFG4_FLASH_SIZE ; 
 int MCP_REG_NVM_CFG4_FLASH_SIZE_SHIFT ; 
 int ecore_rd (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ) ; 

enum _ecore_status_t ecore_mcp_get_flash_size(struct ecore_hwfn *p_hwfn,
					      struct ecore_ptt *p_ptt,
					      u32 *p_flash_size)
{
	u32 flash_size;

#ifndef ASIC_ONLY
	if (CHIP_REV_IS_EMUL(p_hwfn->p_dev)) {
		DP_NOTICE(p_hwfn, false, "Emulation - can't get flash size\n");
		return ECORE_INVAL;
	}
#endif

	if (IS_VF(p_hwfn->p_dev))
		return ECORE_INVAL;

	flash_size = ecore_rd(p_hwfn, p_ptt, MCP_REG_NVM_CFG4);
	flash_size = (flash_size & MCP_REG_NVM_CFG4_FLASH_SIZE) >>
		     MCP_REG_NVM_CFG4_FLASH_SIZE_SHIFT;
	flash_size = (1 << (flash_size + MCP_BYTES_PER_MBIT_OFFSET));

	*p_flash_size = flash_size;

	return ECORE_SUCCESS;
}