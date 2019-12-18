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
struct flush_tlb_info {int dummy; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 unsigned long TLB_FLUSH_ALL ; 
 int /*<<< orphan*/  do_flush_tlb_all ; 
 int /*<<< orphan*/  do_kernel_range_flush ; 
 struct flush_tlb_info* get_flush_tlb_info (int /*<<< orphan*/ *,unsigned long,unsigned long,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  on_each_cpu (int /*<<< orphan*/ ,struct flush_tlb_info*,int) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  put_flush_tlb_info () ; 
 unsigned long tlb_single_page_flush_ceiling ; 

void flush_tlb_kernel_range(unsigned long start, unsigned long end)
{
	/* Balance as user space task's flush, a bit conservative */
	if (end == TLB_FLUSH_ALL ||
	    (end - start) > tlb_single_page_flush_ceiling << PAGE_SHIFT) {
		on_each_cpu(do_flush_tlb_all, NULL, 1);
	} else {
		struct flush_tlb_info *info;

		preempt_disable();
		info = get_flush_tlb_info(NULL, start, end, 0, false, 0);

		on_each_cpu(do_kernel_range_flush, info, 1);

		put_flush_tlb_info();
		preempt_enable();
	}
}