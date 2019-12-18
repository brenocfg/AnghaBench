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
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/  ng_ID_t ;
typedef  int /*<<< orphan*/  item_p ;
typedef  int /*<<< orphan*/ * hook_p ;

/* Variables and functions */
 int ENETDOWN ; 
 int /*<<< orphan*/  ITEM_DEBUG_CHECKS ; 
 int /*<<< orphan*/  NGI_SET_HOOK (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NGI_SET_NODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_FREE_ITEM (int /*<<< orphan*/ ) ; 
 scalar_t__ NG_HOOK_NOT_VALID (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NG_HOOK_PEER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NG_HOOK_REF (int /*<<< orphan*/ *) ; 
 scalar_t__ NG_NODE_NOT_VALID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_NODE_REF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_PEER_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SET_RETADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TOPOLOGY_RLOCK () ; 
 int /*<<< orphan*/  TOPOLOGY_RUNLOCK () ; 
 int /*<<< orphan*/  TRAP_ERROR () ; 

int
ng_address_hook(node_p here, item_p item, hook_p hook, ng_ID_t retaddr)
{
	hook_p peer;
	node_p peernode;
	ITEM_DEBUG_CHECKS;
	/*
	 * Quick sanity check..
	 * Since a hook holds a reference on its node, once we know
	 * that the peer is still connected (even if invalid,) we know
	 * that the peer node is present, though maybe invalid.
	 */
	TOPOLOGY_RLOCK();
	if ((hook == NULL) || NG_HOOK_NOT_VALID(hook) ||
	    NG_HOOK_NOT_VALID(peer = NG_HOOK_PEER(hook)) ||
	    NG_NODE_NOT_VALID(peernode = NG_PEER_NODE(hook))) {
		NG_FREE_ITEM(item);
		TRAP_ERROR();
		TOPOLOGY_RUNLOCK();
		return (ENETDOWN);
	}

	/*
	 * Transfer our interest to the other (peer) end.
	 */
	NG_HOOK_REF(peer);
	NG_NODE_REF(peernode);
	NGI_SET_HOOK(item, peer);
	NGI_SET_NODE(item, peernode);
	SET_RETADDR(item, here, retaddr);

	TOPOLOGY_RUNLOCK();

	return (0);
}