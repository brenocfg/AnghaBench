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
typedef  int /*<<< orphan*/  u32 ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int /*<<< orphan*/  p_dev; } ;

/* Variables and functions */
 scalar_t__ CHIP_REV_IS_SLOW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ECORE_MSG_HW ; 
 int /*<<< orphan*/  OSAL_UDELAY (int) ; 
 int /*<<< orphan*/  OSAL_WARN (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WR (struct ecore_hwfn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_is_reg_fifo_empty (struct ecore_hwfn*,struct ecore_ptt*) ; 
 int /*<<< orphan*/  ecore_set_ptt (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ) ; 

void ecore_wr(struct ecore_hwfn *p_hwfn, struct ecore_ptt *p_ptt, u32 hw_addr,
	      u32 val)
{
	bool prev_fifo_err;
	u32 bar_addr;

	prev_fifo_err = !ecore_is_reg_fifo_empty(p_hwfn, p_ptt);

	bar_addr = ecore_set_ptt(p_hwfn, p_ptt, hw_addr);
	REG_WR(p_hwfn, bar_addr, val);
	DP_VERBOSE(p_hwfn, ECORE_MSG_HW,
		   "bar_addr 0x%x, hw_addr 0x%x, val 0x%x\n",
		   bar_addr, hw_addr, val);

#ifndef ASIC_ONLY
	if (CHIP_REV_IS_SLOW(p_hwfn->p_dev))
		OSAL_UDELAY(100);
#endif

	OSAL_WARN(!prev_fifo_err && !ecore_is_reg_fifo_empty(p_hwfn, p_ptt),
		  "reg_fifo error was caused by a call to ecore_wr(0x%x, 0x%x)\n",
		  hw_addr, val);
}