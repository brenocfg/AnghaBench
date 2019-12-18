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
struct tsb {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; TYPE_1__* tsb_block; } ;
struct mm_struct {TYPE_2__ context; } ;
typedef  int gfp_t ;
struct TYPE_3__ {unsigned long tsb_rss_limit; int tsb_reg_val; int tsb_nentries; struct tsb* tsb; } ;

/* Variables and functions */
 int GFP_KERNEL ; 
 unsigned long MAX_ORDER ; 
 unsigned long MM_TSB_BASE ; 
 unsigned long PAGE_SHIFT ; 
 unsigned long PAGE_SIZE ; 
 unsigned long REAL_HPAGE_SHIFT ; 
 int __GFP_NORETRY ; 
 int __GFP_NOWARN ; 
 unsigned long __pa (unsigned long) ; 
 scalar_t__ cheetah_plus ; 
 scalar_t__ hypervisor ; 
 struct tsb* kmem_cache_alloc_node (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct tsb*) ; 
 int /*<<< orphan*/  numa_node_id () ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  setup_tsb_params (struct mm_struct*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  smp_tsb_sync (struct mm_struct*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ tlb_type ; 
 int /*<<< orphan*/ * tsb_caches ; 
 int /*<<< orphan*/  tsb_context_switch (struct mm_struct*) ; 
 int /*<<< orphan*/  tsb_init (struct tsb*,unsigned long) ; 
 unsigned long tsb_size_to_rss_limit (unsigned long) ; 
 scalar_t__ unlikely (int) ; 

void tsb_grow(struct mm_struct *mm, unsigned long tsb_index, unsigned long rss)
{
	unsigned long max_tsb_size = 1 * 1024 * 1024;
	unsigned long new_size, old_size, flags;
	struct tsb *old_tsb, *new_tsb;
	unsigned long new_cache_index, old_cache_index;
	unsigned long new_rss_limit;
	gfp_t gfp_flags;

	if (max_tsb_size > (PAGE_SIZE << MAX_ORDER))
		max_tsb_size = (PAGE_SIZE << MAX_ORDER);

	new_cache_index = 0;
	for (new_size = 8192; new_size < max_tsb_size; new_size <<= 1UL) {
		new_rss_limit = tsb_size_to_rss_limit(new_size);
		if (new_rss_limit > rss)
			break;
		new_cache_index++;
	}

	if (new_size == max_tsb_size)
		new_rss_limit = ~0UL;

retry_tsb_alloc:
	gfp_flags = GFP_KERNEL;
	if (new_size > (PAGE_SIZE * 2))
		gfp_flags |= __GFP_NOWARN | __GFP_NORETRY;

	new_tsb = kmem_cache_alloc_node(tsb_caches[new_cache_index],
					gfp_flags, numa_node_id());
	if (unlikely(!new_tsb)) {
		/* Not being able to fork due to a high-order TSB
		 * allocation failure is very bad behavior.  Just back
		 * down to a 0-order allocation and force no TSB
		 * growing for this address space.
		 */
		if (mm->context.tsb_block[tsb_index].tsb == NULL &&
		    new_cache_index > 0) {
			new_cache_index = 0;
			new_size = 8192;
			new_rss_limit = ~0UL;
			goto retry_tsb_alloc;
		}

		/* If we failed on a TSB grow, we are under serious
		 * memory pressure so don't try to grow any more.
		 */
		if (mm->context.tsb_block[tsb_index].tsb != NULL)
			mm->context.tsb_block[tsb_index].tsb_rss_limit = ~0UL;
		return;
	}

	/* Mark all tags as invalid.  */
	tsb_init(new_tsb, new_size);

	/* Ok, we are about to commit the changes.  If we are
	 * growing an existing TSB the locking is very tricky,
	 * so WATCH OUT!
	 *
	 * We have to hold mm->context.lock while committing to the
	 * new TSB, this synchronizes us with processors in
	 * flush_tsb_user() and switch_mm() for this address space.
	 *
	 * But even with that lock held, processors run asynchronously
	 * accessing the old TSB via TLB miss handling.  This is OK
	 * because those actions are just propagating state from the
	 * Linux page tables into the TSB, page table mappings are not
	 * being changed.  If a real fault occurs, the processor will
	 * synchronize with us when it hits flush_tsb_user(), this is
	 * also true for the case where vmscan is modifying the page
	 * tables.  The only thing we need to be careful with is to
	 * skip any locked TSB entries during copy_tsb().
	 *
	 * When we finish committing to the new TSB, we have to drop
	 * the lock and ask all other cpus running this address space
	 * to run tsb_context_switch() to see the new TSB table.
	 */
	spin_lock_irqsave(&mm->context.lock, flags);

	old_tsb = mm->context.tsb_block[tsb_index].tsb;
	old_cache_index =
		(mm->context.tsb_block[tsb_index].tsb_reg_val & 0x7UL);
	old_size = (mm->context.tsb_block[tsb_index].tsb_nentries *
		    sizeof(struct tsb));


	/* Handle multiple threads trying to grow the TSB at the same time.
	 * One will get in here first, and bump the size and the RSS limit.
	 * The others will get in here next and hit this check.
	 */
	if (unlikely(old_tsb &&
		     (rss < mm->context.tsb_block[tsb_index].tsb_rss_limit))) {
		spin_unlock_irqrestore(&mm->context.lock, flags);

		kmem_cache_free(tsb_caches[new_cache_index], new_tsb);
		return;
	}

	mm->context.tsb_block[tsb_index].tsb_rss_limit = new_rss_limit;

	if (old_tsb) {
		extern void copy_tsb(unsigned long old_tsb_base,
				     unsigned long old_tsb_size,
				     unsigned long new_tsb_base,
				     unsigned long new_tsb_size,
				     unsigned long page_size_shift);
		unsigned long old_tsb_base = (unsigned long) old_tsb;
		unsigned long new_tsb_base = (unsigned long) new_tsb;

		if (tlb_type == cheetah_plus || tlb_type == hypervisor) {
			old_tsb_base = __pa(old_tsb_base);
			new_tsb_base = __pa(new_tsb_base);
		}
		copy_tsb(old_tsb_base, old_size, new_tsb_base, new_size,
			tsb_index == MM_TSB_BASE ?
			PAGE_SHIFT : REAL_HPAGE_SHIFT);
	}

	mm->context.tsb_block[tsb_index].tsb = new_tsb;
	setup_tsb_params(mm, tsb_index, new_size);

	spin_unlock_irqrestore(&mm->context.lock, flags);

	/* If old_tsb is NULL, we're being invoked for the first time
	 * from init_new_context().
	 */
	if (old_tsb) {
		/* Reload it on the local cpu.  */
		tsb_context_switch(mm);

		/* Now force other processors to do the same.  */
		preempt_disable();
		smp_tsb_sync(mm);
		preempt_enable();

		/* Now it is safe to free the old tsb.  */
		kmem_cache_free(tsb_caches[old_cache_index], old_tsb);
	}
}