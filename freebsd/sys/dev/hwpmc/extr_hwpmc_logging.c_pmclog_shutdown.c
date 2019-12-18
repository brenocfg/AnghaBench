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
struct pmclog_buffer {int /*<<< orphan*/  plb_base; } ;
struct TYPE_2__ {int /*<<< orphan*/  pdbh_plbs; int /*<<< orphan*/  pdbh_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_PMC ; 
 struct pmclog_buffer* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct pmclog_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  plb_next ; 
 TYPE_1__** pmc_dom_hdrs ; 
 int /*<<< orphan*/  pmc_kthread_mtx ; 
 int vm_ndomains ; 

void
pmclog_shutdown()
{
	struct pmclog_buffer *plb;
	int domain;

	mtx_destroy(&pmc_kthread_mtx);

	for (domain = 0; domain < vm_ndomains; domain++) {
		while ((plb = TAILQ_FIRST(&pmc_dom_hdrs[domain]->pdbh_head)) != NULL) {
			TAILQ_REMOVE(&pmc_dom_hdrs[domain]->pdbh_head, plb, plb_next);
			free(plb->plb_base, M_PMC);
		}
		free(pmc_dom_hdrs[domain]->pdbh_plbs, M_PMC);
	}
}