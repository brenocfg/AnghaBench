#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* node_p ;
typedef  TYPE_3__* hook_p ;
struct TYPE_17__ {int hk_refs; TYPE_2__* hk_node; int /*<<< orphan*/ * hk_peer; int /*<<< orphan*/  hk_flags; } ;
struct TYPE_16__ {int /*<<< orphan*/  nd_numhooks; int /*<<< orphan*/  nd_hooks; TYPE_1__* nd_type; } ;
struct TYPE_15__ {int (* newhook ) (TYPE_2__*,TYPE_3__*,char const*) ;} ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HK_INVALID ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_ALLOC_HOOK (TYPE_3__*) ; 
 int /*<<< orphan*/  NG_HOOKSIZ ; 
 int /*<<< orphan*/  NG_HOOK_NAME (TYPE_3__*) ; 
 int /*<<< orphan*/  NG_HOOK_REF (TYPE_3__*) ; 
 int /*<<< orphan*/  NG_HOOK_UNREF (TYPE_3__*) ; 
 int /*<<< orphan*/  NG_NODE_REF (TYPE_2__*) ; 
 int /*<<< orphan*/  TRAP_ERROR () ; 
 int /*<<< orphan*/  hk_hooks ; 
 int /*<<< orphan*/  ng_deadhook ; 
 int /*<<< orphan*/ * ng_findhook (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_2__*,TYPE_3__*,char const*) ; 

__attribute__((used)) static int
ng_add_hook(node_p node, const char *name, hook_p *hookp)
{
	hook_p hook;
	int error = 0;

	/* Check that the given name is good */
	if (name == NULL) {
		TRAP_ERROR();
		return (EINVAL);
	}
	if (ng_findhook(node, name) != NULL) {
		TRAP_ERROR();
		return (EEXIST);
	}

	/* Allocate the hook and link it up */
	NG_ALLOC_HOOK(hook);
	if (hook == NULL) {
		TRAP_ERROR();
		return (ENOMEM);
	}
	hook->hk_refs = 1;		/* add a reference for us to return */
	hook->hk_flags = HK_INVALID;
	hook->hk_peer = &ng_deadhook;	/* start off this way */
	hook->hk_node = node;
	NG_NODE_REF(node);		/* each hook counts as a reference */

	/* Set hook name */
	strlcpy(NG_HOOK_NAME(hook), name, NG_HOOKSIZ);

	/*
	 * Check if the node type code has something to say about it
	 * If it fails, the unref of the hook will also unref the node.
	 */
	if (node->nd_type->newhook != NULL) {
		if ((error = (*node->nd_type->newhook)(node, hook, name))) {
			NG_HOOK_UNREF(hook);	/* this frees the hook */
			return (error);
		}
	}
	/*
	 * The 'type' agrees so far, so go ahead and link it in.
	 * We'll ask again later when we actually connect the hooks.
	 */
	LIST_INSERT_HEAD(&node->nd_hooks, hook, hk_hooks);
	node->nd_numhooks++;
	NG_HOOK_REF(hook);	/* one for the node */

	if (hookp)
		*hookp = hook;
	return (0);
}