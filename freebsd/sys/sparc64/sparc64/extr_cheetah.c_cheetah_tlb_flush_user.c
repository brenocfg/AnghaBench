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
typedef  int /*<<< orphan*/  register_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASI_DTLB_DATA_ACCESS_REG ; 
 int /*<<< orphan*/  ASI_DTLB_TAG_READ_REG ; 
 int /*<<< orphan*/  ASI_ITLB_DATA_ACCESS_REG ; 
 int /*<<< orphan*/  ASI_ITLB_TAG_READ_REG ; 
 scalar_t__ CHEETAH_DT512_ENTRIES ; 
 scalar_t__ CHEETAH_IT128_ENTRIES ; 
 scalar_t__ CHEETAH_IT512_ENTRIES ; 
 scalar_t__ CHEETAH_T16_ENTRIES ; 
 scalar_t__ CPU_IMPL_ULTRASPARCIVp ; 
 scalar_t__ PCPU_GET (int /*<<< orphan*/ ) ; 
 int TD_L ; 
 int TD_V ; 
 scalar_t__ TLB_CTX_KERNEL ; 
 int /*<<< orphan*/  TLB_DAR_DT512_0 ; 
 int /*<<< orphan*/  TLB_DAR_DT512_1 ; 
 int /*<<< orphan*/  TLB_DAR_IT128 ; 
 int /*<<< orphan*/  TLB_DAR_IT512 ; 
 scalar_t__ TLB_DAR_SLOT (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  TLB_DAR_T16 ; 
 scalar_t__ TLB_TAR_CTX (int) ; 
 int /*<<< orphan*/  impl ; 
 int /*<<< orphan*/  intr_disable () ; 
 int /*<<< orphan*/  intr_restore (int /*<<< orphan*/ ) ; 
 int ldxa (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stxa_sync (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
cheetah_tlb_flush_user(void)
{
	u_long data, tag;
	register_t s;
	u_int i, slot;

	/*
	 * We read ASI_{D,I}TLB_DATA_ACCESS_REG twice back-to-back in order
	 * to work around errata of USIII and beyond.
	 */
	for (i = 0; i < CHEETAH_T16_ENTRIES; i++) {
		slot = TLB_DAR_SLOT(TLB_DAR_T16, i);
		s = intr_disable();
		(void)ldxa(slot, ASI_DTLB_DATA_ACCESS_REG);
		data = ldxa(slot, ASI_DTLB_DATA_ACCESS_REG);
		intr_restore(s);
		tag = ldxa(slot, ASI_DTLB_TAG_READ_REG);
		if ((data & TD_V) != 0 && (data & TD_L) == 0 &&
		    TLB_TAR_CTX(tag) != TLB_CTX_KERNEL)
			stxa_sync(slot, ASI_DTLB_DATA_ACCESS_REG, 0);
		s = intr_disable();
		(void)ldxa(slot, ASI_ITLB_DATA_ACCESS_REG);
		data = ldxa(slot, ASI_ITLB_DATA_ACCESS_REG);
		intr_restore(s);
		tag = ldxa(slot, ASI_ITLB_TAG_READ_REG);
		if ((data & TD_V) != 0 && (data & TD_L) == 0 &&
		    TLB_TAR_CTX(tag) != TLB_CTX_KERNEL)
			stxa_sync(slot, ASI_ITLB_DATA_ACCESS_REG, 0);
	}
	for (i = 0; i < CHEETAH_DT512_ENTRIES; i++) {
		slot = TLB_DAR_SLOT(TLB_DAR_DT512_0, i);
		s = intr_disable();
		(void)ldxa(slot, ASI_DTLB_DATA_ACCESS_REG);
		data = ldxa(slot, ASI_DTLB_DATA_ACCESS_REG);
		intr_restore(s);
		tag = ldxa(slot, ASI_DTLB_TAG_READ_REG);
		if ((data & TD_V) != 0 && TLB_TAR_CTX(tag) != TLB_CTX_KERNEL)
			stxa_sync(slot, ASI_DTLB_DATA_ACCESS_REG, 0);
		slot = TLB_DAR_SLOT(TLB_DAR_DT512_1, i);
		s = intr_disable();
		(void)ldxa(slot, ASI_ITLB_DATA_ACCESS_REG);
		data = ldxa(slot, ASI_DTLB_DATA_ACCESS_REG);
		intr_restore(s);
		tag = ldxa(slot, ASI_DTLB_TAG_READ_REG);
		if ((data & TD_V) != 0 && TLB_TAR_CTX(tag) != TLB_CTX_KERNEL)
			stxa_sync(slot, ASI_DTLB_DATA_ACCESS_REG, 0);
	}
	if (PCPU_GET(impl) == CPU_IMPL_ULTRASPARCIVp) {
		for (i = 0; i < CHEETAH_IT512_ENTRIES; i++) {
			slot = TLB_DAR_SLOT(TLB_DAR_IT512, i);
			s = intr_disable();
			(void)ldxa(slot, ASI_ITLB_DATA_ACCESS_REG);
			data = ldxa(slot, ASI_ITLB_DATA_ACCESS_REG);
			intr_restore(s);
			tag = ldxa(slot, ASI_ITLB_TAG_READ_REG);
			if ((data & TD_V) != 0 &&
			    TLB_TAR_CTX(tag) != TLB_CTX_KERNEL)
				stxa_sync(slot, ASI_ITLB_DATA_ACCESS_REG, 0);
		}
	} else {
		for (i = 0; i < CHEETAH_IT128_ENTRIES; i++) {
			slot = TLB_DAR_SLOT(TLB_DAR_IT128, i);
			s = intr_disable();
			(void)ldxa(slot, ASI_ITLB_DATA_ACCESS_REG);
			data = ldxa(slot, ASI_ITLB_DATA_ACCESS_REG);
			tag = ldxa(slot, ASI_ITLB_TAG_READ_REG);
			intr_restore(s);
			if ((data & TD_V) != 0 &&
			    TLB_TAR_CTX(tag) != TLB_CTX_KERNEL)
				stxa_sync(slot, ASI_ITLB_DATA_ACCESS_REG, 0);
		}
	}
}