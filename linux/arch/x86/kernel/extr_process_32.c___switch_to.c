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
struct fpu {int dummy; } ;
struct thread_struct {int gs; scalar_t__ iopl; struct fpu fpu; } ;
struct task_struct {struct thread_struct thread; } ;

/* Variables and functions */
 struct task_struct* THREAD_SIZE ; 
 int /*<<< orphan*/  TIF_NEED_FPU_LOAD ; 
 int /*<<< orphan*/  arch_end_context_switch (struct task_struct*) ; 
 int /*<<< orphan*/  cpu_current_top_of_stack ; 
 int /*<<< orphan*/  current_task ; 
 scalar_t__ get_kernel_rpl () ; 
 int /*<<< orphan*/  lazy_load_gs (int) ; 
 int /*<<< orphan*/  lazy_save_gs (int) ; 
 int /*<<< orphan*/  load_TLS (struct thread_struct*,int) ; 
 int /*<<< orphan*/  refresh_sysenter_cs (struct thread_struct*) ; 
 int /*<<< orphan*/  resctrl_sched_in () ; 
 int /*<<< orphan*/  set_iopl_mask (scalar_t__) ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/  switch_fpu_finish (struct fpu*) ; 
 int /*<<< orphan*/  switch_fpu_prepare (struct fpu*,int) ; 
 int /*<<< orphan*/  switch_to_extra (struct task_struct*,struct task_struct*) ; 
 scalar_t__ task_stack_page (struct task_struct*) ; 
 int /*<<< orphan*/  test_thread_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  this_cpu_write (int /*<<< orphan*/ ,struct task_struct*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  update_task_stack (struct task_struct*) ; 

struct task_struct *
__switch_to(struct task_struct *prev_p, struct task_struct *next_p)
{
	struct thread_struct *prev = &prev_p->thread,
			     *next = &next_p->thread;
	struct fpu *prev_fpu = &prev->fpu;
	struct fpu *next_fpu = &next->fpu;
	int cpu = smp_processor_id();

	/* never put a printk in __switch_to... printk() calls wake_up*() indirectly */

	if (!test_thread_flag(TIF_NEED_FPU_LOAD))
		switch_fpu_prepare(prev_fpu, cpu);

	/*
	 * Save away %gs. No need to save %fs, as it was saved on the
	 * stack on entry.  No need to save %es and %ds, as those are
	 * always kernel segments while inside the kernel.  Doing this
	 * before setting the new TLS descriptors avoids the situation
	 * where we temporarily have non-reloadable segments in %fs
	 * and %gs.  This could be an issue if the NMI handler ever
	 * used %fs or %gs (it does not today), or if the kernel is
	 * running inside of a hypervisor layer.
	 */
	lazy_save_gs(prev->gs);

	/*
	 * Load the per-thread Thread-Local Storage descriptor.
	 */
	load_TLS(next, cpu);

	/*
	 * Restore IOPL if needed.  In normal use, the flags restore
	 * in the switch assembly will handle this.  But if the kernel
	 * is running virtualized at a non-zero CPL, the popf will
	 * not restore flags, so it must be done in a separate step.
	 */
	if (get_kernel_rpl() && unlikely(prev->iopl != next->iopl))
		set_iopl_mask(next->iopl);

	switch_to_extra(prev_p, next_p);

	/*
	 * Leave lazy mode, flushing any hypercalls made here.
	 * This must be done before restoring TLS segments so
	 * the GDT and LDT are properly updated.
	 */
	arch_end_context_switch(next_p);

	/*
	 * Reload esp0 and cpu_current_top_of_stack.  This changes
	 * current_thread_info().  Refresh the SYSENTER configuration in
	 * case prev or next is vm86.
	 */
	update_task_stack(next_p);
	refresh_sysenter_cs(next);
	this_cpu_write(cpu_current_top_of_stack,
		       (unsigned long)task_stack_page(next_p) +
		       THREAD_SIZE);

	/*
	 * Restore %gs if needed (which is common)
	 */
	if (prev->gs | next->gs)
		lazy_load_gs(next->gs);

	this_cpu_write(current_task, next_p);

	switch_fpu_finish(next_fpu);

	/* Load the Intel cache allocation PQR MSR. */
	resctrl_sched_in();

	return prev_p;
}