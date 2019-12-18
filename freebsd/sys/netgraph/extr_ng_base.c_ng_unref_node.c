#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* node_p ;
struct TYPE_9__ {int /*<<< orphan*/  q_mtx; } ;
struct TYPE_11__ {TYPE_1__ nd_input_queue; TYPE_2__* nd_type; int /*<<< orphan*/  nd_refs; int /*<<< orphan*/  nd_vnet; } ;
struct TYPE_10__ {int /*<<< orphan*/  refs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURVNET_RESTORE () ; 
 int /*<<< orphan*/  CURVNET_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDHASH_WLOCK () ; 
 int /*<<< orphan*/  IDHASH_WUNLOCK () ; 
 int /*<<< orphan*/  LIST_REMOVE (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NAMEHASH_WLOCK () ; 
 int /*<<< orphan*/  NAMEHASH_WUNLOCK () ; 
 int /*<<< orphan*/  NG_FREE_NODE (TYPE_3__*) ; 
 scalar_t__ NG_NODE_HAS_NAME (TYPE_3__*) ; 
 int /*<<< orphan*/  V_ng_named_nodes ; 
 int /*<<< orphan*/  V_ng_nodes ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nd_idnodes ; 
 int /*<<< orphan*/  nd_nodes ; 
 TYPE_3__ ng_deadnode ; 
 scalar_t__ refcount_release (int /*<<< orphan*/ *) ; 

void
ng_unref_node(node_p node)
{

	if (node == &ng_deadnode)
		return;

	CURVNET_SET(node->nd_vnet);

	if (refcount_release(&node->nd_refs)) { /* we were the last */

		node->nd_type->refs--; /* XXX maybe should get types lock? */
		NAMEHASH_WLOCK();
		if (NG_NODE_HAS_NAME(node)) {
			V_ng_named_nodes--;
			LIST_REMOVE(node, nd_nodes);
		}
		NAMEHASH_WUNLOCK();

		IDHASH_WLOCK();
		V_ng_nodes--;
		LIST_REMOVE(node, nd_idnodes);
		IDHASH_WUNLOCK();

		mtx_destroy(&node->nd_input_queue.q_mtx);
		NG_FREE_NODE(node);
	}
	CURVNET_RESTORE();
}