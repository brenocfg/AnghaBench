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
struct pmcpl_ct_node {int /*<<< orphan*/  pct_color; int /*<<< orphan*/ * pct_instr; scalar_t__ pct_instr_c; scalar_t__ pct_ninstr; int /*<<< orphan*/ * pct_arc; scalar_t__ pct_arc_c; scalar_t__ pct_narc; scalar_t__ pct_func; int /*<<< orphan*/ * pct_image; int /*<<< orphan*/ * pct_sym; int /*<<< orphan*/  pct_samples; } ;

/* Variables and functions */
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  PMCPL_PCT_WHITE ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 struct pmcpl_ct_node* malloc (int) ; 
 int /*<<< orphan*/  pmcpl_ct_samples_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct pmcpl_ct_node *
pmcpl_ct_node_allocate(void)
{
	struct pmcpl_ct_node *ct;

	if ((ct = malloc(sizeof(*ct))) == NULL)
		err(EX_OSERR, "ERROR: Cannot allocate callgraph node");

	pmcpl_ct_samples_init(&ct->pct_samples);

	ct->pct_sym	= NULL;
	ct->pct_image	= NULL;
	ct->pct_func	= 0;

	ct->pct_narc	= 0;
	ct->pct_arc_c	= 0;
	ct->pct_arc	= NULL;

	ct->pct_ninstr	= 0;
	ct->pct_instr_c	= 0;
	ct->pct_instr	= NULL;

	ct->pct_color   = PMCPL_PCT_WHITE;

	return (ct);
}