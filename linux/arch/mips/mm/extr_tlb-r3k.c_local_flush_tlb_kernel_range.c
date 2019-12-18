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
struct TYPE_2__ {unsigned long tlbsize; } ;

/* Variables and functions */
 int KSEG0 ; 
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 TYPE_1__ current_cpu_data ; 
 int /*<<< orphan*/  local_flush_tlb_all () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  printk (char*,unsigned long,unsigned long) ; 
 int read_c0_entryhi () ; 
 int read_c0_index () ; 
 int /*<<< orphan*/  tlb_probe () ; 
 int /*<<< orphan*/  tlb_write_indexed () ; 
 int /*<<< orphan*/  write_c0_entryhi (int) ; 
 int /*<<< orphan*/  write_c0_entrylo0 (int /*<<< orphan*/ ) ; 

void local_flush_tlb_kernel_range(unsigned long start, unsigned long end)
{
	unsigned long size, flags;

#ifdef DEBUG_TLB
	printk("[tlbrange<%lu,0x%08lx,0x%08lx>]", start, end);
#endif
	local_irq_save(flags);
	size = (end - start + (PAGE_SIZE - 1)) >> PAGE_SHIFT;
	if (size <= current_cpu_data.tlbsize) {
		int pid = read_c0_entryhi();

		start &= PAGE_MASK;
		end += PAGE_SIZE - 1;
		end &= PAGE_MASK;

		while (start < end) {
			int idx;

			write_c0_entryhi(start);
			start += PAGE_SIZE;		/* BARRIER */
			tlb_probe();
			idx = read_c0_index();
			write_c0_entrylo0(0);
			write_c0_entryhi(KSEG0);
			if (idx < 0)			/* BARRIER */
				continue;
			tlb_write_indexed();
		}
		write_c0_entryhi(pid);
	} else {
		local_flush_tlb_all();
	}
	local_irq_restore(flags);
}