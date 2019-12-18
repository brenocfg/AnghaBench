#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vnode {TYPE_1__* v_data; } ;
struct TYPE_2__ {scalar_t__ sn_id; scalar_t__ sn_parent_id; } ;
typedef  TYPE_1__ sfs_node_t ;

/* Variables and functions */

__attribute__((used)) static int
sfs_compare_ids(struct vnode *vp, void *arg)
{
	sfs_node_t *n1 = vp->v_data;
	sfs_node_t *n2 = arg;
	bool equal;

	equal = n1->sn_id == n2->sn_id &&
	    n1->sn_parent_id == n2->sn_parent_id;

	/* Zero means equality. */
	return (!equal);
}