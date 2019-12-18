#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* node_p ;
typedef  int /*<<< orphan*/  item_p ;
typedef  TYPE_3__* hook_p ;
struct TYPE_20__ {int /*<<< orphan*/  hk_flags; TYPE_2__* hk_node; struct TYPE_20__* hk_peer; int /*<<< orphan*/  hk_name; } ;
struct TYPE_19__ {TYPE_1__* nd_type; int /*<<< orphan*/  nd_numhooks; int /*<<< orphan*/  nd_hooks; } ;
struct TYPE_18__ {int (* newhook ) (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ ) ;int (* connect ) (TYPE_3__*) ;} ;

/* Variables and functions */
 int EEXIST ; 
 int ENOENT ; 
 int /*<<< orphan*/  ERROUT (int) ; 
 int /*<<< orphan*/  HK_INVALID ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_FREE_ITEM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_HOOK_NAME (TYPE_3__*) ; 
 int /*<<< orphan*/  NG_HOOK_REF (TYPE_3__*) ; 
 int /*<<< orphan*/  NG_NODE_REF (TYPE_2__*) ; 
 int /*<<< orphan*/  NG_REUSE_ITEM ; 
 int /*<<< orphan*/  TOPOLOGY_RLOCK () ; 
 int /*<<< orphan*/  TOPOLOGY_RUNLOCK () ; 
 int /*<<< orphan*/  TRAP_ERROR () ; 
 int /*<<< orphan*/  hk_hooks ; 
 int /*<<< orphan*/  ng_con_part3 ; 
 TYPE_3__ ng_deadhook ; 
 int /*<<< orphan*/  ng_destroy_hook (TYPE_3__*) ; 
 int /*<<< orphan*/ * ng_findhook (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int ng_send_fn2 (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int stub1 (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int stub2 (TYPE_3__*) ; 

__attribute__((used)) static int
ng_con_part2(node_p node, item_p item, hook_p hook)
{
	hook_p	peer;
	int	error = 0;

	/*
	 * When we run, we know that the node 'node' is locked for us.
	 * Our caller has a reference on the hook.
	 * Our caller has a reference on the node.
	 * (In this case our caller is ng_apply_item() ).
	 * The peer hook has a reference on the hook.
	 * our node pointer points to the 'dead' node.
	 * First check the hook name is unique.
	 * Should not happen because we checked before queueing this.
	 */
	if (ng_findhook(node, NG_HOOK_NAME(hook)) != NULL) {
		TRAP_ERROR();
		ng_destroy_hook(hook); /* should destroy peer too */
		printf("failed in ng_con_part2()\n");
		ERROUT(EEXIST);
	}
	/*
	 * Check if the node type code has something to say about it
	 * If it fails, the unref of the hook will also unref the attached node,
	 * however since that node is 'ng_deadnode' this will do nothing.
	 * The peer hook will also be destroyed.
	 */
	if (node->nd_type->newhook != NULL) {
		if ((error = (*node->nd_type->newhook)(node, hook,
		    hook->hk_name))) {
			ng_destroy_hook(hook); /* should destroy peer too */
			printf("failed in ng_con_part2()\n");
			ERROUT(error);
		}
	}

	/*
	 * The 'type' agrees so far, so go ahead and link it in.
	 * We'll ask again later when we actually connect the hooks.
	 */
	hook->hk_node = node;		/* just overwrite ng_deadnode */
	NG_NODE_REF(node);		/* each hook counts as a reference */
	LIST_INSERT_HEAD(&node->nd_hooks, hook, hk_hooks);
	node->nd_numhooks++;
	NG_HOOK_REF(hook);	/* one for the node */
	
	/*
	 * We now have a symmetrical situation, where both hooks have been
	 * linked to their nodes, the newhook methods have been called
	 * And the references are all correct. The hooks are still marked
	 * as invalid, as we have not called the 'connect' methods
	 * yet.
	 * We can call the local one immediately as we have the
	 * node locked, but we need to queue the remote one.
	 */
	if (hook->hk_node->nd_type->connect) {
		if ((error = (*hook->hk_node->nd_type->connect) (hook))) {
			ng_destroy_hook(hook);	/* also zaps peer */
			printf("failed in ng_con_part2(A)\n");
			ERROUT(error);
		}
	}

	/*
	 * Acquire topo mutex to avoid race with ng_destroy_hook().
	 */
	TOPOLOGY_RLOCK();
	peer = hook->hk_peer;
	if (peer == &ng_deadhook) {
		TOPOLOGY_RUNLOCK();
		printf("failed in ng_con_part2(B)\n");
		ng_destroy_hook(hook);
		ERROUT(ENOENT);
	}
	TOPOLOGY_RUNLOCK();

	if ((error = ng_send_fn2(peer->hk_node, peer, item, &ng_con_part3,
	    NULL, 0, NG_REUSE_ITEM))) {
		printf("failed in ng_con_part2(C)\n");
		ng_destroy_hook(hook);	/* also zaps peer */
		return (error);		/* item was consumed. */
	}
	hook->hk_flags &= ~HK_INVALID; /* need both to be able to work */
	return (0);			/* item was consumed. */
done:
	NG_FREE_ITEM(item);
	return (error);
}