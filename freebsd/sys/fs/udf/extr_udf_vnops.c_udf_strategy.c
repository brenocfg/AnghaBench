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
typedef  int /*<<< orphan*/  uint32_t ;
struct vop_strategy_args {struct vnode* a_vp; struct buf* a_bp; } ;
struct vnode {int dummy; } ;
struct udf_node {TYPE_1__* udfmp; } ;
struct bufobj {int dummy; } ;
struct buf {int b_blkno; int b_lblkno; int /*<<< orphan*/  b_iooffset; } ;
typedef  int /*<<< orphan*/  off_t ;
typedef  int daddr_t ;
struct TYPE_2__ {int bshift; struct bufobj* im_bo; } ;

/* Variables and functions */
 int /*<<< orphan*/  BO_STRATEGY (struct bufobj*,struct buf*) ; 
 int DEV_BSHIFT ; 
 struct udf_node* VTON (struct vnode*) ; 
 int /*<<< orphan*/  bufdone (struct buf*) ; 
 int /*<<< orphan*/  clrbuf (struct buf*) ; 
 int /*<<< orphan*/  dbtob (int) ; 
 int /*<<< orphan*/  lblktosize (TYPE_1__*,int) ; 
 int udf_bmap_internal (struct udf_node*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
udf_strategy(struct vop_strategy_args *a)
{
	struct buf *bp;
	struct vnode *vp;
	struct udf_node *node;
	struct bufobj *bo;
	off_t offset;
	uint32_t maxsize;
	daddr_t sector;
	int error;

	bp = a->a_bp;
	vp = a->a_vp;
	node = VTON(vp);

	if (bp->b_blkno == bp->b_lblkno) {
		offset = lblktosize(node->udfmp, bp->b_lblkno);
		error = udf_bmap_internal(node, offset, &sector, &maxsize);
		if (error) {
			clrbuf(bp);
			bp->b_blkno = -1;
			bufdone(bp);
			return (0);
		}
		/* bmap gives sector numbers, bio works with device blocks */
		bp->b_blkno = sector << (node->udfmp->bshift - DEV_BSHIFT);
	}
	bo = node->udfmp->im_bo;
	bp->b_iooffset = dbtob(bp->b_blkno);
	BO_STRATEGY(bo, bp);
	return (0);
}