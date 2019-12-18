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
struct pmcpl_ct_node {int pct_narc; struct pmcpl_ct_node* pct_instr; struct pmcpl_ct_node* pct_arc; int /*<<< orphan*/  pct_samples; int /*<<< orphan*/  pcta_callid; int /*<<< orphan*/  pcta_samples; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct pmcpl_ct_node*) ; 
 int /*<<< orphan*/  pmcpl_ct_samples_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pmcpl_ct_node_free(struct pmcpl_ct_node *ct)
{
	int i;

	for (i = 0; i < ct->pct_narc; i++) {
		pmcpl_ct_samples_free(&ct->pct_arc[i].pcta_samples);
		pmcpl_ct_samples_free(&ct->pct_arc[i].pcta_callid);
	}

	pmcpl_ct_samples_free(&ct->pct_samples);
	free(ct->pct_arc);
	free(ct->pct_instr);
	free(ct);
}