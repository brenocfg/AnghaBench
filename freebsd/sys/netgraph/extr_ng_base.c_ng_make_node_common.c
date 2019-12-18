#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct ng_type {int /*<<< orphan*/  refs; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__* node_p ;
struct TYPE_9__ {scalar_t__ q_flags; int /*<<< orphan*/  queue; } ;
struct TYPE_8__ {scalar_t__ nd_ID; int /*<<< orphan*/  nd_hooks; TYPE_3__ nd_input_queue; int /*<<< orphan*/  nd_vnet; struct ng_type* nd_type; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IDHASH_WLOCK () ; 
 int /*<<< orphan*/  IDHASH_WUNLOCK () ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_ALLOC_NODE (TYPE_1__*) ; 
 int /*<<< orphan*/  NG_IDHASH_FIND (scalar_t__,TYPE_1__*) ; 
 size_t NG_IDHASH_FN (scalar_t__) ; 
 int /*<<< orphan*/  NG_NODE_REF (TYPE_1__*) ; 
 int /*<<< orphan*/  NG_QUEUE_LOCK_INIT (TYPE_3__*) ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRAP_ERROR () ; 
 int /*<<< orphan*/  V_nextID ; 
 int /*<<< orphan*/ * V_ng_ID_hash ; 
 int V_ng_ID_hmask ; 
 int V_ng_nodes ; 
 int /*<<< orphan*/  curvnet ; 
 int /*<<< orphan*/  nd_idnodes ; 
 int /*<<< orphan*/  ng_ID_rehash () ; 
 int /*<<< orphan*/ * ng_findtype (int /*<<< orphan*/ ) ; 

int
ng_make_node_common(struct ng_type *type, node_p *nodepp)
{
	node_p node;

	/* Require the node type to have been already installed */
	if (ng_findtype(type->name) == NULL) {
		TRAP_ERROR();
		return (EINVAL);
	}

	/* Make a node and try attach it to the type */
	NG_ALLOC_NODE(node);
	if (node == NULL) {
		TRAP_ERROR();
		return (ENOMEM);
	}
	node->nd_type = type;
#ifdef VIMAGE
	node->nd_vnet = curvnet;
#endif
	NG_NODE_REF(node);				/* note reference */
	type->refs++;

	NG_QUEUE_LOCK_INIT(&node->nd_input_queue);
	STAILQ_INIT(&node->nd_input_queue.queue);
	node->nd_input_queue.q_flags = 0;

	/* Initialize hook list for new node */
	LIST_INIT(&node->nd_hooks);

	/* Get an ID and put us in the hash chain. */
	IDHASH_WLOCK();
	for (;;) { /* wrap protection, even if silly */
		node_p node2 = NULL;
		node->nd_ID = V_nextID++; /* 137/sec for 1 year before wrap */

		/* Is there a problem with the new number? */
		NG_IDHASH_FIND(node->nd_ID, node2); /* already taken? */
		if ((node->nd_ID != 0) && (node2 == NULL)) {
			break;
		}
	}
	V_ng_nodes++;
	if (V_ng_nodes * 2 > V_ng_ID_hmask)
		ng_ID_rehash();
	LIST_INSERT_HEAD(&V_ng_ID_hash[NG_IDHASH_FN(node->nd_ID)], node,
	    nd_idnodes);
	IDHASH_WUNLOCK();

	/* Done */
	*nodepp = node;
	return (0);
}