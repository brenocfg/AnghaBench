#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  size_t u32 ;
struct TYPE_4__ {scalar_t__ ctx_id; int /*<<< orphan*/  tlb_gen; } ;
struct mm_struct {TYPE_1__ context; } ;
struct flush_tlb_info {scalar_t__ new_tlb_gen; unsigned long end; unsigned long start; unsigned long stride_shift; } ;
typedef  enum tlb_flush_reason { ____Placeholder_tlb_flush_reason } tlb_flush_reason ;
struct TYPE_6__ {TYPE_2__* ctxs; int /*<<< orphan*/  is_lazy; int /*<<< orphan*/  loaded_mm_asid; int /*<<< orphan*/  loaded_mm; } ;
struct TYPE_5__ {int /*<<< orphan*/  tlb_gen; int /*<<< orphan*/  ctx_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  NR_TLB_LOCAL_FLUSH_ALL ; 
 int /*<<< orphan*/  NR_TLB_LOCAL_FLUSH_ONE ; 
 unsigned long TLB_FLUSH_ALL ; 
 int /*<<< orphan*/  VM_WARN_ON (int) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  __flush_tlb_one_user (unsigned long) ; 
 scalar_t__ atomic64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  count_vm_tlb_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  count_vm_tlb_events (int /*<<< orphan*/ ,unsigned long) ; 
 TYPE_3__ cpu_tlbstate ; 
 struct mm_struct init_mm ; 
 int /*<<< orphan*/  irqs_disabled () ; 
 int /*<<< orphan*/  local_flush_tlb () ; 
 int /*<<< orphan*/  switch_mm_irqs_off (int /*<<< orphan*/ *,struct mm_struct*,int /*<<< orphan*/ *) ; 
 scalar_t__ this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  this_cpu_write (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  trace_tlb_flush (int,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void flush_tlb_func_common(const struct flush_tlb_info *f,
				  bool local, enum tlb_flush_reason reason)
{
	/*
	 * We have three different tlb_gen values in here.  They are:
	 *
	 * - mm_tlb_gen:     the latest generation.
	 * - local_tlb_gen:  the generation that this CPU has already caught
	 *                   up to.
	 * - f->new_tlb_gen: the generation that the requester of the flush
	 *                   wants us to catch up to.
	 */
	struct mm_struct *loaded_mm = this_cpu_read(cpu_tlbstate.loaded_mm);
	u32 loaded_mm_asid = this_cpu_read(cpu_tlbstate.loaded_mm_asid);
	u64 mm_tlb_gen = atomic64_read(&loaded_mm->context.tlb_gen);
	u64 local_tlb_gen = this_cpu_read(cpu_tlbstate.ctxs[loaded_mm_asid].tlb_gen);

	/* This code cannot presently handle being reentered. */
	VM_WARN_ON(!irqs_disabled());

	if (unlikely(loaded_mm == &init_mm))
		return;

	VM_WARN_ON(this_cpu_read(cpu_tlbstate.ctxs[loaded_mm_asid].ctx_id) !=
		   loaded_mm->context.ctx_id);

	if (this_cpu_read(cpu_tlbstate.is_lazy)) {
		/*
		 * We're in lazy mode.  We need to at least flush our
		 * paging-structure cache to avoid speculatively reading
		 * garbage into our TLB.  Since switching to init_mm is barely
		 * slower than a minimal flush, just switch to init_mm.
		 *
		 * This should be rare, with native_flush_tlb_others skipping
		 * IPIs to lazy TLB mode CPUs.
		 */
		switch_mm_irqs_off(NULL, &init_mm, NULL);
		return;
	}

	if (unlikely(local_tlb_gen == mm_tlb_gen)) {
		/*
		 * There's nothing to do: we're already up to date.  This can
		 * happen if two concurrent flushes happen -- the first flush to
		 * be handled can catch us all the way up, leaving no work for
		 * the second flush.
		 */
		trace_tlb_flush(reason, 0);
		return;
	}

	WARN_ON_ONCE(local_tlb_gen > mm_tlb_gen);
	WARN_ON_ONCE(f->new_tlb_gen > mm_tlb_gen);

	/*
	 * If we get to this point, we know that our TLB is out of date.
	 * This does not strictly imply that we need to flush (it's
	 * possible that f->new_tlb_gen <= local_tlb_gen), but we're
	 * going to need to flush in the very near future, so we might
	 * as well get it over with.
	 *
	 * The only question is whether to do a full or partial flush.
	 *
	 * We do a partial flush if requested and two extra conditions
	 * are met:
	 *
	 * 1. f->new_tlb_gen == local_tlb_gen + 1.  We have an invariant that
	 *    we've always done all needed flushes to catch up to
	 *    local_tlb_gen.  If, for example, local_tlb_gen == 2 and
	 *    f->new_tlb_gen == 3, then we know that the flush needed to bring
	 *    us up to date for tlb_gen 3 is the partial flush we're
	 *    processing.
	 *
	 *    As an example of why this check is needed, suppose that there
	 *    are two concurrent flushes.  The first is a full flush that
	 *    changes context.tlb_gen from 1 to 2.  The second is a partial
	 *    flush that changes context.tlb_gen from 2 to 3.  If they get
	 *    processed on this CPU in reverse order, we'll see
	 *     local_tlb_gen == 1, mm_tlb_gen == 3, and end != TLB_FLUSH_ALL.
	 *    If we were to use __flush_tlb_one_user() and set local_tlb_gen to
	 *    3, we'd be break the invariant: we'd update local_tlb_gen above
	 *    1 without the full flush that's needed for tlb_gen 2.
	 *
	 * 2. f->new_tlb_gen == mm_tlb_gen.  This is purely an optimiation.
	 *    Partial TLB flushes are not all that much cheaper than full TLB
	 *    flushes, so it seems unlikely that it would be a performance win
	 *    to do a partial flush if that won't bring our TLB fully up to
	 *    date.  By doing a full flush instead, we can increase
	 *    local_tlb_gen all the way to mm_tlb_gen and we can probably
	 *    avoid another flush in the very near future.
	 */
	if (f->end != TLB_FLUSH_ALL &&
	    f->new_tlb_gen == local_tlb_gen + 1 &&
	    f->new_tlb_gen == mm_tlb_gen) {
		/* Partial flush */
		unsigned long nr_invalidate = (f->end - f->start) >> f->stride_shift;
		unsigned long addr = f->start;

		while (addr < f->end) {
			__flush_tlb_one_user(addr);
			addr += 1UL << f->stride_shift;
		}
		if (local)
			count_vm_tlb_events(NR_TLB_LOCAL_FLUSH_ONE, nr_invalidate);
		trace_tlb_flush(reason, nr_invalidate);
	} else {
		/* Full flush. */
		local_flush_tlb();
		if (local)
			count_vm_tlb_event(NR_TLB_LOCAL_FLUSH_ALL);
		trace_tlb_flush(reason, TLB_FLUSH_ALL);
	}

	/* Both paths above update our state to mm_tlb_gen. */
	this_cpu_write(cpu_tlbstate.ctxs[loaded_mm_asid].tlb_gen, mm_tlb_gen);
}