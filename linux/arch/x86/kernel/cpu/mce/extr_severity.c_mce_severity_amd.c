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
struct mce {int status; } ;
typedef  enum context { ____Placeholder_context } context ;
struct TYPE_2__ {scalar_t__ smca; scalar_t__ overflow_recov; } ;

/* Variables and functions */
 int IN_KERNEL ; 
 int MCE_AR_SEVERITY ; 
 int MCE_DEFERRED_SEVERITY ; 
 int MCE_KEEP_SEVERITY ; 
 int MCE_PANIC_SEVERITY ; 
 int MCE_UC_SEVERITY ; 
 int MCI_STATUS_DEFERRED ; 
 int MCI_STATUS_OVER ; 
 int MCI_STATUS_PCC ; 
 int MCI_STATUS_UC ; 
 int error_context (struct mce*) ; 
 TYPE_1__ mce_flags ; 
 int mce_severity_amd_smca (struct mce*,int) ; 

__attribute__((used)) static int mce_severity_amd(struct mce *m, int tolerant, char **msg, bool is_excp)
{
	enum context ctx = error_context(m);

	/* Processor Context Corrupt, no need to fumble too much, die! */
	if (m->status & MCI_STATUS_PCC)
		return MCE_PANIC_SEVERITY;

	if (m->status & MCI_STATUS_UC) {

		if (ctx == IN_KERNEL)
			return MCE_PANIC_SEVERITY;

		/*
		 * On older systems where overflow_recov flag is not present, we
		 * should simply panic if an error overflow occurs. If
		 * overflow_recov flag is present and set, then software can try
		 * to at least kill process to prolong system operation.
		 */
		if (mce_flags.overflow_recov) {
			if (mce_flags.smca)
				return mce_severity_amd_smca(m, ctx);

			/* kill current process */
			return MCE_AR_SEVERITY;
		} else {
			/* at least one error was not logged */
			if (m->status & MCI_STATUS_OVER)
				return MCE_PANIC_SEVERITY;
		}

		/*
		 * For any other case, return MCE_UC_SEVERITY so that we log the
		 * error and exit #MC handler.
		 */
		return MCE_UC_SEVERITY;
	}

	/*
	 * deferred error: poll handler catches these and adds to mce_ring so
	 * memory-failure can take recovery actions.
	 */
	if (m->status & MCI_STATUS_DEFERRED)
		return MCE_DEFERRED_SEVERITY;

	/*
	 * corrected error: poll handler catches these and passes responsibility
	 * of decoding the error to EDAC
	 */
	return MCE_KEEP_SEVERITY;
}