#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_offset_t ;
typedef  int ufs2_daddr_t ;
typedef  int u_int ;
struct vnode {int /*<<< orphan*/  v_bufobj; TYPE_2__* v_mount; } ;
struct thread {int dummy; } ;
struct inode {int dummy; } ;
struct buf {size_t b_bcount; int b_kvasize; int b_lblkno; int b_blkno; int b_bufsize; int b_offset; int b_iooffset; int /*<<< orphan*/  b_flags; scalar_t__ b_resid; scalar_t__ b_data; int /*<<< orphan*/  b_iodone; int /*<<< orphan*/  b_iocmd; } ;
typedef  int off_t ;
typedef  int daddr_t ;
typedef  scalar_t__ caddr_t ;
struct TYPE_3__ {int f_iosize; } ;
struct TYPE_4__ {TYPE_1__ mnt_stat; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_READ ; 
 int /*<<< orphan*/  BO_STRATEGY (int /*<<< orphan*/ *,struct buf*) ; 
 int /*<<< orphan*/  B_DONE ; 
 int DEV_BSIZE ; 
 int EFAULT ; 
 int EINVAL ; 
 struct vnode* ITODEVVP (struct inode*) ; 
 int PAGE_MASK ; 
 scalar_t__ PAGE_SIZE ; 
 struct inode* VTOI (struct vnode*) ; 
 int /*<<< orphan*/  bdone ; 
 int /*<<< orphan*/  bzero (scalar_t__,int) ; 
 int /*<<< orphan*/  maybe_yield () ; 
 int ufs_bmaparray (struct vnode*,int,int*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 scalar_t__ vmapbuf (struct buf*,int) ; 

__attribute__((used)) static int
ffs_rawread_readahead(struct vnode *vp,
		      caddr_t udata,
		      off_t offset,
		      size_t len,
		      struct thread *td,
		      struct buf *bp)
{
	int error;
	u_int iolen;
	off_t blockno;
	int blockoff;
	int bsize;
	struct vnode *dp;
	int bforwards;
	struct inode *ip;
	ufs2_daddr_t blkno;
	
	bsize = vp->v_mount->mnt_stat.f_iosize;
	
	ip = VTOI(vp);
	dp = ITODEVVP(ip);

	iolen = ((vm_offset_t) udata) & PAGE_MASK;
	bp->b_bcount = len;
	if (bp->b_bcount + iolen > bp->b_kvasize) {
		bp->b_bcount = bp->b_kvasize;
		if (iolen != 0)
			bp->b_bcount -= PAGE_SIZE;
	}
	bp->b_flags = 0;	/* XXX necessary ? */
	bp->b_iocmd = BIO_READ;
	bp->b_iodone = bdone;
	bp->b_data = udata;
	blockno = offset / bsize;
	blockoff = (offset % bsize) / DEV_BSIZE;
	if ((daddr_t) blockno != blockno) {
		return EINVAL; /* blockno overflow */
	}
	
	bp->b_lblkno = bp->b_blkno = blockno;
	
	error = ufs_bmaparray(vp, bp->b_lblkno, &blkno, NULL, &bforwards, NULL);
	if (error != 0)
		return error;
	if (blkno == -1) {

		/* Fill holes with NULs to preserve semantics */
		
		if (bp->b_bcount + blockoff * DEV_BSIZE > bsize)
			bp->b_bcount = bsize - blockoff * DEV_BSIZE;
		bp->b_bufsize = bp->b_bcount;
		
		if (vmapbuf(bp, 1) < 0)
			return EFAULT;
		
		maybe_yield();
		bzero(bp->b_data, bp->b_bufsize);

		/* Mark operation completed (similar to bufdone()) */

		bp->b_resid = 0;
		bp->b_flags |= B_DONE;
		return 0;
	}
	bp->b_blkno = blkno + blockoff;
	bp->b_offset = bp->b_iooffset = (blkno + blockoff) * DEV_BSIZE;
	
	if (bp->b_bcount + blockoff * DEV_BSIZE > bsize * (1 + bforwards))
		bp->b_bcount = bsize * (1 + bforwards) - blockoff * DEV_BSIZE;
	bp->b_bufsize = bp->b_bcount;
	
	if (vmapbuf(bp, 1) < 0)
		return EFAULT;
	
	BO_STRATEGY(&dp->v_bufobj, bp);
	return 0;
}