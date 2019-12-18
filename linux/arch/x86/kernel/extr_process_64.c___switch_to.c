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
struct thread_struct {unsigned short es; unsigned short ds; scalar_t__ iopl; struct fpu fpu; } ;
struct task_struct {struct thread_struct thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_DEBUG_ENTRY ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIF_NEED_FPU_LOAD ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  X86_BUG_SYSRET_SS_ATTRS ; 
 int /*<<< orphan*/  X86_FEATURE_XENPV ; 
 unsigned short __KERNEL_DS ; 
 int /*<<< orphan*/  arch_end_context_switch (struct task_struct*) ; 
 int /*<<< orphan*/  cpu_current_top_of_stack ; 
 int /*<<< orphan*/  current_task ; 
 int /*<<< orphan*/  ds ; 
 int /*<<< orphan*/  es ; 
 int /*<<< orphan*/  irq_count ; 
 int /*<<< orphan*/  load_TLS (struct thread_struct*,int) ; 
 int /*<<< orphan*/  loadsegment (int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  resctrl_sched_in () ; 
 int /*<<< orphan*/  save_fsgs (struct task_struct*) ; 
 int /*<<< orphan*/  savesegment (int /*<<< orphan*/ ,unsigned short) ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/  ss ; 
 scalar_t__ static_cpu_has (int /*<<< orphan*/ ) ; 
 scalar_t__ static_cpu_has_bug (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  switch_fpu_finish (struct fpu*) ; 
 int /*<<< orphan*/  switch_fpu_prepare (struct fpu*,int) ; 
 int /*<<< orphan*/  switch_to_extra (struct task_struct*,struct task_struct*) ; 
 struct task_struct* task_top_of_stack (struct task_struct*) ; 
 int /*<<< orphan*/  test_thread_flag (int /*<<< orphan*/ ) ; 
 int this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  this_cpu_write (int /*<<< orphan*/ ,struct task_struct*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  update_task_stack (struct task_struct*) ; 
 int /*<<< orphan*/  x86_fsgsbase_load (struct thread_struct*,struct thread_struct*) ; 
 int /*<<< orphan*/  xen_set_iopl_mask (scalar_t__) ; 

struct task_struct *
__switch_to(struct task_struct *prev_p, struct task_struct *next_p)
{
	struct thread_struct *prev = &prev_p->thread;
	struct thread_struct *next = &next_p->thread;
	struct fpu *prev_fpu = &prev->fpu;
	struct fpu *next_fpu = &next->fpu;
	int cpu = smp_processor_id();

	WARN_ON_ONCE(IS_ENABLED(CONFIG_DEBUG_ENTRY) &&
		     this_cpu_read(irq_count) != -1);

	if (!test_thread_flag(TIF_NEED_FPU_LOAD))
		switch_fpu_prepare(prev_fpu, cpu);

	/* We must save %fs and %gs before load_TLS() because
	 * %fs and %gs may be cleared by load_TLS().
	 *
	 * (e.g. xen_load_tls())
	 */
	save_fsgs(prev_p);

	/*
	 * Load TLS before restoring any segments so that segment loads
	 * reference the correct GDT entries.
	 */
	load_TLS(next, cpu);

	/*
	 * Leave lazy mode, flushing any hypercalls made here.  This
	 * must be done after loading TLS entries in the GDT but before
	 * loading segments that might reference them.
	 */
	arch_end_context_switch(next_p);

	/* Switch DS and ES.
	 *
	 * Reading them only returns the selectors, but writing them (if
	 * nonzero) loads the full descriptor from the GDT or LDT.  The
	 * LDT for next is loaded in switch_mm, and the GDT is loaded
	 * above.
	 *
	 * We therefore need to write new values to the segment
	 * registers on every context switch unless both the new and old
	 * values are zero.
	 *
	 * Note that we don't need to do anything for CS and SS, as
	 * those are saved and restored as part of pt_regs.
	 */
	savesegment(es, prev->es);
	if (unlikely(next->es | prev->es))
		loadsegment(es, next->es);

	savesegment(ds, prev->ds);
	if (unlikely(next->ds | prev->ds))
		loadsegment(ds, next->ds);

	x86_fsgsbase_load(prev, next);

	/*
	 * Switch the PDA and FPU contexts.
	 */
	this_cpu_write(current_task, next_p);
	this_cpu_write(cpu_current_top_of_stack, task_top_of_stack(next_p));

	switch_fpu_finish(next_fpu);

	/* Reload sp0. */
	update_task_stack(next_p);

	switch_to_extra(prev_p, next_p);

#ifdef CONFIG_XEN_PV
	/*
	 * On Xen PV, IOPL bits in pt_regs->flags have no effect, and
	 * current_pt_regs()->flags may not match the current task's
	 * intended IOPL.  We need to switch it manually.
	 */
	if (unlikely(static_cpu_has(X86_FEATURE_XENPV) &&
		     prev->iopl != next->iopl))
		xen_set_iopl_mask(next->iopl);
#endif

	if (static_cpu_has_bug(X86_BUG_SYSRET_SS_ATTRS)) {
		/*
		 * AMD CPUs have a misfeature: SYSRET sets the SS selector but
		 * does not update the cached descriptor.  As a result, if we
		 * do SYSRET while SS is NULL, we'll end up in user mode with
		 * SS apparently equal to __USER_DS but actually unusable.
		 *
		 * The straightforward workaround would be to fix it up just
		 * before SYSRET, but that would slow down the system call
		 * fast paths.  Instead, we ensure that SS is never NULL in
		 * system call context.  We do this by replacing NULL SS
		 * selectors at every context switch.  SYSCALL sets up a valid
		 * SS, so the only way to get NULL is to re-enter the kernel
		 * from CPL 3 through an interrupt.  Since that can't happen
		 * in the same task as a running syscall, we are guaranteed to
		 * context switch between every interrupt vector entry and a
		 * subsequent SYSRET.
		 *
		 * We read SS first because SS reads are much faster than
		 * writes.  Out of caution, we force SS to __KERNEL_DS even if
		 * it previously had a different non-NULL value.
		 */
		unsigned short ss_sel;
		savesegment(ss, ss_sel);
		if (ss_sel != __KERNEL_DS)
			loadsegment(ss, __KERNEL_DS);
	}

	/* Load the Intel cache allocation PQR MSR. */
	resctrl_sched_in();

	return prev_p;
}