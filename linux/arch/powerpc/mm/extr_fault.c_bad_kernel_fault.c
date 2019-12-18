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
struct pt_regs {int /*<<< orphan*/  nip; } ;

/* Variables and functions */
 unsigned long DSISR_KEYFAULT ; 
 unsigned long DSISR_NOEXEC_OR_G ; 
 unsigned long DSISR_PROTFAULT ; 
 unsigned long TASK_SIZE ; 
 int TRAP (struct pt_regs*) ; 
 scalar_t__ bad_kuap_fault (struct pt_regs*,int) ; 
 int /*<<< orphan*/  current_uid () ; 
 int /*<<< orphan*/  from_kuid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_user_ns ; 
 int /*<<< orphan*/  pr_crit_ratelimited (char*,...) ; 
 int /*<<< orphan*/  search_exception_tables (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool bad_kernel_fault(struct pt_regs *regs, unsigned long error_code,
			     unsigned long address, bool is_write)
{
	int is_exec = TRAP(regs) == 0x400;

	/* NX faults set DSISR_PROTFAULT on the 8xx, DSISR_NOEXEC_OR_G on others */
	if (is_exec && (error_code & (DSISR_NOEXEC_OR_G | DSISR_KEYFAULT |
				      DSISR_PROTFAULT))) {
		pr_crit_ratelimited("kernel tried to execute %s page (%lx) - exploit attempt? (uid: %d)\n",
				    address >= TASK_SIZE ? "exec-protected" : "user",
				    address,
				    from_kuid(&init_user_ns, current_uid()));

		// Kernel exec fault is always bad
		return true;
	}

	if (!is_exec && address < TASK_SIZE && (error_code & DSISR_PROTFAULT) &&
	    !search_exception_tables(regs->nip)) {
		pr_crit_ratelimited("Kernel attempted to access user page (%lx) - exploit attempt? (uid: %d)\n",
				    address,
				    from_kuid(&init_user_ns, current_uid()));
	}

	// Kernel fault on kernel address is bad
	if (address >= TASK_SIZE)
		return true;

	// Fault on user outside of certain regions (eg. copy_tofrom_user()) is bad
	if (!search_exception_tables(regs->nip))
		return true;

	// Read/write fault in a valid region (the exception table search passed
	// above), but blocked by KUAP is bad, it can never succeed.
	if (bad_kuap_fault(regs, is_write))
		return true;

	// What's left? Kernel fault on user in well defined regions (extable
	// matched), and allowed by KUAP in the faulting context.
	return false;
}