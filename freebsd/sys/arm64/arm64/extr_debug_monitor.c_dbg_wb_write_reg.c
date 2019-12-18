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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_REG_BASE_BCR ; 
 int /*<<< orphan*/  DBG_REG_BASE_BVR ; 
 int /*<<< orphan*/  DBG_REG_BASE_WCR ; 
 int /*<<< orphan*/  DBG_REG_BASE_WVR ; 
 int /*<<< orphan*/  DBG_WB_BCR ; 
 int /*<<< orphan*/  DBG_WB_BVR ; 
 int /*<<< orphan*/  DBG_WB_WCR ; 
 int /*<<< orphan*/  DBG_WB_WVR ; 
 int /*<<< orphan*/  SWITCH_CASES_WRITE_WB_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isb () ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static void
dbg_wb_write_reg(int reg, int n, uint64_t val)
{
	switch (reg + n) {
	SWITCH_CASES_WRITE_WB_REG(DBG_WB_WVR, DBG_REG_BASE_WVR, val);
	SWITCH_CASES_WRITE_WB_REG(DBG_WB_WCR, DBG_REG_BASE_WCR, val);
	SWITCH_CASES_WRITE_WB_REG(DBG_WB_BVR, DBG_REG_BASE_BVR, val);
	SWITCH_CASES_WRITE_WB_REG(DBG_WB_BCR, DBG_REG_BASE_BCR, val);
	default:
		printf("trying to write to wrong debug register %d\n", n);
		return;
	}
	isb();
}