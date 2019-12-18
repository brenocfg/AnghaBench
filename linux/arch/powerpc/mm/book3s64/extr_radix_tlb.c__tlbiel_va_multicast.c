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
struct tlbiel_va {unsigned long va; unsigned long pid; unsigned long psize; unsigned long ric; } ;
struct TYPE_2__ {int /*<<< orphan*/  copros; } ;
struct mm_struct {TYPE_1__ context; } ;
struct cpumask {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RIC_FLUSH_TLB ; 
 int /*<<< orphan*/  _tlbie_va (unsigned long,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_tlbiel_va ; 
 struct cpumask* mm_cpumask (struct mm_struct*) ; 
 int /*<<< orphan*/  on_each_cpu_mask (struct cpumask*,int /*<<< orphan*/ ,struct tlbiel_va*,int) ; 

__attribute__((used)) static inline void _tlbiel_va_multicast(struct mm_struct *mm,
				unsigned long va, unsigned long pid,
				unsigned long psize, unsigned long ric)
{
	struct cpumask *cpus = mm_cpumask(mm);
	struct tlbiel_va t = { .va = va, .pid = pid, .psize = psize, .ric = ric };
	on_each_cpu_mask(cpus, do_tlbiel_va, &t, 1);
	if (atomic_read(&mm->context.copros) > 0)
		_tlbie_va(va, pid, psize, RIC_FLUSH_TLB);
}