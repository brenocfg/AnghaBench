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
struct pmc_thread {int dummy; } ;
struct pmc_process {int /*<<< orphan*/  pp_tds; } ;

/* Variables and functions */
 struct pmc_thread* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct pmc_thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_PMC ; 
 int /*<<< orphan*/  free (struct pmc_process*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmc_thread_descriptor_pool_free (struct pmc_thread*) ; 
 int /*<<< orphan*/  pt_next ; 

__attribute__((used)) static void
pmc_destroy_process_descriptor(struct pmc_process *pp)
{
	struct pmc_thread *pmc_td;

	while ((pmc_td = LIST_FIRST(&pp->pp_tds)) != NULL) {
		LIST_REMOVE(pmc_td, pt_next);
		pmc_thread_descriptor_pool_free(pmc_td);
	}
	free(pp, M_PMC);
}