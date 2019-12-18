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
struct tmpfs_mount {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TMPFS_LOCK (struct tmpfs_mount*) ; 
 int /*<<< orphan*/  TMPFS_NODE_LOCK (struct tmpfs_node*) ; 
 int /*<<< orphan*/  TMPFS_NODE_UNLOCK (struct tmpfs_node*) ; 
 int /*<<< orphan*/  TMPFS_UNLOCK (struct tmpfs_mount*) ; 
 int /*<<< orphan*/  tmpfs_free_node_locked (struct tmpfs_mount*,struct tmpfs_node*,int) ; 

void
tmpfs_free_node(struct tmpfs_mount *tmp, struct tmpfs_node *node)
{

	TMPFS_LOCK(tmp);
	TMPFS_NODE_LOCK(node);
	if (!tmpfs_free_node_locked(tmp, node, false)) {
		TMPFS_NODE_UNLOCK(node);
		TMPFS_UNLOCK(tmp);
	}
}