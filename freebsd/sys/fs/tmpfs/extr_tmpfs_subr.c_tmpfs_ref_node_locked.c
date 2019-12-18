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
struct tmpfs_node {scalar_t__ tn_refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  TMPFS_NODE_ASSERT_LOCKED (struct tmpfs_node*) ; 
 scalar_t__ UINT_MAX ; 

void
tmpfs_ref_node_locked(struct tmpfs_node *node)
{

	TMPFS_NODE_ASSERT_LOCKED(node);
	KASSERT(node->tn_refcount > 0, ("node %p zero refcount", node));
	KASSERT(node->tn_refcount < UINT_MAX, ("node %p refcount %u", node,
	    node->tn_refcount));
	node->tn_refcount++;
}