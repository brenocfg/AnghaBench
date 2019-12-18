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
 int /*<<< orphan*/  CCM_CCGRx (int) ; 
 int /*<<< orphan*/  CCM_CSCDR1 ; 
 int /*<<< orphan*/  CCM_CSCDR2 ; 
 int /*<<< orphan*/  CCM_CSCDR3 ; 
 int /*<<< orphan*/  CCM_CSCMR1 ; 
 int /*<<< orphan*/  CCM_CSCMR2 ; 
 void** ccgr ; 
 void* cscdr1 ; 
 void* cscdr2 ; 
 void* cscdr3 ; 
 void* cscmr1 ; 
 void* cscmr2 ; 
 void* readl_relaxed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vf610_clk_suspend(void)
{
	int i;

	cscmr1 = readl_relaxed(CCM_CSCMR1);
	cscmr2 = readl_relaxed(CCM_CSCMR2);

	cscdr1 = readl_relaxed(CCM_CSCDR1);
	cscdr2 = readl_relaxed(CCM_CSCDR2);
	cscdr3 = readl_relaxed(CCM_CSCDR3);

	for (i = 0; i < 12; i++)
		ccgr[i] = readl_relaxed(CCM_CCGRx(i));

	return 0;
}