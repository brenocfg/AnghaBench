#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct pf_ruleset {TYPE_3__* rules; } ;
struct pf_rule {int quick; TYPE_1__* anchor; } ;
struct pf_anchor_stackframe {struct pf_ruleset* rs; TYPE_4__* child; } ;
struct pf_anchor_node {int dummy; } ;
struct TYPE_9__ {struct pf_ruleset ruleset; } ;
struct TYPE_7__ {int /*<<< orphan*/  ptr; } ;
struct TYPE_8__ {TYPE_2__ active; } ;
struct TYPE_6__ {struct pf_anchor_node children; } ;

/* Variables and functions */
 scalar_t__ PF_ANCHOR_MATCH (struct pf_anchor_stackframe*) ; 
 struct pf_rule* PF_ANCHOR_RULE (struct pf_anchor_stackframe*) ; 
 int /*<<< orphan*/  PF_ANCHOR_SET_MATCH (struct pf_anchor_stackframe*) ; 
 int /*<<< orphan*/  PF_RULES_RASSERT () ; 
 TYPE_4__* RB_NEXT (int /*<<< orphan*/ ,struct pf_anchor_node*,TYPE_4__*) ; 
 struct pf_rule* TAILQ_FIRST (int /*<<< orphan*/ ) ; 
 struct pf_rule* TAILQ_NEXT (struct pf_rule*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entries ; 
 int /*<<< orphan*/  pf_anchor_node ; 

int
pf_step_out_of_anchor(struct pf_anchor_stackframe *stack, int *depth,
    struct pf_ruleset **rs, int n, struct pf_rule **r, struct pf_rule **a,
    int *match)
{
	struct pf_anchor_stackframe	*f;
	struct pf_rule *fr;
	int quick = 0;

	PF_RULES_RASSERT();

	do {
		if (*depth <= 0)
			break;
		f = stack + *depth - 1;
		fr = PF_ANCHOR_RULE(f);
		if (f->child != NULL) {
			struct pf_anchor_node *parent;

			/*
			 * This block traverses through
			 * a wildcard anchor.
			 */
			parent = &fr->anchor->children;
			if (match != NULL && *match) {
				/*
				 * If any of "*" matched, then
				 * "foo/ *" matched, mark frame
				 * appropriately.
				 */
				PF_ANCHOR_SET_MATCH(f);
				*match = 0;
			}
			f->child = RB_NEXT(pf_anchor_node, parent, f->child);
			if (f->child != NULL) {
				*rs = &f->child->ruleset;
				*r = TAILQ_FIRST((*rs)->rules[n].active.ptr);
				if (*r == NULL)
					continue;
				else
					break;
			}
		}
		(*depth)--;
		if (*depth == 0 && a != NULL)
			*a = NULL;
		*rs = f->rs;
		if (PF_ANCHOR_MATCH(f) || (match != NULL && *match))
			quick = fr->quick;
		*r = TAILQ_NEXT(fr, entries);
	} while (*r == NULL);

	return (quick);
}