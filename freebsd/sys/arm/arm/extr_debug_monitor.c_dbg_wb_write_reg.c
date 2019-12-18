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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_WB_BCR ; 
 int /*<<< orphan*/  DBG_WB_BVR ; 
 int /*<<< orphan*/  DBG_WB_WCR ; 
 int /*<<< orphan*/  DBG_WB_WVR ; 
 int OP2_SHIFT ; 
 int /*<<< orphan*/  SWITCH_CASES_WRITE_WB_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  db_printf (char*,int) ; 
 int /*<<< orphan*/  isb () ; 

__attribute__((used)) static void
dbg_wb_write_reg(int reg, int n, uint32_t val)
{

	switch (reg + n) {
	SWITCH_CASES_WRITE_WB_REG(DBG_WB_WVR, val);
	SWITCH_CASES_WRITE_WB_REG(DBG_WB_WCR, val);
	SWITCH_CASES_WRITE_WB_REG(DBG_WB_BVR, val);
	SWITCH_CASES_WRITE_WB_REG(DBG_WB_BCR, val);
	default:
		db_printf(
		    "trying to write to CP14 reg. using wrong opc2 %d\n",
		    reg >> OP2_SHIFT);
	}
	isb();
}