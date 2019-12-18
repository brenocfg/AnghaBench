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
struct eeh_pe {int addr; TYPE_1__* phb; } ;
struct TYPE_2__ {int global_number; } ;

/* Variables and functions */
 int EEH_PE_CFG_BLOCKED ; 
 int EEH_PE_RESET ; 
 int EEH_RESET_DEACTIVATE ; 
 int EEH_RESET_FUNDAMENTAL ; 
 int EEH_RESET_HOT ; 
 int EIO ; 
 int ENOTRECOVERABLE ; 
 int /*<<< orphan*/  PCI_BUS_RESET_WAIT_MSEC ; 
 int /*<<< orphan*/  eeh_pe_dev_traverse (struct eeh_pe*,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  eeh_pe_refreeze_passed (struct eeh_pe*) ; 
 int eeh_pe_reset (struct eeh_pe*,int,int) ; 
 int /*<<< orphan*/  eeh_pe_state_clear (struct eeh_pe*,int,int) ; 
 int /*<<< orphan*/  eeh_pe_state_mark (struct eeh_pe*,int) ; 
 int /*<<< orphan*/  eeh_set_dev_freset ; 
 scalar_t__ eeh_state_active (int) ; 
 int eeh_wait_state (struct eeh_pe*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int,int,...) ; 

int eeh_pe_reset_full(struct eeh_pe *pe, bool include_passed)
{
	int reset_state = (EEH_PE_RESET | EEH_PE_CFG_BLOCKED);
	int type = EEH_RESET_HOT;
	unsigned int freset = 0;
	int i, state = 0, ret;

	/*
	 * Determine the type of reset to perform - hot or fundamental.
	 * Hot reset is the default operation, unless any device under the
	 * PE requires a fundamental reset.
	 */
	eeh_pe_dev_traverse(pe, eeh_set_dev_freset, &freset);

	if (freset)
		type = EEH_RESET_FUNDAMENTAL;

	/* Mark the PE as in reset state and block config space accesses */
	eeh_pe_state_mark(pe, reset_state);

	/* Make three attempts at resetting the bus */
	for (i = 0; i < 3; i++) {
		ret = eeh_pe_reset(pe, type, include_passed);
		if (!ret)
			ret = eeh_pe_reset(pe, EEH_RESET_DEACTIVATE,
					   include_passed);
		if (ret) {
			ret = -EIO;
			pr_warn("EEH: Failure %d resetting PHB#%x-PE#%x (attempt %d)\n\n",
				state, pe->phb->global_number, pe->addr, i + 1);
			continue;
		}
		if (i)
			pr_warn("EEH: PHB#%x-PE#%x: Successful reset (attempt %d)\n",
				pe->phb->global_number, pe->addr, i + 1);

		/* Wait until the PE is in a functioning state */
		state = eeh_wait_state(pe, PCI_BUS_RESET_WAIT_MSEC);
		if (state < 0) {
			pr_warn("EEH: Unrecoverable slot failure on PHB#%x-PE#%x",
				pe->phb->global_number, pe->addr);
			ret = -ENOTRECOVERABLE;
			break;
		}
		if (eeh_state_active(state))
			break;
		else
			pr_warn("EEH: PHB#%x-PE#%x: Slot inactive after reset: 0x%x (attempt %d)\n",
				pe->phb->global_number, pe->addr, state, i + 1);
	}

	/* Resetting the PE may have unfrozen child PEs. If those PEs have been
	 * (potentially) passed through to a guest, re-freeze them:
	 */
	if (!include_passed)
		eeh_pe_refreeze_passed(pe);

	eeh_pe_state_clear(pe, reset_state, true);
	return ret;
}