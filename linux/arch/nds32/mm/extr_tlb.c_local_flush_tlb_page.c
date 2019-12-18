#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {TYPE_2__* vm_mm; } ;
struct TYPE_3__ {unsigned long id; } ;
struct TYPE_4__ {TYPE_1__ context; } ;

/* Variables and functions */
 int /*<<< orphan*/  NDS32_SR_TLB_MISC ; 
 unsigned long TLB_MISC_mskCID ; 
 int /*<<< orphan*/  __nds32__isb () ; 
 unsigned long __nds32__mfsr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __nds32__mtsr_dsb (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __nds32__tlbop_inv (unsigned long) ; 
 int /*<<< orphan*/  cid_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void local_flush_tlb_page(struct vm_area_struct *vma, unsigned long addr)
{
	unsigned long flags, ocid, ncid;

	spin_lock_irqsave(&cid_lock, flags);
	ocid = __nds32__mfsr(NDS32_SR_TLB_MISC);
	ncid = (ocid & ~TLB_MISC_mskCID) | vma->vm_mm->context.id;
	__nds32__mtsr_dsb(ncid, NDS32_SR_TLB_MISC);
	__nds32__tlbop_inv(addr);
	__nds32__isb();
	__nds32__mtsr_dsb(ocid, NDS32_SR_TLB_MISC);
	spin_unlock_irqrestore(&cid_lock, flags);
}