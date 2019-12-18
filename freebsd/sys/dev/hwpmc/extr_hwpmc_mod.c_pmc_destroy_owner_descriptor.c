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
struct pmc_owner {int /*<<< orphan*/  po_mtx; TYPE_1__* po_owner; } ;
struct TYPE_2__ {int /*<<< orphan*/  p_comm; int /*<<< orphan*/  p_pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_PMC ; 
 int /*<<< orphan*/  OWN ; 
 int /*<<< orphan*/  PMCDBG4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,struct pmc_owner*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REL ; 
 int /*<<< orphan*/  free (struct pmc_owner*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pmc_destroy_owner_descriptor(struct pmc_owner *po)
{

	PMCDBG4(OWN,REL,1, "destroy-owner po=%p proc=%p (%d, %s)",
	    po, po->po_owner, po->po_owner->p_pid, po->po_owner->p_comm);

	mtx_destroy(&po->po_mtx);
	free(po, M_PMC);
}