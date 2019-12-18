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
struct tlbiel_va_range {unsigned long start; unsigned long end; unsigned long pid; unsigned long page_size; unsigned long psize; int also_pwc; } ;
struct TYPE_2__ {int /*<<< orphan*/  copros; } ;
struct mm_struct {TYPE_1__ context; } ;
struct cpumask {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _tlbie_va_range (unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,int) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_tlbiel_va_range ; 
 struct cpumask* mm_cpumask (struct mm_struct*) ; 
 int /*<<< orphan*/  on_each_cpu_mask (struct cpumask*,int /*<<< orphan*/ ,struct tlbiel_va_range*,int) ; 

__attribute__((used)) static inline void _tlbiel_va_range_multicast(struct mm_struct *mm,
				unsigned long start, unsigned long end,
				unsigned long pid, unsigned long page_size,
				unsigned long psize, bool also_pwc)
{
	struct cpumask *cpus = mm_cpumask(mm);
	struct tlbiel_va_range t = { .start = start, .end = end,
				.pid = pid, .page_size = page_size,
				.psize = psize, .also_pwc = also_pwc };

	on_each_cpu_mask(cpus, do_tlbiel_va_range, &t, 1);
	if (atomic_read(&mm->context.copros) > 0)
		_tlbie_va_range(start, end, pid, page_size, psize, also_pwc);
}