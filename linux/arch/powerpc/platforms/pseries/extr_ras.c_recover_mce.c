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
struct pt_regs {int msr; int /*<<< orphan*/  nip; } ;
struct machine_check_event {scalar_t__ disposition; scalar_t__ severity; scalar_t__ sync_error; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_MCEERR_AR ; 
 scalar_t__ MCE_DISPOSITION_RECOVERED ; 
 scalar_t__ MCE_SEV_FATAL ; 
 int MSR_RI ; 
 int /*<<< orphan*/  SIGBUS ; 
 int /*<<< orphan*/  _exception (int /*<<< orphan*/ ,struct pt_regs*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (char*,struct pt_regs*,int /*<<< orphan*/ ) ; 
 scalar_t__ die_will_crash () ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ user_mode (struct pt_regs*) ; 

__attribute__((used)) static int recover_mce(struct pt_regs *regs, struct machine_check_event *evt)
{
	int recovered = 0;

	if (!(regs->msr & MSR_RI)) {
		/* If MSR_RI isn't set, we cannot recover */
		pr_err("Machine check interrupt unrecoverable: MSR(RI=0)\n");
		recovered = 0;
	} else if (evt->disposition == MCE_DISPOSITION_RECOVERED) {
		/* Platform corrected itself */
		recovered = 1;
	} else if (evt->severity == MCE_SEV_FATAL) {
		/* Fatal machine check */
		pr_err("Machine check interrupt is fatal\n");
		recovered = 0;
	}

	if (!recovered && evt->sync_error) {
		/*
		 * Try to kill processes if we get a synchronous machine check
		 * (e.g., one caused by execution of this instruction). This
		 * will devolve into a panic if we try to kill init or are in
		 * an interrupt etc.
		 *
		 * TODO: Queue up this address for hwpoisioning later.
		 * TODO: This is not quite right for d-side machine
		 *       checks ->nip is not necessarily the important
		 *       address.
		 */
		if ((user_mode(regs))) {
			_exception(SIGBUS, regs, BUS_MCEERR_AR, regs->nip);
			recovered = 1;
		} else if (die_will_crash()) {
			/*
			 * die() would kill the kernel, so better to go via
			 * the platform reboot code that will log the
			 * machine check.
			 */
			recovered = 0;
		} else {
			die("Machine check", regs, SIGBUS);
			recovered = 1;
		}
	}

	return recovered;
}