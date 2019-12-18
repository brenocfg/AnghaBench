#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned long sparc64_ctx_val; } ;
struct mm_struct {TYPE_1__ context; } ;

/* Variables and functions */
 int CTX_NR_BITS ; 
 int CTX_NR_MASK ; 
 unsigned long CTX_PGSZ_MASK ; 
 int /*<<< orphan*/  CTX_VALID (TYPE_1__) ; 
 int CTX_VERSION_MASK ; 
 int /*<<< orphan*/  cpumask_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctx_alloc_lock ; 
 unsigned long find_next_zero_bit (unsigned long*,unsigned long,int) ; 
 int /*<<< orphan*/  mm_cpumask (struct mm_struct*) ; 
 unsigned long* mmu_context_bmap ; 
 int /*<<< orphan*/  mmu_context_wrap () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int tlb_context_cache ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void get_new_mmu_context(struct mm_struct *mm)
{
	unsigned long ctx, new_ctx;
	unsigned long orig_pgsz_bits;

	spin_lock(&ctx_alloc_lock);
retry:
	/* wrap might have happened, test again if our context became valid */
	if (unlikely(CTX_VALID(mm->context)))
		goto out;
	orig_pgsz_bits = (mm->context.sparc64_ctx_val & CTX_PGSZ_MASK);
	ctx = (tlb_context_cache + 1) & CTX_NR_MASK;
	new_ctx = find_next_zero_bit(mmu_context_bmap, 1 << CTX_NR_BITS, ctx);
	if (new_ctx >= (1 << CTX_NR_BITS)) {
		new_ctx = find_next_zero_bit(mmu_context_bmap, ctx, 1);
		if (new_ctx >= ctx) {
			mmu_context_wrap();
			goto retry;
		}
	}
	if (mm->context.sparc64_ctx_val)
		cpumask_clear(mm_cpumask(mm));
	mmu_context_bmap[new_ctx>>6] |= (1UL << (new_ctx & 63));
	new_ctx |= (tlb_context_cache & CTX_VERSION_MASK);
	tlb_context_cache = new_ctx;
	mm->context.sparc64_ctx_val = new_ctx | orig_pgsz_bits;
out:
	spin_unlock(&ctx_alloc_lock);
}