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
struct pf_ruleset {scalar_t__ tables; TYPE_4__* anchor; TYPE_3__* rules; scalar_t__ topen; } ;
struct pf_anchor {struct pf_ruleset ruleset; int /*<<< orphan*/  children; } ;
struct TYPE_9__ {scalar_t__ refcnt; struct pf_anchor* parent; int /*<<< orphan*/  children; } ;
struct TYPE_7__ {scalar_t__ open; int /*<<< orphan*/  ptr; } ;
struct TYPE_6__ {int /*<<< orphan*/  ptr; } ;
struct TYPE_8__ {TYPE_2__ inactive; TYPE_1__ active; } ;

/* Variables and functions */
 int PF_RULESET_MAX ; 
 int /*<<< orphan*/  RB_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RB_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_pf_anchors ; 
 int /*<<< orphan*/  pf_anchor_global ; 
 int /*<<< orphan*/  pf_anchor_node ; 
 struct pf_ruleset pf_main_ruleset ; 
 int /*<<< orphan*/  rs_free (TYPE_4__*) ; 

void
pf_remove_if_empty_ruleset(struct pf_ruleset *ruleset)
{
	struct pf_anchor	*parent;
	int			 i;

	while (ruleset != NULL) {
		if (ruleset == &pf_main_ruleset || ruleset->anchor == NULL ||
		    !RB_EMPTY(&ruleset->anchor->children) ||
		    ruleset->anchor->refcnt > 0 || ruleset->tables > 0 ||
		    ruleset->topen)
			return;
		for (i = 0; i < PF_RULESET_MAX; ++i)
			if (!TAILQ_EMPTY(ruleset->rules[i].active.ptr) ||
			    !TAILQ_EMPTY(ruleset->rules[i].inactive.ptr) ||
			    ruleset->rules[i].inactive.open)
				return;
		RB_REMOVE(pf_anchor_global, &V_pf_anchors, ruleset->anchor);
		if ((parent = ruleset->anchor->parent) != NULL)
			RB_REMOVE(pf_anchor_node, &parent->children,
			    ruleset->anchor);
		rs_free(ruleset->anchor);
		if (parent == NULL)
			return;
		ruleset = &parent->ruleset;
	}
}