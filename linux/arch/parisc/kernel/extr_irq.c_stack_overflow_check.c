#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {unsigned long* gr; scalar_t__* sr; } ;
struct TYPE_4__ {int /*<<< orphan*/  comm; } ;
struct TYPE_3__ {int /*<<< orphan*/  kernel_stack_usage; int /*<<< orphan*/  irq_stack_usage; } ;

/* Variables and functions */
 unsigned long IRQ_STACK_SIZE ; 
 unsigned long STACK_MARGIN ; 
 unsigned long THREAD_SIZE ; 
 TYPE_2__* current ; 
 scalar_t__ current_thread_info () ; 
 int /*<<< orphan*/  irq_stack_union ; 
 TYPE_1__ irq_stat ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  panic (char*) ; 
 unsigned int per_cpu (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_emerg (char*,int /*<<< orphan*/ ,unsigned long,unsigned long,unsigned long) ; 
 int smp_processor_id () ; 
 int sysctl_panic_on_stackoverflow ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void stack_overflow_check(struct pt_regs *regs)
{
#ifdef CONFIG_DEBUG_STACKOVERFLOW
	#define STACK_MARGIN	(256*6)

	/* Our stack starts directly behind the thread_info struct. */
	unsigned long stack_start = (unsigned long) current_thread_info();
	unsigned long sp = regs->gr[30];
	unsigned long stack_usage;
	unsigned int *last_usage;
	int cpu = smp_processor_id();

	/* if sr7 != 0, we interrupted a userspace process which we do not want
	 * to check for stack overflow. We will only check the kernel stack. */
	if (regs->sr[7])
		return;

	/* exit if already in panic */
	if (sysctl_panic_on_stackoverflow < 0)
		return;

	/* calculate kernel stack usage */
	stack_usage = sp - stack_start;
#ifdef CONFIG_IRQSTACKS
	if (likely(stack_usage <= THREAD_SIZE))
		goto check_kernel_stack; /* found kernel stack */

	/* check irq stack usage */
	stack_start = (unsigned long) &per_cpu(irq_stack_union, cpu).stack;
	stack_usage = sp - stack_start;

	last_usage = &per_cpu(irq_stat.irq_stack_usage, cpu);
	if (unlikely(stack_usage > *last_usage))
		*last_usage = stack_usage;

	if (likely(stack_usage < (IRQ_STACK_SIZE - STACK_MARGIN)))
		return;

	pr_emerg("stackcheck: %s will most likely overflow irq stack "
		 "(sp:%lx, stk bottom-top:%lx-%lx)\n",
		current->comm, sp, stack_start, stack_start + IRQ_STACK_SIZE);
	goto panic_check;

check_kernel_stack:
#endif

	/* check kernel stack usage */
	last_usage = &per_cpu(irq_stat.kernel_stack_usage, cpu);

	if (unlikely(stack_usage > *last_usage))
		*last_usage = stack_usage;

	if (likely(stack_usage < (THREAD_SIZE - STACK_MARGIN)))
		return;

	pr_emerg("stackcheck: %s will most likely overflow kernel stack "
		 "(sp:%lx, stk bottom-top:%lx-%lx)\n",
		current->comm, sp, stack_start, stack_start + THREAD_SIZE);

#ifdef CONFIG_IRQSTACKS
panic_check:
#endif
	if (sysctl_panic_on_stackoverflow) {
		sysctl_panic_on_stackoverflow = -1; /* disable further checks */
		panic("low stack detected by irq handler - check messages\n");
	}
#endif
}