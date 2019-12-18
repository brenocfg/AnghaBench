#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * v_data; } ;
typedef  TYPE_1__ vnode_t ;
typedef  int /*<<< orphan*/  sfs_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  sfs_vnode_remove (TYPE_1__*) ; 

__attribute__((used)) static void *
sfs_reclaim_vnode(vnode_t *vp)
{
	sfs_node_t *node;
	void *data;

	sfs_vnode_remove(vp);
	data = vp->v_data;
	vp->v_data = NULL;
	return (data);
}