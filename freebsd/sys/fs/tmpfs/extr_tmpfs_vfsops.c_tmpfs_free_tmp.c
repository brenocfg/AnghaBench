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
struct tmpfs_mount {scalar_t__ tm_refcount; scalar_t__ tm_pages_used; scalar_t__ tm_nodes_inuse; int /*<<< orphan*/  tm_allnode_lock; int /*<<< orphan*/  tm_node_pool; int /*<<< orphan*/  tm_dirent_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  M_TMPFSMNT ; 
 int /*<<< orphan*/  TMPFS_UNLOCK (struct tmpfs_mount*) ; 
 int /*<<< orphan*/  free (struct tmpfs_mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uma_zdestroy (int /*<<< orphan*/ ) ; 

void
tmpfs_free_tmp(struct tmpfs_mount *tmp)
{

	MPASS(tmp->tm_refcount > 0);
	tmp->tm_refcount--;
	if (tmp->tm_refcount > 0) {
		TMPFS_UNLOCK(tmp);
		return;
	}
	TMPFS_UNLOCK(tmp);

	uma_zdestroy(tmp->tm_dirent_pool);
	uma_zdestroy(tmp->tm_node_pool);

	mtx_destroy(&tmp->tm_allnode_lock);
	MPASS(tmp->tm_pages_used == 0);
	MPASS(tmp->tm_nodes_inuse == 0);

	free(tmp, M_TMPFSMNT);
}