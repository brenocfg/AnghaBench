#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/  item_p ;
typedef  TYPE_3__* hook_p ;
struct TYPE_10__ {int /*<<< orphan*/  hk_flags; TYPE_2__* hk_node; } ;
struct TYPE_9__ {TYPE_1__* nd_type; } ;
struct TYPE_8__ {int (* connect ) (TYPE_3__*) ;} ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  ERROUT (int) ; 
 int /*<<< orphan*/  HK_INVALID ; 
 int /*<<< orphan*/  NG_FREE_ITEM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NG_HOOK_NODE (TYPE_3__*) ; 
 int /*<<< orphan*/  ng_deadnode ; 
 int /*<<< orphan*/  ng_destroy_hook (TYPE_3__*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int stub1 (TYPE_3__*) ; 

__attribute__((used)) static int
ng_con_part3(node_p node, item_p item, hook_p hook)
{
	int	error = 0;

	/*
	 * When we run, we know that the node 'node' is locked for us.
	 * Our caller has a reference on the hook.
	 * Our caller has a reference on the node.
	 * (In this case our caller is ng_apply_item() ).
	 * The peer hook has a reference on the hook.
	 * We are all set up except for the final call to the node, and
	 * the clearing of the INVALID flag.
	 */
	if (NG_HOOK_NODE(hook) == &ng_deadnode) {
		/*
		 * The node must have been freed again since we last visited
		 * here. ng_destry_hook() has this effect but nothing else does.
		 * We should just release our references and
		 * free anything we can think of.
		 * Since we know it's been destroyed, and it's our caller
		 * that holds the references, just return.
		 */
		ERROUT(ENOENT);
	}
	if (hook->hk_node->nd_type->connect) {
		if ((error = (*hook->hk_node->nd_type->connect) (hook))) {
			ng_destroy_hook(hook);	/* also zaps peer */
			printf("failed in ng_con_part3()\n");
			ERROUT(error);
		}
	}
	/*
	 *  XXX this is wrong for SMP. Possibly we need
	 * to separate out 'create' and 'invalid' flags.
	 * should only set flags on hooks we have locked under our node.
	 */
	hook->hk_flags &= ~HK_INVALID;
done:
	NG_FREE_ITEM(item);
	return (error);
}