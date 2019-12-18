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
struct TYPE_2__ {struct t4_offload_policy* bf_insns; } ;
struct t4_offload_policy {int nrules; struct t4_offload_policy* rule; TYPE_1__ bpf_prog; } ;
struct offload_rule {int nrules; struct offload_rule* rule; TYPE_1__ bpf_prog; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_CXGBE ; 
 int /*<<< orphan*/  free (struct t4_offload_policy*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
free_offload_policy(struct t4_offload_policy *op)
{
	struct offload_rule *r;
	int i;

	if (op == NULL)
		return;

	r = &op->rule[0];
	for (i = 0; i < op->nrules; i++, r++) {
		free(r->bpf_prog.bf_insns, M_CXGBE);
	}
	free(op->rule, M_CXGBE);
	free(op, M_CXGBE);
}