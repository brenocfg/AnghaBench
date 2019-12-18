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
struct tmpfs_node {int tn_status; } ;
struct tmpfs_mount {scalar_t__ tm_ronly; } ;

/* Variables and functions */
 int /*<<< orphan*/  TMPFS_NODE_LOCK (struct tmpfs_node*) ; 
 int /*<<< orphan*/  TMPFS_NODE_UNLOCK (struct tmpfs_node*) ; 

void
tmpfs_set_status(struct tmpfs_mount *tm, struct tmpfs_node *node, int status)
{

	if ((node->tn_status & status) == status || tm->tm_ronly)
		return;
	TMPFS_NODE_LOCK(node);
	node->tn_status |= status;
	TMPFS_NODE_UNLOCK(node);
}