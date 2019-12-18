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
struct tmpfs_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TMPFS_NODE_LOCK (struct tmpfs_node*) ; 
 int /*<<< orphan*/  TMPFS_NODE_UNLOCK (struct tmpfs_node*) ; 
 int /*<<< orphan*/  tmpfs_ref_node_locked (struct tmpfs_node*) ; 

void
tmpfs_ref_node(struct tmpfs_node *node)
{

	TMPFS_NODE_LOCK(node);
	tmpfs_ref_node_locked(node);
	TMPFS_NODE_UNLOCK(node);
}