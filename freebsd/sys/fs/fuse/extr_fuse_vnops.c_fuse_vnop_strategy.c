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
struct vop_strategy_args {struct buf* a_bp; struct vnode* a_vp; } ;
struct vnode {int dummy; } ;
struct buf {int /*<<< orphan*/  b_error; int /*<<< orphan*/  b_ioflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_ERROR ; 
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  bufdone (struct buf*) ; 
 int /*<<< orphan*/  fuse_io_strategy (struct vnode*,struct buf*) ; 
 scalar_t__ fuse_isdeadfs (struct vnode*) ; 

__attribute__((used)) static int
fuse_vnop_strategy(struct vop_strategy_args *ap)
{
	struct vnode *vp = ap->a_vp;
	struct buf *bp = ap->a_bp;

	if (!vp || fuse_isdeadfs(vp)) {
		bp->b_ioflags |= BIO_ERROR;
		bp->b_error = ENXIO;
		bufdone(bp);
		return 0;
	}

	/*
	 * VOP_STRATEGY always returns zero and signals error via bp->b_ioflags.
	 * fuse_io_strategy sets bp's error fields
	 */
	(void)fuse_io_strategy(vp, bp);

	return 0;
}