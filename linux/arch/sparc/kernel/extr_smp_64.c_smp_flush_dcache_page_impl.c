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
typedef  int u64 ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __local_flush_dcache_page (struct page*) ; 
 int /*<<< orphan*/  __pa (void*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ cheetah ; 
 scalar_t__ cheetah_plus ; 
 scalar_t__ cpu_online (int) ; 
 int /*<<< orphan*/  cpumask_of (int) ; 
 int /*<<< orphan*/  dcpage_flushes ; 
 int /*<<< orphan*/  dcpage_flushes_xcall ; 
 int get_cpu () ; 
 scalar_t__ hypervisor ; 
 void* page_address (struct page*) ; 
 int /*<<< orphan*/ * page_mapping_file (struct page*) ; 
 int /*<<< orphan*/  put_cpu () ; 
 scalar_t__ spitfire ; 
 scalar_t__ tlb_type ; 
 int /*<<< orphan*/  xcall_deliver (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xcall_flush_dcache_page_cheetah ; 
 int /*<<< orphan*/  xcall_flush_dcache_page_spitfire ; 

void smp_flush_dcache_page_impl(struct page *page, int cpu)
{
	int this_cpu;

	if (tlb_type == hypervisor)
		return;

#ifdef CONFIG_DEBUG_DCFLUSH
	atomic_inc(&dcpage_flushes);
#endif

	this_cpu = get_cpu();

	if (cpu == this_cpu) {
		__local_flush_dcache_page(page);
	} else if (cpu_online(cpu)) {
		void *pg_addr = page_address(page);
		u64 data0 = 0;

		if (tlb_type == spitfire) {
			data0 = ((u64)&xcall_flush_dcache_page_spitfire);
			if (page_mapping_file(page) != NULL)
				data0 |= ((u64)1 << 32);
		} else if (tlb_type == cheetah || tlb_type == cheetah_plus) {
#ifdef DCACHE_ALIASING_POSSIBLE
			data0 =	((u64)&xcall_flush_dcache_page_cheetah);
#endif
		}
		if (data0) {
			xcall_deliver(data0, __pa(pg_addr),
				      (u64) pg_addr, cpumask_of(cpu));
#ifdef CONFIG_DEBUG_DCFLUSH
			atomic_inc(&dcpage_flushes_xcall);
#endif
		}
	}

	put_cpu();
}