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
typedef  int u_long ;
typedef  scalar_t__ u_int ;

/* Variables and functions */
 int /*<<< orphan*/  ASI_DTLB_DATA_ACCESS_REG ; 
 int /*<<< orphan*/  ASI_DTLB_TAG_READ_REG ; 
 int /*<<< orphan*/  ASI_ITLB_DATA_ACCESS_REG ; 
 int /*<<< orphan*/  ASI_ITLB_TAG_READ_REG ; 
 int TD_L ; 
 int TD_V ; 
 scalar_t__ TLB_CTX_KERNEL ; 
 int /*<<< orphan*/  TLB_DAR_FTLB ; 
 scalar_t__ TLB_DAR_SLOT (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  TLB_DAR_STLB ; 
 scalar_t__ TLB_TAR_CTX (int) ; 
 scalar_t__ ZEUS_FTLB_ENTRIES ; 
 scalar_t__ ZEUS_STLB_ENTRIES ; 
 int ldxa (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stxa_sync (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
zeus_tlb_flush_user(void)
{
	u_long data, tag;
	u_int i, slot;

	for (i = 0; i < ZEUS_FTLB_ENTRIES; i++) {
		slot = TLB_DAR_SLOT(TLB_DAR_FTLB, i);
		data = ldxa(slot, ASI_DTLB_DATA_ACCESS_REG);
		tag = ldxa(slot, ASI_DTLB_TAG_READ_REG);
		if ((data & TD_V) != 0 && (data & TD_L) == 0 &&
		    TLB_TAR_CTX(tag) != TLB_CTX_KERNEL)
			stxa_sync(slot, ASI_DTLB_DATA_ACCESS_REG, 0);
		data = ldxa(slot, ASI_ITLB_DATA_ACCESS_REG);
		tag = ldxa(slot, ASI_ITLB_TAG_READ_REG);
		if ((data & TD_V) != 0 && (data & TD_L) == 0 &&
		    TLB_TAR_CTX(tag) != TLB_CTX_KERNEL)
			stxa_sync(slot, ASI_ITLB_DATA_ACCESS_REG, 0);
	}
	for (i = 0; i < ZEUS_STLB_ENTRIES; i++) {
		slot = TLB_DAR_SLOT(TLB_DAR_STLB, i);
		data = ldxa(slot, ASI_DTLB_DATA_ACCESS_REG);
		tag = ldxa(slot, ASI_DTLB_TAG_READ_REG);
		if ((data & TD_V) != 0 && (data & TD_L) == 0 &&
		    TLB_TAR_CTX(tag) != TLB_CTX_KERNEL)
			stxa_sync(slot, ASI_DTLB_DATA_ACCESS_REG, 0);
		data = ldxa(slot, ASI_ITLB_DATA_ACCESS_REG);
		tag = ldxa(slot, ASI_ITLB_TAG_READ_REG);
		if ((data & TD_V) != 0 && (data & TD_L) == 0 &&
		    TLB_TAR_CTX(tag) != TLB_CTX_KERNEL)
			stxa_sync(slot, ASI_ITLB_DATA_ACCESS_REG, 0);
	}
}