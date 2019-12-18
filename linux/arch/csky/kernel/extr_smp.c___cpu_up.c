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
struct task_struct {int dummy; } ;

/* Variables and functions */
 scalar_t__ THREAD_SIZE ; 
 int /*<<< orphan*/  cpu_online (unsigned int) ; 
 int /*<<< orphan*/  cpumask_of (unsigned int) ; 
 unsigned long mfcr (char*) ; 
 int /*<<< orphan*/  mtcr (char*,unsigned long) ; 
 unsigned long secondary_ccr ; 
 unsigned long secondary_hint ; 
 scalar_t__ secondary_stack ; 
 int /*<<< orphan*/  send_arch_ipi (int /*<<< orphan*/ ) ; 
 scalar_t__ task_stack_page (struct task_struct*) ; 

int __cpu_up(unsigned int cpu, struct task_struct *tidle)
{
	unsigned long mask = 1 << cpu;

	secondary_stack =
		(unsigned int) task_stack_page(tidle) + THREAD_SIZE - 8;
	secondary_hint = mfcr("cr31");
	secondary_ccr  = mfcr("cr18");

	/*
	 * Because other CPUs are in reset status, we must flush data
	 * from cache to out and secondary CPUs use them in
	 * csky_start_secondary(void)
	 */
	mtcr("cr17", 0x22);

	if (mask & mfcr("cr<29, 0>")) {
		send_arch_ipi(cpumask_of(cpu));
	} else {
		/* Enable cpu in SMP reset ctrl reg */
		mask |= mfcr("cr<29, 0>");
		mtcr("cr<29, 0>", mask);
	}

	/* Wait for the cpu online */
	while (!cpu_online(cpu));

	secondary_stack = 0;

	return 0;
}