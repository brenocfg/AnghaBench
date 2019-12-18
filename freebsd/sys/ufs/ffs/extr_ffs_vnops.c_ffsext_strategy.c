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
struct vop_strategy_args {TYPE_1__* a_bp; struct vnode* a_vp; } ;
struct vnode {scalar_t__ v_type; } ;
typedef  int /*<<< orphan*/  daddr_t ;
struct TYPE_2__ {int /*<<< orphan*/  b_lblkno; } ;

/* Variables and functions */
 scalar_t__ I_IS_UFS2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UFS_NXADDR ; 
 scalar_t__ VFIFO ; 
 int VOP_STRATEGY_APV (int /*<<< orphan*/ *,struct vop_strategy_args*) ; 
 int /*<<< orphan*/  VTOI (struct vnode*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  ufs_fifoops ; 
 int /*<<< orphan*/  ufs_vnodeops ; 

__attribute__((used)) static int
ffsext_strategy(struct vop_strategy_args *ap)
/*
struct vop_strategy_args {
	struct vnodeop_desc *a_desc;
	struct vnode *a_vp;
	struct buf *a_bp;
};
*/
{
	struct vnode *vp;
	daddr_t lbn;

	vp = ap->a_vp;
	lbn = ap->a_bp->b_lblkno;
	if (I_IS_UFS2(VTOI(vp)) && lbn < 0 && lbn >= -UFS_NXADDR)
		return (VOP_STRATEGY_APV(&ufs_vnodeops, ap));
	if (vp->v_type == VFIFO)
		return (VOP_STRATEGY_APV(&ufs_fifoops, ap));
	panic("spec nodes went here");
}