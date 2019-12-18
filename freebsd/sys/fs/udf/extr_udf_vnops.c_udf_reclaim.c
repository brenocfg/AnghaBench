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
struct vop_reclaim_args {struct vnode* a_vp; } ;
struct vnode {int /*<<< orphan*/ * v_data; } ;
struct udf_node {int /*<<< orphan*/ * fentry; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_UDFFENTRY ; 
 struct udf_node* VTON (struct vnode*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udf_zone_node ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct udf_node*) ; 
 int /*<<< orphan*/  vfs_hash_remove (struct vnode*) ; 

__attribute__((used)) static int
udf_reclaim(struct vop_reclaim_args *a)
{
	struct vnode *vp;
	struct udf_node *unode;

	vp = a->a_vp;
	unode = VTON(vp);

	if (unode != NULL) {
		vfs_hash_remove(vp);

		if (unode->fentry != NULL)
			free(unode->fentry, M_UDFFENTRY);
		uma_zfree(udf_zone_node, unode);
		vp->v_data = NULL;
	}

	return (0);
}