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
typedef  void* u64 ;
struct residency_counts {void* hits_after; void* miss_after; void* hits_before; void* miss_before; } ;
struct pseudo_lock_region {int /*<<< orphan*/  size; int /*<<< orphan*/  kmem; int /*<<< orphan*/  line_size; int /*<<< orphan*/  cpu; } ;
struct perf_event_attr {int dummy; } ;
struct perf_event {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct perf_event*) ; 
 int /*<<< orphan*/  MSR_MISC_FEATURE_CONTROL ; 
 void* READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 struct perf_event* perf_event_create_kernel_counter (struct perf_event_attr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ perf_event_read_local (struct perf_event*,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_event_release_kernel (struct perf_event*) ; 
 int prefetch_disable_bits ; 
 int /*<<< orphan*/  rdpmcl (int,void*) ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  wrmsr (int /*<<< orphan*/ ,int,int) ; 
 int x86_perf_rdpmc_index (struct perf_event*) ; 

__attribute__((used)) static int measure_residency_fn(struct perf_event_attr *miss_attr,
				struct perf_event_attr *hit_attr,
				struct pseudo_lock_region *plr,
				struct residency_counts *counts)
{
	u64 hits_before = 0, hits_after = 0, miss_before = 0, miss_after = 0;
	struct perf_event *miss_event, *hit_event;
	int hit_pmcnum, miss_pmcnum;
	unsigned int line_size;
	unsigned int size;
	unsigned long i;
	void *mem_r;
	u64 tmp;

	miss_event = perf_event_create_kernel_counter(miss_attr, plr->cpu,
						      NULL, NULL, NULL);
	if (IS_ERR(miss_event))
		goto out;

	hit_event = perf_event_create_kernel_counter(hit_attr, plr->cpu,
						     NULL, NULL, NULL);
	if (IS_ERR(hit_event))
		goto out_miss;

	local_irq_disable();
	/*
	 * Check any possible error state of events used by performing
	 * one local read.
	 */
	if (perf_event_read_local(miss_event, &tmp, NULL, NULL)) {
		local_irq_enable();
		goto out_hit;
	}
	if (perf_event_read_local(hit_event, &tmp, NULL, NULL)) {
		local_irq_enable();
		goto out_hit;
	}

	/*
	 * Disable hardware prefetchers.
	 */
	wrmsr(MSR_MISC_FEATURE_CONTROL, prefetch_disable_bits, 0x0);

	/* Initialize rest of local variables */
	/*
	 * Performance event has been validated right before this with
	 * interrupts disabled - it is thus safe to read the counter index.
	 */
	miss_pmcnum = x86_perf_rdpmc_index(miss_event);
	hit_pmcnum = x86_perf_rdpmc_index(hit_event);
	line_size = READ_ONCE(plr->line_size);
	mem_r = READ_ONCE(plr->kmem);
	size = READ_ONCE(plr->size);

	/*
	 * Read counter variables twice - first to load the instructions
	 * used in L1 cache, second to capture accurate value that does not
	 * include cache misses incurred because of instruction loads.
	 */
	rdpmcl(hit_pmcnum, hits_before);
	rdpmcl(miss_pmcnum, miss_before);
	/*
	 * From SDM: Performing back-to-back fast reads are not guaranteed
	 * to be monotonic.
	 * Use LFENCE to ensure all previous instructions are retired
	 * before proceeding.
	 */
	rmb();
	rdpmcl(hit_pmcnum, hits_before);
	rdpmcl(miss_pmcnum, miss_before);
	/*
	 * Use LFENCE to ensure all previous instructions are retired
	 * before proceeding.
	 */
	rmb();
	for (i = 0; i < size; i += line_size) {
		/*
		 * Add a barrier to prevent speculative execution of this
		 * loop reading beyond the end of the buffer.
		 */
		rmb();
		asm volatile("mov (%0,%1,1), %%eax\n\t"
			     :
			     : "r" (mem_r), "r" (i)
			     : "%eax", "memory");
	}
	/*
	 * Use LFENCE to ensure all previous instructions are retired
	 * before proceeding.
	 */
	rmb();
	rdpmcl(hit_pmcnum, hits_after);
	rdpmcl(miss_pmcnum, miss_after);
	/*
	 * Use LFENCE to ensure all previous instructions are retired
	 * before proceeding.
	 */
	rmb();
	/* Re-enable hardware prefetchers */
	wrmsr(MSR_MISC_FEATURE_CONTROL, 0x0, 0x0);
	local_irq_enable();
out_hit:
	perf_event_release_kernel(hit_event);
out_miss:
	perf_event_release_kernel(miss_event);
out:
	/*
	 * All counts will be zero on failure.
	 */
	counts->miss_before = miss_before;
	counts->hits_before = hits_before;
	counts->miss_after  = miss_after;
	counts->hits_after  = hits_after;
	return 0;
}