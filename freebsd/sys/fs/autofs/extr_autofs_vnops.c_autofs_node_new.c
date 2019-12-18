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
struct autofs_node {int /*<<< orphan*/  an_children; struct autofs_mount* an_mount; struct autofs_node* an_parent; int /*<<< orphan*/  an_ctime; int /*<<< orphan*/  an_vnode_lock; int /*<<< orphan*/  an_callout; int /*<<< orphan*/  an_fileno; int /*<<< orphan*/  an_name; } ;
struct autofs_mount {int /*<<< orphan*/  am_last_fileno; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTOFS_ASSERT_XLOCKED (struct autofs_mount*) ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_AUTOFS ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  RB_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RB_INSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct autofs_node*) ; 
 int /*<<< orphan*/  SX_NOWITNESS ; 
 int /*<<< orphan*/  atomic_fetchadd_int (int /*<<< orphan*/ *,int) ; 
 scalar_t__ autofs_node_find (struct autofs_node*,char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  autofs_node_tree ; 
 int /*<<< orphan*/  autofs_node_zone ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  getnanotime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strdup (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strndup (char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_init_flags (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct autofs_node* uma_zalloc (int /*<<< orphan*/ ,int) ; 

int
autofs_node_new(struct autofs_node *parent, struct autofs_mount *amp,
    const char *name, int namelen, struct autofs_node **anpp)
{
	struct autofs_node *anp;

	if (parent != NULL) {
		AUTOFS_ASSERT_XLOCKED(parent->an_mount);

		KASSERT(autofs_node_find(parent, name, namelen, NULL) == ENOENT,
		    ("node \"%s\" already exists", name));
	}

	anp = uma_zalloc(autofs_node_zone, M_WAITOK | M_ZERO);
	if (namelen >= 0)
		anp->an_name = strndup(name, namelen, M_AUTOFS);
	else
		anp->an_name = strdup(name, M_AUTOFS);
	anp->an_fileno = atomic_fetchadd_int(&amp->am_last_fileno, 1);
	callout_init(&anp->an_callout, 1);
	/*
	 * The reason for SX_NOWITNESS here is that witness(4)
	 * cannot tell vnodes apart, so the following perfectly
	 * valid lock order...
	 *
	 * vnode lock A -> autofsvlk B -> vnode lock B
	 *
	 * ... gets reported as a LOR.
	 */
	sx_init_flags(&anp->an_vnode_lock, "autofsvlk", SX_NOWITNESS);
	getnanotime(&anp->an_ctime);
	anp->an_parent = parent;
	anp->an_mount = amp;
	if (parent != NULL)
		RB_INSERT(autofs_node_tree, &parent->an_children, anp);
	RB_INIT(&anp->an_children);

	*anpp = anp;
	return (0);
}