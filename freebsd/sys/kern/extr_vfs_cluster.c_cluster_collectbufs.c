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
struct vnode {int v_lastw; int v_cstart; } ;
struct cluster_save {int bs_nchildren; struct buf** bs_children; } ;
struct buf {scalar_t__ b_blkno; scalar_t__ b_lblkno; int /*<<< orphan*/  b_bcount; } ;
typedef  int daddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_SEGMENT ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  NOCRED ; 
 int /*<<< orphan*/  VOP_BMAP (struct vnode*,scalar_t__,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bread_gb (struct vnode*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct buf**) ; 
 int /*<<< orphan*/  brelse (struct buf*) ; 
 int /*<<< orphan*/  free (struct cluster_save*,int /*<<< orphan*/ ) ; 
 struct cluster_save* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct cluster_save *
cluster_collectbufs(struct vnode *vp, struct buf *last_bp, int gbflags)
{
	struct cluster_save *buflist;
	struct buf *bp;
	daddr_t lbn;
	int i, j, len, error;

	len = vp->v_lastw - vp->v_cstart + 1;
	buflist = malloc(sizeof(struct buf *) * (len + 1) + sizeof(*buflist),
	    M_SEGMENT, M_WAITOK);
	buflist->bs_nchildren = 0;
	buflist->bs_children = (struct buf **) (buflist + 1);
	for (lbn = vp->v_cstart, i = 0; i < len; lbn++, i++) {
		error = bread_gb(vp, lbn, last_bp->b_bcount, NOCRED,
		    gbflags, &bp);
		if (error != 0) {
			/*
			 * If read fails, release collected buffers
			 * and return failure.
			 */
			for (j = 0; j < i; j++)
				brelse(buflist->bs_children[j]);
			free(buflist, M_SEGMENT);
			return (NULL);
		}
		buflist->bs_children[i] = bp;
		if (bp->b_blkno == bp->b_lblkno)
			VOP_BMAP(vp, bp->b_lblkno, NULL, &bp->b_blkno,
				NULL, NULL);
	}
	buflist->bs_children[i] = bp = last_bp;
	if (bp->b_blkno == bp->b_lblkno)
		VOP_BMAP(vp, bp->b_lblkno, NULL, &bp->b_blkno, NULL, NULL);
	buflist->bs_nchildren = i + 1;
	return (buflist);
}