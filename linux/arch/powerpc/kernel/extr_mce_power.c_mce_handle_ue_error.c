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
struct pt_regs {int /*<<< orphan*/  nip; } ;
struct mce_error_info {int ignore_event; } ;
struct exception_table_entry {int dummy; } ;
struct TYPE_2__ {scalar_t__ (* mce_check_early_recovery ) (struct pt_regs*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  extable_fixup (struct exception_table_entry const*) ; 
 TYPE_1__ ppc_md ; 
 struct exception_table_entry* search_kernel_exception_table (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct pt_regs*) ; 

__attribute__((used)) static long mce_handle_ue_error(struct pt_regs *regs,
				struct mce_error_info *mce_err)
{
	long handled = 0;
	const struct exception_table_entry *entry;

	entry = search_kernel_exception_table(regs->nip);
	if (entry) {
		mce_err->ignore_event = true;
		regs->nip = extable_fixup(entry);
		return 1;
	}

	/*
	 * On specific SCOM read via MMIO we may get a machine check
	 * exception with SRR0 pointing inside opal. If that is the
	 * case OPAL may have recovery address to re-read SCOM data in
	 * different way and hence we can recover from this MC.
	 */

	if (ppc_md.mce_check_early_recovery) {
		if (ppc_md.mce_check_early_recovery(regs))
			handled = 1;
	}
	return handled;
}