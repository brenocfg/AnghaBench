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
struct vop_access_args {int a_accmode; int /*<<< orphan*/  a_cred; struct vnode* a_vp; } ;
struct vnode {int v_type; } ;
struct udf_node {TYPE_1__* fentry; } ;
typedef  int /*<<< orphan*/  mode_t ;
typedef  int accmode_t ;
struct TYPE_2__ {int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;

/* Variables and functions */
 int EROFS ; 
#define  VDIR 130 
#define  VLNK 129 
#define  VREG 128 
 struct udf_node* VTON (struct vnode*) ; 
 int VWRITE ; 
 int /*<<< orphan*/  udf_permtomode (struct udf_node*) ; 
 int vaccess (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
udf_access(struct vop_access_args *a)
{
	struct vnode *vp;
	struct udf_node *node;
	accmode_t accmode;
	mode_t mode;

	vp = a->a_vp;
	node = VTON(vp);
	accmode = a->a_accmode;

	if (accmode & VWRITE) {
		switch (vp->v_type) {
		case VDIR:
		case VLNK:
		case VREG:
			return (EROFS);
			/* NOT REACHED */
		default:
			break;
		}
	}

	mode = udf_permtomode(node);

	return (vaccess(vp->v_type, mode, node->fentry->uid, node->fentry->gid,
	    accmode, a->a_cred, NULL));
}