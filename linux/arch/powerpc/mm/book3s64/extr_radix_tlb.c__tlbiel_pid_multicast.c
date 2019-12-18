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
struct tlbiel_pid {unsigned long pid; unsigned long ric; } ;
struct TYPE_2__ {int /*<<< orphan*/  copros; } ;
struct mm_struct {TYPE_1__ context; } ;
struct cpumask {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RIC_FLUSH_ALL ; 
 int /*<<< orphan*/  _tlbie_pid (unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_tlbiel_pid ; 
 struct cpumask* mm_cpumask (struct mm_struct*) ; 
 int /*<<< orphan*/  on_each_cpu_mask (struct cpumask*,int /*<<< orphan*/ ,struct tlbiel_pid*,int) ; 

__attribute__((used)) static inline void _tlbiel_pid_multicast(struct mm_struct *mm,
				unsigned long pid, unsigned long ric)
{
	struct cpumask *cpus = mm_cpumask(mm);
	struct tlbiel_pid t = { .pid = pid, .ric = ric };

	on_each_cpu_mask(cpus, do_tlbiel_pid, &t, 1);
	/*
	 * Always want the CPU translations to be invalidated with tlbiel in
	 * these paths, so while coprocessors must use tlbie, we can not
	 * optimise away the tlbiel component.
	 */
	if (atomic_read(&mm->context.copros) > 0)
		_tlbie_pid(pid, RIC_FLUSH_ALL);
}