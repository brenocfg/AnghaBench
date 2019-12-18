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
struct rtas_error_log {int dummy; } ;
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int RTAS_DISP_FULLY_RECOVERED ; 
 scalar_t__ fwnmi_active ; 
 struct rtas_error_log* fwnmi_get_errinfo (struct pt_regs*) ; 
 int /*<<< orphan*/  fwnmi_release_errinfo () ; 
 int /*<<< orphan*/  irq_work_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mce_errlog_process_work ; 
 int mce_handle_error (struct pt_regs*,struct rtas_error_log*) ; 

long pseries_machine_check_realmode(struct pt_regs *regs)
{
	struct rtas_error_log *errp;
	int disposition;

	if (fwnmi_active) {
		errp = fwnmi_get_errinfo(regs);
		/*
		 * Call to fwnmi_release_errinfo() in real mode causes kernel
		 * to panic. Hence we will call it as soon as we go into
		 * virtual mode.
		 */
		disposition = mce_handle_error(regs, errp);
		fwnmi_release_errinfo();

		/* Queue irq work to log this rtas event later. */
		irq_work_queue(&mce_errlog_process_work);

		if (disposition == RTAS_DISP_FULLY_RECOVERED)
			return 1;
	}

	return 0;
}