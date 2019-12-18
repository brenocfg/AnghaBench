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
struct tlb_batch {int /*<<< orphan*/  hugepage_shift; struct mm_struct* mm; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; TYPE_1__* tsb_block; } ;
struct mm_struct {TYPE_2__ context; } ;
struct TYPE_3__ {unsigned long tsb_nentries; scalar_t__ tsb; } ;

/* Variables and functions */
 size_t MM_TSB_BASE ; 
 size_t MM_TSB_HUGE ; 
 int /*<<< orphan*/  PAGE_SHIFT ; 
 int /*<<< orphan*/  REAL_HPAGE_SHIFT ; 
 int /*<<< orphan*/  __flush_huge_tsb_one (struct tlb_batch*,int /*<<< orphan*/ ,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __flush_tsb_one (struct tlb_batch*,int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 unsigned long __pa (unsigned long) ; 
 scalar_t__ cheetah_plus ; 
 scalar_t__ hypervisor ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ tlb_type ; 

void flush_tsb_user(struct tlb_batch *tb)
{
	struct mm_struct *mm = tb->mm;
	unsigned long nentries, base, flags;

	spin_lock_irqsave(&mm->context.lock, flags);

	if (tb->hugepage_shift < REAL_HPAGE_SHIFT) {
		base = (unsigned long) mm->context.tsb_block[MM_TSB_BASE].tsb;
		nentries = mm->context.tsb_block[MM_TSB_BASE].tsb_nentries;
		if (tlb_type == cheetah_plus || tlb_type == hypervisor)
			base = __pa(base);
		if (tb->hugepage_shift == PAGE_SHIFT)
			__flush_tsb_one(tb, PAGE_SHIFT, base, nentries);
#if defined(CONFIG_HUGETLB_PAGE)
		else
			__flush_huge_tsb_one(tb, PAGE_SHIFT, base, nentries,
					     tb->hugepage_shift);
#endif
	}
#if defined(CONFIG_HUGETLB_PAGE) || defined(CONFIG_TRANSPARENT_HUGEPAGE)
	else if (mm->context.tsb_block[MM_TSB_HUGE].tsb) {
		base = (unsigned long) mm->context.tsb_block[MM_TSB_HUGE].tsb;
		nentries = mm->context.tsb_block[MM_TSB_HUGE].tsb_nentries;
		if (tlb_type == cheetah_plus || tlb_type == hypervisor)
			base = __pa(base);
		__flush_huge_tsb_one(tb, REAL_HPAGE_SHIFT, base, nentries,
				     tb->hugepage_shift);
	}
#endif
	spin_unlock_irqrestore(&mm->context.lock, flags);
}