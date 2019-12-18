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
struct pmc_owner {int po_flags; int /*<<< orphan*/  po_pmcs; } ;

/* Variables and functions */
 scalar_t__ LIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OMR ; 
 int /*<<< orphan*/  OWN ; 
 int /*<<< orphan*/  PMCDBG1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,struct pmc_owner*) ; 
 int PMC_PO_OWNS_LOGFILE ; 
 int /*<<< orphan*/  pmc_destroy_owner_descriptor (struct pmc_owner*) ; 
 int /*<<< orphan*/  pmc_remove_owner (struct pmc_owner*) ; 

__attribute__((used)) static void
pmc_maybe_remove_owner(struct pmc_owner *po)
{

	PMCDBG1(OWN,OMR,1, "maybe-remove-owner po=%p", po);

	/*
	 * Remove owner record if
	 * - this process does not own any PMCs
	 * - this process has not allocated a system-wide sampling buffer
	 */

	if (LIST_EMPTY(&po->po_pmcs) &&
	    ((po->po_flags & PMC_PO_OWNS_LOGFILE) == 0)) {
		pmc_remove_owner(po);
		pmc_destroy_owner_descriptor(po);
	}
}