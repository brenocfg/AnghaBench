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
struct pt_regs {int dummy; } ;
struct machine_check_event {scalar_t__ version; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCE_EVENT_RELEASE ; 
 scalar_t__ MCE_V1 ; 
 int /*<<< orphan*/  get_mce_event (struct machine_check_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  machine_check_print_event_info (struct machine_check_event*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__) ; 
 scalar_t__ recover_mce (struct pt_regs*,struct machine_check_event*) ; 
 int /*<<< orphan*/  user_mode (struct pt_regs*) ; 

int pSeries_machine_check_exception(struct pt_regs *regs)
{
	struct machine_check_event evt;

	if (!get_mce_event(&evt, MCE_EVENT_RELEASE))
		return 0;

	/* Print things out */
	if (evt.version != MCE_V1) {
		pr_err("Machine Check Exception, Unknown event version %d !\n",
		       evt.version);
		return 0;
	}
	machine_check_print_event_info(&evt, user_mode(regs), false);

	if (recover_mce(regs, &evt))
		return 1;

	return 0;
}