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
struct el_common {int dummy; } ;

/* Variables and functions */
 char* KERN_CRIT ; 
 scalar_t__ MCHK_DISPOSITION_DISMISS ; 
 unsigned long SCB_Q_PROCERR ; 
 int /*<<< orphan*/  dik_show_regs (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  draina () ; 
 char* err_print_prefix ; 
 scalar_t__ ev6_process_logout_frame (struct el_common*,int) ; 
 int /*<<< orphan*/  get_irq_regs () ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  printk (char*,char*,char*,unsigned int,int) ; 
 scalar_t__ smp_processor_id () ; 
 int /*<<< orphan*/  wrmces (int) ; 

void
ev6_machine_check(unsigned long vector, unsigned long la_ptr)
{
	struct el_common *mchk_header = (struct el_common *)la_ptr;

	/*
	 * Sync the processor
	 */
	mb();
	draina();

	/*
	 * Parse the logout frame without printing first. If the only error(s)
	 * found are have a disposition of "dismiss", then just dismiss them
	 * and don't print any message
	 */
	if (ev6_process_logout_frame(mchk_header, 0) != 
	    MCHK_DISPOSITION_DISMISS) {
		char *saved_err_prefix = err_print_prefix;
		err_print_prefix = KERN_CRIT;

		/*
		 * Either a nondismissable error was detected or no
		 * recognized error was detected  in the logout frame 
		 * -- report the error in either case
		 */
		printk("%s*CPU %s Error (Vector 0x%x) reported on CPU %d:\n", 
		       err_print_prefix,
		       (vector == SCB_Q_PROCERR)?"Correctable":"Uncorrectable",
		       (unsigned int)vector, (int)smp_processor_id());
		
		ev6_process_logout_frame(mchk_header, 1);
		dik_show_regs(get_irq_regs(), NULL);

		err_print_prefix = saved_err_prefix;
	}

	/* 
	 * Release the logout frame 
	 */
	wrmces(0x7);
	mb();
}