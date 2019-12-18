#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* node_p ;
typedef  int /*<<< orphan*/ * hook_p ;
struct TYPE_13__ {int nd_flags; TYPE_1__* nd_type; int /*<<< orphan*/  nd_hooks; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* shutdown ) (TYPE_2__*) ;int /*<<< orphan*/  (* close ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/ * LIST_FIRST (int /*<<< orphan*/ *) ; 
 int NGF_CLOSING ; 
 int NGF_INVALID ; 
 scalar_t__ NG_NODE_IS_VALID (TYPE_2__*) ; 
 int /*<<< orphan*/  NG_NODE_REF (TYPE_2__*) ; 
 int /*<<< orphan*/  NG_NODE_UNREF (TYPE_2__*) ; 
 TYPE_2__ ng_deadnode ; 
 int /*<<< orphan*/  ng_destroy_hook (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ng_flush_input_queue (TYPE_2__*) ; 
 int /*<<< orphan*/  ng_unname (TYPE_2__*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*) ; 

void
ng_rmnode(node_p node, hook_p dummy1, void *dummy2, int dummy3)
{
	hook_p hook;

	/* Check if it's already shutting down */
	if ((node->nd_flags & NGF_CLOSING) != 0)
		return;

	if (node == &ng_deadnode) {
		printf ("shutdown called on deadnode\n");
		return;
	}

	/* Add an extra reference so it doesn't go away during this */
	NG_NODE_REF(node);

	/*
	 * Mark it invalid so any newcomers know not to try use it
	 * Also add our own mark so we can't recurse
	 * note that NGF_INVALID does not do this as it's also set during
	 * creation
	 */
	node->nd_flags |= NGF_INVALID|NGF_CLOSING;

	/* If node has its pre-shutdown method, then call it first*/
	if (node->nd_type && node->nd_type->close)
		(*node->nd_type->close)(node);

	/* Notify all remaining connected nodes to disconnect */
	while ((hook = LIST_FIRST(&node->nd_hooks)) != NULL)
		ng_destroy_hook(hook);

	/*
	 * Drain the input queue forceably.
	 * it has no hooks so what's it going to do, bleed on someone?
	 * Theoretically we came here from a queue entry that was added
	 * Just before the queue was closed, so it should be empty anyway.
	 * Also removes us from worklist if needed.
	 */
	ng_flush_input_queue(node);

	/* Ask the type if it has anything to do in this case */
	if (node->nd_type && node->nd_type->shutdown) {
		(*node->nd_type->shutdown)(node);
		if (NG_NODE_IS_VALID(node)) {
			/*
			 * Well, blow me down if the node code hasn't declared
			 * that it doesn't want to die.
			 * Presumably it is a persistent node.
			 * If we REALLY want it to go away,
			 *  e.g. hardware going away,
			 * Our caller should set NGF_REALLY_DIE in nd_flags.
			 */
			node->nd_flags &= ~(NGF_INVALID|NGF_CLOSING);
			NG_NODE_UNREF(node); /* Assume they still have theirs */
			return;
		}
	} else {				/* do the default thing */
		NG_NODE_UNREF(node);
	}

	ng_unname(node); /* basically a NOP these days */

	/*
	 * Remove extra reference, possibly the last
	 * Possible other holders of references may include
	 * timeout callouts, but theoretically the node's supposed to
	 * have cancelled them. Possibly hardware dependencies may
	 * force a driver to 'linger' with a reference.
	 */
	NG_NODE_UNREF(node);
}