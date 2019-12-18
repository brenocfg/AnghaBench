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
struct arch_hw_breakpoint {unsigned long address; int len; int /*<<< orphan*/  type; } ;
struct thread_struct {struct arch_hw_breakpoint hw_brk; struct perf_event** ptrace_bps; } ;
struct task_struct {struct thread_struct thread; } ;
struct ppc_hw_breakpoint {int version; int trigger_type; int addr_mode; int condition_mode; unsigned long addr; int addr2; } ;
struct perf_event_attr {unsigned long bp_addr; int bp_len; int /*<<< orphan*/  bp_type; } ;
struct perf_event {int dummy; } ;

/* Variables and functions */
 long EINVAL ; 
 long EIO ; 
 long ENODEV ; 
 long ENOSPC ; 
 long ENOTSUPP ; 
 unsigned long HW_BREAKPOINT_ALIGN ; 
 int /*<<< orphan*/  HW_BRK_TYPE_READ ; 
 int /*<<< orphan*/  HW_BRK_TYPE_TRANSLATE ; 
 int /*<<< orphan*/  HW_BRK_TYPE_WRITE ; 
 scalar_t__ IS_ERR (struct perf_event*) ; 
 int PPC_BREAKPOINT_CONDITION_BE_ALL ; 
 int PPC_BREAKPOINT_CONDITION_MODE ; 
 int PPC_BREAKPOINT_CONDITION_NONE ; 
 int PPC_BREAKPOINT_MODE_EXACT ; 
 int PPC_BREAKPOINT_MODE_MASK ; 
 int PPC_BREAKPOINT_MODE_RANGE_INCLUSIVE ; 
 int PPC_BREAKPOINT_TRIGGER_EXECUTE ; 
 int PPC_BREAKPOINT_TRIGGER_READ ; 
 int PPC_BREAKPOINT_TRIGGER_RW ; 
 int PPC_BREAKPOINT_TRIGGER_WRITE ; 
 long PTR_ERR (struct perf_event*) ; 
 unsigned long TASK_SIZE ; 
 int /*<<< orphan*/  arch_bp_generic_fields (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hw_breakpoint_init (struct perf_event_attr*) ; 
 int /*<<< orphan*/  ppc_breakpoint_available () ; 
 int /*<<< orphan*/  ptrace_triggered ; 
 struct perf_event* register_user_hw_breakpoint (struct perf_event_attr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct task_struct*) ; 
 long set_dac (struct task_struct*,struct ppc_hw_breakpoint*) ; 
 long set_dac_range (struct task_struct*,struct ppc_hw_breakpoint*) ; 
 long set_instruction_bp (struct task_struct*,struct ppc_hw_breakpoint*) ; 

__attribute__((used)) static long ppc_set_hwdebug(struct task_struct *child,
		     struct ppc_hw_breakpoint *bp_info)
{
#ifdef CONFIG_HAVE_HW_BREAKPOINT
	int len = 0;
	struct thread_struct *thread = &(child->thread);
	struct perf_event *bp;
	struct perf_event_attr attr;
#endif /* CONFIG_HAVE_HW_BREAKPOINT */
#ifndef CONFIG_PPC_ADV_DEBUG_REGS
	struct arch_hw_breakpoint brk;
#endif

	if (bp_info->version != 1)
		return -ENOTSUPP;
#ifdef CONFIG_PPC_ADV_DEBUG_REGS
	/*
	 * Check for invalid flags and combinations
	 */
	if ((bp_info->trigger_type == 0) ||
	    (bp_info->trigger_type & ~(PPC_BREAKPOINT_TRIGGER_EXECUTE |
				       PPC_BREAKPOINT_TRIGGER_RW)) ||
	    (bp_info->addr_mode & ~PPC_BREAKPOINT_MODE_MASK) ||
	    (bp_info->condition_mode &
	     ~(PPC_BREAKPOINT_CONDITION_MODE |
	       PPC_BREAKPOINT_CONDITION_BE_ALL)))
		return -EINVAL;
#if CONFIG_PPC_ADV_DEBUG_DVCS == 0
	if (bp_info->condition_mode != PPC_BREAKPOINT_CONDITION_NONE)
		return -EINVAL;
#endif

	if (bp_info->trigger_type & PPC_BREAKPOINT_TRIGGER_EXECUTE) {
		if ((bp_info->trigger_type != PPC_BREAKPOINT_TRIGGER_EXECUTE) ||
		    (bp_info->condition_mode != PPC_BREAKPOINT_CONDITION_NONE))
			return -EINVAL;
		return set_instruction_bp(child, bp_info);
	}
	if (bp_info->addr_mode == PPC_BREAKPOINT_MODE_EXACT)
		return set_dac(child, bp_info);

#ifdef CONFIG_PPC_ADV_DEBUG_DAC_RANGE
	return set_dac_range(child, bp_info);
#else
	return -EINVAL;
#endif
#else /* !CONFIG_PPC_ADV_DEBUG_DVCS */
	/*
	 * We only support one data breakpoint
	 */
	if ((bp_info->trigger_type & PPC_BREAKPOINT_TRIGGER_RW) == 0 ||
	    (bp_info->trigger_type & ~PPC_BREAKPOINT_TRIGGER_RW) != 0 ||
	    bp_info->condition_mode != PPC_BREAKPOINT_CONDITION_NONE)
		return -EINVAL;

	if ((unsigned long)bp_info->addr >= TASK_SIZE)
		return -EIO;

	brk.address = bp_info->addr & ~7UL;
	brk.type = HW_BRK_TYPE_TRANSLATE;
	brk.len = 8;
	if (bp_info->trigger_type & PPC_BREAKPOINT_TRIGGER_READ)
		brk.type |= HW_BRK_TYPE_READ;
	if (bp_info->trigger_type & PPC_BREAKPOINT_TRIGGER_WRITE)
		brk.type |= HW_BRK_TYPE_WRITE;
#ifdef CONFIG_HAVE_HW_BREAKPOINT
	/*
	 * Check if the request is for 'range' breakpoints. We can
	 * support it if range < 8 bytes.
	 */
	if (bp_info->addr_mode == PPC_BREAKPOINT_MODE_RANGE_INCLUSIVE)
		len = bp_info->addr2 - bp_info->addr;
	else if (bp_info->addr_mode == PPC_BREAKPOINT_MODE_EXACT)
		len = 1;
	else
		return -EINVAL;
	bp = thread->ptrace_bps[0];
	if (bp)
		return -ENOSPC;

	/* Create a new breakpoint request if one doesn't exist already */
	hw_breakpoint_init(&attr);
	attr.bp_addr = (unsigned long)bp_info->addr & ~HW_BREAKPOINT_ALIGN;
	attr.bp_len = len;
	arch_bp_generic_fields(brk.type, &attr.bp_type);

	thread->ptrace_bps[0] = bp = register_user_hw_breakpoint(&attr,
					       ptrace_triggered, NULL, child);
	if (IS_ERR(bp)) {
		thread->ptrace_bps[0] = NULL;
		return PTR_ERR(bp);
	}

	return 1;
#endif /* CONFIG_HAVE_HW_BREAKPOINT */

	if (bp_info->addr_mode != PPC_BREAKPOINT_MODE_EXACT)
		return -EINVAL;

	if (child->thread.hw_brk.address)
		return -ENOSPC;

	if (!ppc_breakpoint_available())
		return -ENODEV;

	child->thread.hw_brk = brk;

	return 1;
#endif /* !CONFIG_PPC_ADV_DEBUG_DVCS */
}