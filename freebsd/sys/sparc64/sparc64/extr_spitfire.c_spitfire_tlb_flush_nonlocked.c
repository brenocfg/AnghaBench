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
typedef  scalar_t__ u_int ;

/* Variables and functions */
 int /*<<< orphan*/  ASI_DTLB_DATA_ACCESS_REG ; 
 int /*<<< orphan*/  ASI_ITLB_DATA_ACCESS_REG ; 
 scalar_t__ SPITFIRE_TLB_ENTRIES ; 
 int TD_L ; 
 scalar_t__ TLB_DAR_SLOT (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  TLB_DAR_T32 ; 
 int ldxa (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stxa_sync (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
spitfire_tlb_flush_nonlocked(void)
{
	u_int i;
	u_int slot;

	for (i = 0; i < SPITFIRE_TLB_ENTRIES; i++) {
		slot = TLB_DAR_SLOT(TLB_DAR_T32, i);
		if ((ldxa(slot, ASI_DTLB_DATA_ACCESS_REG) & TD_L) == 0)
			stxa_sync(slot, ASI_DTLB_DATA_ACCESS_REG, 0);
		if ((ldxa(slot, ASI_ITLB_DATA_ACCESS_REG) & TD_L) == 0)
			stxa_sync(slot, ASI_ITLB_DATA_ACCESS_REG, 0);
	}
}