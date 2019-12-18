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
struct autofs_node {int /*<<< orphan*/  an_name; int /*<<< orphan*/  an_vnode_lock; int /*<<< orphan*/  an_children; struct autofs_node* an_parent; int /*<<< orphan*/  an_callout; int /*<<< orphan*/  an_mount; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTOFS_ASSERT_XLOCKED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  M_AUTOFS ; 
 int /*<<< orphan*/  RB_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RB_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct autofs_node*) ; 
 int /*<<< orphan*/  autofs_node_tree ; 
 int /*<<< orphan*/  autofs_node_zone ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct autofs_node*) ; 

void
autofs_node_delete(struct autofs_node *anp)
{
	struct autofs_node *parent;

	AUTOFS_ASSERT_XLOCKED(anp->an_mount);
	KASSERT(RB_EMPTY(&anp->an_children), ("have children"));

	callout_drain(&anp->an_callout);

	parent = anp->an_parent;
	if (parent != NULL)
		RB_REMOVE(autofs_node_tree, &parent->an_children, anp);
	sx_destroy(&anp->an_vnode_lock);
	free(anp->an_name, M_AUTOFS);
	uma_zfree(autofs_node_zone, anp);
}