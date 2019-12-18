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
typedef  scalar_t__ u_quad_t ;
struct TYPE_2__ {int bo_bsize; } ;
struct vnode {TYPE_1__ v_bufobj; } ;
struct thread {int dummy; } ;
struct nfsnode {scalar_t__ n_size; } ;
struct buf {scalar_t__ b_dirtyoff; scalar_t__ b_bcount; scalar_t__ b_dirtyend; int /*<<< orphan*/  b_flags; } ;
typedef  int daddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_RELBUF ; 
 int EINTR ; 
 int /*<<< orphan*/  NFSLOCKNODE (struct nfsnode*) ; 
 int /*<<< orphan*/  NFSUNLOCKNODE (struct nfsnode*) ; 
 struct nfsnode* VTONFS (struct vnode*) ; 
 int /*<<< orphan*/  brelse (struct buf*) ; 
 struct buf* nfs_getcacheblk (struct vnode*,int,int,struct thread*) ; 
 int /*<<< orphan*/  vnode_pager_setsize (struct vnode*,scalar_t__) ; 
 int vtruncbuf (struct vnode*,scalar_t__,int) ; 

int
ncl_meta_setsize(struct vnode *vp, struct thread *td, u_quad_t nsize)
{
	struct nfsnode *np = VTONFS(vp);
	u_quad_t tsize;
	int biosize = vp->v_bufobj.bo_bsize;
	int error = 0;

	NFSLOCKNODE(np);
	tsize = np->n_size;
	np->n_size = nsize;
	NFSUNLOCKNODE(np);

	if (nsize < tsize) {
		struct buf *bp;
		daddr_t lbn;
		int bufsize;

		/*
		 * vtruncbuf() doesn't get the buffer overlapping the
		 * truncation point.  We may have a B_DELWRI and/or B_CACHE
		 * buffer that now needs to be truncated.
		 */
		error = vtruncbuf(vp, nsize, biosize);
		lbn = nsize / biosize;
		bufsize = nsize - (lbn * biosize);
		bp = nfs_getcacheblk(vp, lbn, bufsize, td);
		if (!bp)
			return EINTR;
		if (bp->b_dirtyoff > bp->b_bcount)
			bp->b_dirtyoff = bp->b_bcount;
		if (bp->b_dirtyend > bp->b_bcount)
			bp->b_dirtyend = bp->b_bcount;
		bp->b_flags |= B_RELBUF;  /* don't leave garbage around */
		brelse(bp);
	} else {
		vnode_pager_setsize(vp, nsize);
	}
	return(error);
}