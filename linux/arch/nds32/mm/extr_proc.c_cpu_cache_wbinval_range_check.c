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
struct vm_area_struct {int /*<<< orphan*/  vm_mm; } ;
struct TYPE_2__ {unsigned long line_size; } ;

/* Variables and functions */
 size_t DCACHE ; 
 TYPE_1__* L1_cache_info ; 
 unsigned long PAGE_MASK ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  cpu_dcache_wbinval_all () ; 
 int /*<<< orphan*/  cpu_dcache_wbinval_page (unsigned long) ; 
 int /*<<< orphan*/  cpu_dcache_wbinval_range (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  cpu_icache_inval_all () ; 
 int /*<<< orphan*/  cpu_icache_inval_page (unsigned long) ; 
 int /*<<< orphan*/  cpu_icache_inval_range (unsigned long,unsigned long) ; 
 scalar_t__ va_present (int /*<<< orphan*/ ,unsigned long) ; 

void cpu_cache_wbinval_range_check(struct vm_area_struct *vma,
				   unsigned long start, unsigned long end,
				   bool flushi, bool wbd)
{
	unsigned long line_size, t_start, t_end;

	if (!flushi && !wbd)
		return;
	line_size = L1_cache_info[DCACHE].line_size;
	start = start & ~(line_size - 1);
	end = (end + line_size - 1) & ~(line_size - 1);

	if ((end - start) > (8 * PAGE_SIZE)) {
		if (wbd)
			cpu_dcache_wbinval_all();
		if (flushi)
			cpu_icache_inval_all();
		return;
	}

	t_start = (start + PAGE_SIZE) & PAGE_MASK;
	t_end = ((end - 1) & PAGE_MASK);

	if ((start & PAGE_MASK) == t_end) {
		if (va_present(vma->vm_mm, start)) {
			if (wbd)
				cpu_dcache_wbinval_range(start, end);
			if (flushi)
				cpu_icache_inval_range(start, end);
		}
		return;
	}

	if (va_present(vma->vm_mm, start)) {
		if (wbd)
			cpu_dcache_wbinval_range(start, t_start);
		if (flushi)
			cpu_icache_inval_range(start, t_start);
	}

	if (va_present(vma->vm_mm, end - 1)) {
		if (wbd)
			cpu_dcache_wbinval_range(t_end, end);
		if (flushi)
			cpu_icache_inval_range(t_end, end);
	}

	while (t_start < t_end) {
		if (va_present(vma->vm_mm, t_start)) {
			if (wbd)
				cpu_dcache_wbinval_page(t_start);
			if (flushi)
				cpu_icache_inval_page(t_start);
		}
		t_start += PAGE_SIZE;
	}
}