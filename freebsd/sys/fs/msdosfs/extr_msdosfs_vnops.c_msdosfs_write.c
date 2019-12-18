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
typedef  scalar_t__ uoff_t ;
typedef  scalar_t__ u_long ;
struct vop_write_args {int a_ioflag; struct ucred* a_cred; struct vnode* a_vp; struct uio* a_uio; } ;
struct vnode {int v_type; TYPE_2__* v_mount; } ;
struct uio {scalar_t__ uio_offset; scalar_t__ uio_resid; int /*<<< orphan*/  uio_td; } ;
struct ucred {int dummy; } ;
struct msdosfsmount {int pm_crbomask; int pm_bpcluster; } ;
struct denode {scalar_t__ de_FileSize; int /*<<< orphan*/  de_flag; TYPE_1__* de_fc; int /*<<< orphan*/  de_StartCluster; int /*<<< orphan*/  de_dirclust; int /*<<< orphan*/  de_diroffset; struct msdosfsmount* de_pmp; } ;
struct buf {int b_blkno; int b_lblkno; int /*<<< orphan*/  b_flags; scalar_t__ b_data; } ;
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ daddr_t ;
struct TYPE_4__ {int mnt_flag; } ;
struct TYPE_3__ {scalar_t__ fc_frcn; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_CLUSTEROK ; 
 int /*<<< orphan*/  DE_UPDATE ; 
 int EFBIG ; 
 int EIO ; 
 int EISDIR ; 
 int ENOSPC ; 
 size_t FC_LASTFC ; 
 int IO_APPEND ; 
 int IO_SEQSHIFT ; 
 int IO_SYNC ; 
 int IO_UNIT ; 
 int MNT_NOCLUSTERW ; 
 scalar_t__ MSDOSFS_FILESIZE_MAX ; 
 int /*<<< orphan*/  NOCRED ; 
#define  VDIR 129 
#define  VREG 128 
 struct denode* VTODE (struct vnode*) ; 
 int /*<<< orphan*/  bawrite (struct buf*) ; 
 int /*<<< orphan*/  bdwrite (struct buf*) ; 
 int bread (struct vnode*,scalar_t__,int,struct ucred*,struct buf**) ; 
 int /*<<< orphan*/  brelse (struct buf*) ; 
 scalar_t__ buf_dirty_count_severe () ; 
 int /*<<< orphan*/  bwrite (struct buf*) ; 
 int /*<<< orphan*/  cluster_write (struct vnode*,struct buf*,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ de_clcount (struct msdosfsmount*,scalar_t__) ; 
 scalar_t__ de_cluster (struct msdosfsmount*,scalar_t__) ; 
 int deextend (struct denode*,scalar_t__,struct ucred*) ; 
 int /*<<< orphan*/  detrunc (struct denode*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int deupdat (struct denode*,int) ; 
 int extendfile (struct denode*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct buf* getblk (struct vnode*,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int min (scalar_t__,int) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int pcbmap (struct denode*,int,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,struct vnode*,struct uio*,int,...) ; 
 int /*<<< orphan*/  vfs_bio_clrbuf (struct buf*) ; 
 scalar_t__ vm_page_count_severe () ; 
 int vn_io_fault_uiomove (scalar_t__,int,struct uio*) ; 
 scalar_t__ vn_rlimit_fsize (struct vnode*,struct uio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_pager_setsize (struct vnode*,int) ; 

__attribute__((used)) static int
msdosfs_write(struct vop_write_args *ap)
{
	int n;
	int croffset;
	ssize_t resid;
	u_long osize;
	int error = 0;
	u_long count;
	int seqcount;
	daddr_t bn, lastcn;
	struct buf *bp;
	int ioflag = ap->a_ioflag;
	struct uio *uio = ap->a_uio;
	struct vnode *vp = ap->a_vp;
	struct vnode *thisvp;
	struct denode *dep = VTODE(vp);
	struct msdosfsmount *pmp = dep->de_pmp;
	struct ucred *cred = ap->a_cred;

#ifdef MSDOSFS_DEBUG
	printf("msdosfs_write(vp %p, uio %p, ioflag %x, cred %p\n",
	    vp, uio, ioflag, cred);
	printf("msdosfs_write(): diroff %lu, dirclust %lu, startcluster %lu\n",
	    dep->de_diroffset, dep->de_dirclust, dep->de_StartCluster);
#endif

	switch (vp->v_type) {
	case VREG:
		if (ioflag & IO_APPEND)
			uio->uio_offset = dep->de_FileSize;
		thisvp = vp;
		break;
	case VDIR:
		return EISDIR;
	default:
		panic("msdosfs_write(): bad file type");
	}

	/*
	 * This is needed (unlike in ffs_write()) because we extend the
	 * file outside of the loop but we don't want to extend the file
	 * for writes of 0 bytes.
	 */
	if (uio->uio_resid == 0)
		return (0);

	/*
	 * The caller is supposed to ensure that
	 * uio->uio_offset >= 0 and uio->uio_resid >= 0.
	 */
	if ((uoff_t)uio->uio_offset + uio->uio_resid > MSDOSFS_FILESIZE_MAX)
		return (EFBIG);

	/*
	 * If they've exceeded their filesize limit, tell them about it.
	 */
	if (vn_rlimit_fsize(vp, uio, uio->uio_td))
		return (EFBIG);

	/*
	 * If the offset we are starting the write at is beyond the end of
	 * the file, then they've done a seek.  Unix filesystems allow
	 * files with holes in them, DOS doesn't so we must fill the hole
	 * with zeroed blocks.
	 */
	if (uio->uio_offset > dep->de_FileSize) {
		error = deextend(dep, uio->uio_offset, cred);
		if (error)
			return (error);
	}

	/*
	 * Remember some values in case the write fails.
	 */
	resid = uio->uio_resid;
	osize = dep->de_FileSize;

	/*
	 * If we write beyond the end of the file, extend it to its ultimate
	 * size ahead of the time to hopefully get a contiguous area.
	 */
	if (uio->uio_offset + resid > osize) {
		count = de_clcount(pmp, uio->uio_offset + resid) -
			de_clcount(pmp, osize);
		error = extendfile(dep, count, NULL, NULL, 0);
		if (error &&  (error != ENOSPC || (ioflag & IO_UNIT)))
			goto errexit;
		lastcn = dep->de_fc[FC_LASTFC].fc_frcn;
	} else
		lastcn = de_clcount(pmp, osize) - 1;

	seqcount = ioflag >> IO_SEQSHIFT;
	do {
		if (de_cluster(pmp, uio->uio_offset) > lastcn) {
			error = ENOSPC;
			break;
		}

		croffset = uio->uio_offset & pmp->pm_crbomask;
		n = min(uio->uio_resid, pmp->pm_bpcluster - croffset);
		if (uio->uio_offset + n > dep->de_FileSize) {
			dep->de_FileSize = uio->uio_offset + n;
			/* The object size needs to be set before buffer is allocated */
			vnode_pager_setsize(vp, dep->de_FileSize);
		}

		bn = de_cluster(pmp, uio->uio_offset);
		if ((uio->uio_offset & pmp->pm_crbomask) == 0
		    && (de_cluster(pmp, uio->uio_offset + uio->uio_resid)
			> de_cluster(pmp, uio->uio_offset)
			|| uio->uio_offset + uio->uio_resid >= dep->de_FileSize)) {
			/*
			 * If either the whole cluster gets written,
			 * or we write the cluster from its start beyond EOF,
			 * then no need to read data from disk.
			 */
			bp = getblk(thisvp, bn, pmp->pm_bpcluster, 0, 0, 0);
			/*
			 * This call to vfs_bio_clrbuf() ensures that
			 * even if vn_io_fault_uiomove() below faults,
			 * garbage from the newly instantiated buffer
			 * is not exposed to the userspace via mmap().
			 */
			vfs_bio_clrbuf(bp);
			/*
			 * Do the bmap now, since pcbmap needs buffers
			 * for the FAT table. (see msdosfs_strategy)
			 */
			if (bp->b_blkno == bp->b_lblkno) {
				error = pcbmap(dep, bp->b_lblkno, &bn, 0, 0);
				if (error)
					bp->b_blkno = -1;
				else
					bp->b_blkno = bn;
			}
			if (bp->b_blkno == -1) {
				brelse(bp);
				if (!error)
					error = EIO;		/* XXX */
				break;
			}
		} else {
			/*
			 * The block we need to write into exists, so read it in.
			 */
			error = bread(thisvp, bn, pmp->pm_bpcluster, cred, &bp);
			if (error) {
				break;
			}
		}

		/*
		 * Should these vnode_pager_* functions be done on dir
		 * files?
		 */

		/*
		 * Copy the data from user space into the buf header.
		 */
		error = vn_io_fault_uiomove(bp->b_data + croffset, n, uio);
		if (error) {
			brelse(bp);
			break;
		}

		/* Prepare for clustered writes in some else clauses. */
		if ((vp->v_mount->mnt_flag & MNT_NOCLUSTERW) == 0)
			bp->b_flags |= B_CLUSTEROK;

		/*
		 * If IO_SYNC, then each buffer is written synchronously.
		 * Otherwise, if we have a severe page deficiency then
		 * write the buffer asynchronously.  Otherwise, if on a
		 * cluster boundary then write the buffer asynchronously,
		 * combining it with contiguous clusters if permitted and
		 * possible, since we don't expect more writes into this
		 * buffer soon.  Otherwise, do a delayed write because we
		 * expect more writes into this buffer soon.
		 */
		if (ioflag & IO_SYNC)
			(void)bwrite(bp);
		else if (vm_page_count_severe() || buf_dirty_count_severe())
			bawrite(bp);
		else if (n + croffset == pmp->pm_bpcluster) {
			if ((vp->v_mount->mnt_flag & MNT_NOCLUSTERW) == 0)
				cluster_write(vp, bp, dep->de_FileSize,
				    seqcount, 0);
			else
				bawrite(bp);
		} else
			bdwrite(bp);
		dep->de_flag |= DE_UPDATE;
	} while (error == 0 && uio->uio_resid > 0);

	/*
	 * If the write failed and they want us to, truncate the file back
	 * to the size it was before the write was attempted.
	 */
errexit:
	if (error) {
		if (ioflag & IO_UNIT) {
			detrunc(dep, osize, ioflag & IO_SYNC, NOCRED);
			uio->uio_offset -= resid - uio->uio_resid;
			uio->uio_resid = resid;
		} else {
			detrunc(dep, dep->de_FileSize, ioflag & IO_SYNC, NOCRED);
			if (uio->uio_resid != resid)
				error = 0;
		}
	} else if (ioflag & IO_SYNC)
		error = deupdat(dep, 1);
	return (error);
}