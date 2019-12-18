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

/* Variables and functions */
 int /*<<< orphan*/  L2ARRSTAT0 ; 
 int /*<<< orphan*/  L2ARRSTAT1 ; 
 int /*<<< orphan*/  L2ARRSTAT2 ; 
 int /*<<< orphan*/  L2CPUSTAT ; 
 int /*<<< orphan*/  L2INT ; 
 int /*<<< orphan*/  L2LOG0 ; 
 int /*<<< orphan*/  L2LOG1 ; 
 int /*<<< orphan*/  L2LOG2 ; 
 int /*<<< orphan*/  L2LOG3 ; 
 int /*<<< orphan*/  L2LOG4 ; 
 int /*<<< orphan*/  L2LOG5 ; 
 int /*<<< orphan*/  L2MCK ; 
 int /*<<< orphan*/  L2PLBSTAT0 ; 
 int /*<<< orphan*/  L2PLBSTAT1 ; 
 int /*<<< orphan*/  L2RACSTAT0 ; 
 int /*<<< orphan*/  L2WACSTAT0 ; 
 int /*<<< orphan*/  L2WACSTAT1 ; 
 int /*<<< orphan*/  L2WACSTAT2 ; 
 int /*<<< orphan*/  L2WDFSTAT ; 
 int /*<<< orphan*/  mfl2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

__attribute__((used)) static void l2regs(void)
{
	pr_err("L2 Controller:\n");
	pr_err("MCK:      0x%08x\n", mfl2(L2MCK));
	pr_err("INT:      0x%08x\n", mfl2(L2INT));
	pr_err("PLBSTAT0: 0x%08x\n", mfl2(L2PLBSTAT0));
	pr_err("PLBSTAT1: 0x%08x\n", mfl2(L2PLBSTAT1));
	pr_err("ARRSTAT0: 0x%08x\n", mfl2(L2ARRSTAT0));
	pr_err("ARRSTAT1: 0x%08x\n", mfl2(L2ARRSTAT1));
	pr_err("ARRSTAT2: 0x%08x\n", mfl2(L2ARRSTAT2));
	pr_err("CPUSTAT:  0x%08x\n", mfl2(L2CPUSTAT));
	pr_err("RACSTAT0: 0x%08x\n", mfl2(L2RACSTAT0));
	pr_err("WACSTAT0: 0x%08x\n", mfl2(L2WACSTAT0));
	pr_err("WACSTAT1: 0x%08x\n", mfl2(L2WACSTAT1));
	pr_err("WACSTAT2: 0x%08x\n", mfl2(L2WACSTAT2));
	pr_err("WDFSTAT:  0x%08x\n", mfl2(L2WDFSTAT));
	pr_err("LOG0:     0x%08x\n", mfl2(L2LOG0));
	pr_err("LOG1:     0x%08x\n", mfl2(L2LOG1));
	pr_err("LOG2:     0x%08x\n", mfl2(L2LOG2));
	pr_err("LOG3:     0x%08x\n", mfl2(L2LOG3));
	pr_err("LOG4:     0x%08x\n", mfl2(L2LOG4));
	pr_err("LOG5:     0x%08x\n", mfl2(L2LOG5));
}