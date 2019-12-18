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
struct eeh_pe {int state; } ;

/* Variables and functions */
 int EEH_PE_RECOVERING ; 
 int eeh_clear_pe_frozen_state (struct eeh_pe*,int) ; 
 int /*<<< orphan*/  eeh_dev_restore_state ; 
 int /*<<< orphan*/  eeh_dev_save_state ; 
 int /*<<< orphan*/  eeh_pe_dev_traverse (struct eeh_pe*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int eeh_pe_reset_full (struct eeh_pe*,int) ; 
 int /*<<< orphan*/  eeh_pe_state_clear (struct eeh_pe*,int,int) ; 
 int /*<<< orphan*/  eeh_pe_state_mark (struct eeh_pe*,int) ; 

int eeh_pe_reset_and_recover(struct eeh_pe *pe)
{
	int ret;

	/* Bail if the PE is being recovered */
	if (pe->state & EEH_PE_RECOVERING)
		return 0;

	/* Put the PE into recovery mode */
	eeh_pe_state_mark(pe, EEH_PE_RECOVERING);

	/* Save states */
	eeh_pe_dev_traverse(pe, eeh_dev_save_state, NULL);

	/* Issue reset */
	ret = eeh_pe_reset_full(pe, true);
	if (ret) {
		eeh_pe_state_clear(pe, EEH_PE_RECOVERING, true);
		return ret;
	}

	/* Unfreeze the PE */
	ret = eeh_clear_pe_frozen_state(pe, true);
	if (ret) {
		eeh_pe_state_clear(pe, EEH_PE_RECOVERING, true);
		return ret;
	}

	/* Restore device state */
	eeh_pe_dev_traverse(pe, eeh_dev_restore_state, NULL);

	/* Clear recovery mode */
	eeh_pe_state_clear(pe, EEH_PE_RECOVERING, true);

	return 0;
}