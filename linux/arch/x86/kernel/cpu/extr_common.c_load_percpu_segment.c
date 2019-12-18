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

/* Variables and functions */
 int /*<<< orphan*/  MSR_GS_BASE ; 
 int /*<<< orphan*/  __KERNEL_PERCPU ; 
 int /*<<< orphan*/  __loadsegment_simple (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_kernelmode_gs_base (int) ; 
 int /*<<< orphan*/  fs ; 
 int /*<<< orphan*/  gs ; 
 int /*<<< orphan*/  load_stack_canary_segment () ; 
 int /*<<< orphan*/  loadsegment (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void load_percpu_segment(int cpu)
{
#ifdef CONFIG_X86_32
	loadsegment(fs, __KERNEL_PERCPU);
#else
	__loadsegment_simple(gs, 0);
	wrmsrl(MSR_GS_BASE, cpu_kernelmode_gs_base(cpu));
#endif
	load_stack_canary_segment();
}