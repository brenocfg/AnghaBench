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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_WB_BCR ; 
 int /*<<< orphan*/  DBG_WB_BVR ; 
 int /*<<< orphan*/  DBG_WB_WCR ; 
 int /*<<< orphan*/  DBG_WB_WVR ; 
 int OP2_SHIFT ; 
 int /*<<< orphan*/  SWITCH_CASES_READ_WB_REG (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  db_printf (char*,int) ; 

__attribute__((used)) static uint32_t
dbg_wb_read_reg(int reg, int n)
{
	uint32_t val;

	val = 0;

	switch (reg + n) {
	SWITCH_CASES_READ_WB_REG(DBG_WB_WVR, val);
	SWITCH_CASES_READ_WB_REG(DBG_WB_WCR, val);
	SWITCH_CASES_READ_WB_REG(DBG_WB_BVR, val);
	SWITCH_CASES_READ_WB_REG(DBG_WB_BCR, val);
	default:
		db_printf(
		    "trying to read from CP14 reg. using wrong opc2 %d\n",
		    reg >> OP2_SHIFT);
	}

	return (val);
}