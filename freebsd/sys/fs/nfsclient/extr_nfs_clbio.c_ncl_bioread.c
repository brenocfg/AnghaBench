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
typedef  int uoff_t ;
typedef  scalar_t__ u_quad_t ;
struct TYPE_4__ {int bo_bsize; } ;
struct vnode {int v_type; TYPE_2__ v_bufobj; int /*<<< orphan*/  v_mount; } ;
struct uio {scalar_t__ uio_rw; scalar_t__ uio_resid; scalar_t__ uio_offset; struct thread* uio_td; } ;
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
struct nfsnode {scalar_t__ n_size; int n_direofoffset; } ;
struct nfsmount {int nm_flag; int nm_state; scalar_t__ nm_rsize; scalar_t__ nm_readdirsize; scalar_t__ nm_maxfilesize; int nm_readahead; int /*<<< orphan*/  nm_mtx; } ;
struct buf {int b_flags; int b_resid; scalar_t__ b_data; int /*<<< orphan*/  b_ioflags; void* b_iocmd; } ;
typedef  scalar_t__ off_t ;
typedef  int daddr_t ;
struct TYPE_3__ {int /*<<< orphan*/  biocache_readdirs; int /*<<< orphan*/  biocache_readlinks; int /*<<< orphan*/  biocache_reads; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_ERROR ; 
 void* BIO_READ ; 
 scalar_t__ BKVASIZE ; 
 int B_ASYNC ; 
 int B_CACHE ; 
 int B_DELWRI ; 
 int B_INVAL ; 
 int EFBIG ; 
 int EINTR ; 
 int EINVAL ; 
 int IO_DIRECT ; 
 int IO_SEQSHIFT ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int MIN (unsigned int,int) ; 
 int NFSERR_BAD_COOKIE ; 
 int /*<<< orphan*/  NFSINCRGLOBAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFSLOCKNODE (struct nfsnode*) ; 
 int NFSMNT_NFSV3 ; 
 int NFSSTA_GOTFSINFO ; 
 int /*<<< orphan*/  NFSUNLOCKNODE (struct nfsnode*) ; 
 int NFS_DIRBLKSIZ ; 
 int NFS_MAXPATHLEN ; 
 scalar_t__ UIO_READ ; 
#define  VDIR 130 
 struct nfsmount* VFSTONFS (int /*<<< orphan*/ ) ; 
#define  VLNK 129 
#define  VREG 128 
 struct nfsnode* VTONFS (struct vnode*) ; 
 int /*<<< orphan*/  brelse (struct buf*) ; 
 int /*<<< orphan*/ * incore (TYPE_2__*,int) ; 
 int lmin (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ncl_asyncio (struct nfsmount*,struct buf*,struct ucred*,struct thread*) ; 
 int ncl_doio (struct vnode*,struct buf*,struct ucred*,struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ncl_fsinfo (struct nfsmount*,struct vnode*,struct ucred*,struct thread*) ; 
 int /*<<< orphan*/  ncl_invaldir (struct vnode*) ; 
 int ncl_readrpc (struct vnode*,struct uio*,struct ucred*) ; 
 int ncl_vinvalbuf (struct vnode*,int /*<<< orphan*/ ,struct thread*,int) ; 
 scalar_t__ newnfs_directio_enable ; 
 int /*<<< orphan*/  newnfs_iosize (struct nfsmount*) ; 
 int newnfs_sigintr (struct nfsmount*,struct thread*) ; 
 int nfs_bioread_check_cons (struct vnode*,struct thread*,struct ucred*) ; 
 struct buf* nfs_getcacheblk (struct vnode*,int,int,struct thread*) ; 
 TYPE_1__ nfsstatsv1 ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  vfs_busy_pages (struct buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_unbusy_pages (struct buf*) ; 
 int vn_io_fault_uiomove (scalar_t__,int,struct uio*) ; 

int
ncl_bioread(struct vnode *vp, struct uio *uio, int ioflag, struct ucred *cred)
{
	struct nfsnode *np = VTONFS(vp);
	int biosize, i;
	struct buf *bp, *rabp;
	struct thread *td;
	struct nfsmount *nmp = VFSTONFS(vp->v_mount);
	daddr_t lbn, rabn;
	int bcount;
	int seqcount;
	int nra, error = 0, n = 0, on = 0;
	off_t tmp_off;

	KASSERT(uio->uio_rw == UIO_READ, ("ncl_read mode"));
	if (uio->uio_resid == 0)
		return (0);
	if (uio->uio_offset < 0)	/* XXX VDIR cookies can be negative */
		return (EINVAL);
	td = uio->uio_td;

	mtx_lock(&nmp->nm_mtx);
	if ((nmp->nm_flag & NFSMNT_NFSV3) != 0 &&
	    (nmp->nm_state & NFSSTA_GOTFSINFO) == 0) {
		mtx_unlock(&nmp->nm_mtx);
		(void)ncl_fsinfo(nmp, vp, cred, td);
		mtx_lock(&nmp->nm_mtx);
	}
	if (nmp->nm_rsize == 0 || nmp->nm_readdirsize == 0)
		(void) newnfs_iosize(nmp);

	tmp_off = uio->uio_offset + uio->uio_resid;
	if (vp->v_type != VDIR &&
	    (tmp_off > nmp->nm_maxfilesize || tmp_off < uio->uio_offset)) {
		mtx_unlock(&nmp->nm_mtx);
		return (EFBIG);
	}
	mtx_unlock(&nmp->nm_mtx);

	if (newnfs_directio_enable && (ioflag & IO_DIRECT) && (vp->v_type == VREG))
		/* No caching/ no readaheads. Just read data into the user buffer */
		return ncl_readrpc(vp, uio, cred);

	biosize = vp->v_bufobj.bo_bsize;
	seqcount = (int)((off_t)(ioflag >> IO_SEQSHIFT) * biosize / BKVASIZE);

	error = nfs_bioread_check_cons(vp, td, cred);
	if (error)
		return error;

	do {
	    u_quad_t nsize;

	    NFSLOCKNODE(np);
	    nsize = np->n_size;
	    NFSUNLOCKNODE(np);

	    switch (vp->v_type) {
	    case VREG:
		NFSINCRGLOBAL(nfsstatsv1.biocache_reads);
		lbn = uio->uio_offset / biosize;
		on = uio->uio_offset - (lbn * biosize);

		/*
		 * Start the read ahead(s), as required.
		 */
		if (nmp->nm_readahead > 0) {
		    for (nra = 0; nra < nmp->nm_readahead && nra < seqcount &&
			(off_t)(lbn + 1 + nra) * biosize < nsize; nra++) {
			rabn = lbn + 1 + nra;
			if (incore(&vp->v_bufobj, rabn) == NULL) {
			    rabp = nfs_getcacheblk(vp, rabn, biosize, td);
			    if (!rabp) {
				error = newnfs_sigintr(nmp, td);
				return (error ? error : EINTR);
			    }
			    if ((rabp->b_flags & (B_CACHE|B_DELWRI)) == 0) {
				rabp->b_flags |= B_ASYNC;
				rabp->b_iocmd = BIO_READ;
				vfs_busy_pages(rabp, 0);
				if (ncl_asyncio(nmp, rabp, cred, td)) {
				    rabp->b_flags |= B_INVAL;
				    rabp->b_ioflags |= BIO_ERROR;
				    vfs_unbusy_pages(rabp);
				    brelse(rabp);
				    break;
				}
			    } else {
				brelse(rabp);
			    }
			}
		    }
		}

		/* Note that bcount is *not* DEV_BSIZE aligned. */
		bcount = biosize;
		if ((off_t)lbn * biosize >= nsize) {
			bcount = 0;
		} else if ((off_t)(lbn + 1) * biosize > nsize) {
			bcount = nsize - (off_t)lbn * biosize;
		}
		bp = nfs_getcacheblk(vp, lbn, bcount, td);

		if (!bp) {
			error = newnfs_sigintr(nmp, td);
			return (error ? error : EINTR);
		}

		/*
		 * If B_CACHE is not set, we must issue the read.  If this
		 * fails, we return an error.
		 */

		if ((bp->b_flags & B_CACHE) == 0) {
		    bp->b_iocmd = BIO_READ;
		    vfs_busy_pages(bp, 0);
		    error = ncl_doio(vp, bp, cred, td, 0);
		    if (error) {
			brelse(bp);
			return (error);
		    }
		}

		/*
		 * on is the offset into the current bp.  Figure out how many
		 * bytes we can copy out of the bp.  Note that bcount is
		 * NOT DEV_BSIZE aligned.
		 *
		 * Then figure out how many bytes we can copy into the uio.
		 */

		n = 0;
		if (on < bcount)
			n = MIN((unsigned)(bcount - on), uio->uio_resid);
		break;
	    case VLNK:
		NFSINCRGLOBAL(nfsstatsv1.biocache_readlinks);
		bp = nfs_getcacheblk(vp, (daddr_t)0, NFS_MAXPATHLEN, td);
		if (!bp) {
			error = newnfs_sigintr(nmp, td);
			return (error ? error : EINTR);
		}
		if ((bp->b_flags & B_CACHE) == 0) {
		    bp->b_iocmd = BIO_READ;
		    vfs_busy_pages(bp, 0);
		    error = ncl_doio(vp, bp, cred, td, 0);
		    if (error) {
			bp->b_ioflags |= BIO_ERROR;
			brelse(bp);
			return (error);
		    }
		}
		n = MIN(uio->uio_resid, NFS_MAXPATHLEN - bp->b_resid);
		on = 0;
		break;
	    case VDIR:
		NFSINCRGLOBAL(nfsstatsv1.biocache_readdirs);
		if (np->n_direofoffset
		    && uio->uio_offset >= np->n_direofoffset) {
		    return (0);
		}
		lbn = (uoff_t)uio->uio_offset / NFS_DIRBLKSIZ;
		on = uio->uio_offset & (NFS_DIRBLKSIZ - 1);
		bp = nfs_getcacheblk(vp, lbn, NFS_DIRBLKSIZ, td);
		if (!bp) {
		    error = newnfs_sigintr(nmp, td);
		    return (error ? error : EINTR);
		}
		if ((bp->b_flags & B_CACHE) == 0) {
		    bp->b_iocmd = BIO_READ;
		    vfs_busy_pages(bp, 0);
		    error = ncl_doio(vp, bp, cred, td, 0);
		    if (error) {
			    brelse(bp);
		    }
		    while (error == NFSERR_BAD_COOKIE) {
			ncl_invaldir(vp);
			error = ncl_vinvalbuf(vp, 0, td, 1);

			/*
			 * Yuck! The directory has been modified on the
			 * server. The only way to get the block is by
			 * reading from the beginning to get all the
			 * offset cookies.
			 *
			 * Leave the last bp intact unless there is an error.
			 * Loop back up to the while if the error is another
			 * NFSERR_BAD_COOKIE (double yuch!).
			 */
			for (i = 0; i <= lbn && !error; i++) {
			    if (np->n_direofoffset
				&& (i * NFS_DIRBLKSIZ) >= np->n_direofoffset)
				    return (0);
			    bp = nfs_getcacheblk(vp, i, NFS_DIRBLKSIZ, td);
			    if (!bp) {
				error = newnfs_sigintr(nmp, td);
				return (error ? error : EINTR);
			    }
			    if ((bp->b_flags & B_CACHE) == 0) {
				    bp->b_iocmd = BIO_READ;
				    vfs_busy_pages(bp, 0);
				    error = ncl_doio(vp, bp, cred, td, 0);
				    /*
				     * no error + B_INVAL == directory EOF,
				     * use the block.
				     */
				    if (error == 0 && (bp->b_flags & B_INVAL))
					    break;
			    }
			    /*
			     * An error will throw away the block and the
			     * for loop will break out.  If no error and this
			     * is not the block we want, we throw away the
			     * block and go for the next one via the for loop.
			     */
			    if (error || i < lbn)
				    brelse(bp);
			}
		    }
		    /*
		     * The above while is repeated if we hit another cookie
		     * error.  If we hit an error and it wasn't a cookie error,
		     * we give up.
		     */
		    if (error)
			    return (error);
		}

		/*
		 * If not eof and read aheads are enabled, start one.
		 * (You need the current block first, so that you have the
		 *  directory offset cookie of the next block.)
		 */
		if (nmp->nm_readahead > 0 &&
		    (bp->b_flags & B_INVAL) == 0 &&
		    (np->n_direofoffset == 0 ||
		    (lbn + 1) * NFS_DIRBLKSIZ < np->n_direofoffset) &&
		    incore(&vp->v_bufobj, lbn + 1) == NULL) {
			rabp = nfs_getcacheblk(vp, lbn + 1, NFS_DIRBLKSIZ, td);
			if (rabp) {
			    if ((rabp->b_flags & (B_CACHE|B_DELWRI)) == 0) {
				rabp->b_flags |= B_ASYNC;
				rabp->b_iocmd = BIO_READ;
				vfs_busy_pages(rabp, 0);
				if (ncl_asyncio(nmp, rabp, cred, td)) {
				    rabp->b_flags |= B_INVAL;
				    rabp->b_ioflags |= BIO_ERROR;
				    vfs_unbusy_pages(rabp);
				    brelse(rabp);
				}
			    } else {
				brelse(rabp);
			    }
			}
		}
		/*
		 * Unlike VREG files, whos buffer size ( bp->b_bcount ) is
		 * chopped for the EOF condition, we cannot tell how large
		 * NFS directories are going to be until we hit EOF.  So
		 * an NFS directory buffer is *not* chopped to its EOF.  Now,
		 * it just so happens that b_resid will effectively chop it
		 * to EOF.  *BUT* this information is lost if the buffer goes
		 * away and is reconstituted into a B_CACHE state ( due to
		 * being VMIO ) later.  So we keep track of the directory eof
		 * in np->n_direofoffset and chop it off as an extra step
		 * right here.
		 */
		n = lmin(uio->uio_resid, NFS_DIRBLKSIZ - bp->b_resid - on);
		if (np->n_direofoffset && n > np->n_direofoffset - uio->uio_offset)
			n = np->n_direofoffset - uio->uio_offset;
		break;
	    default:
		printf(" ncl_bioread: type %x unexpected\n", vp->v_type);
		bp = NULL;
		break;
	    }

	    if (n > 0) {
		    error = vn_io_fault_uiomove(bp->b_data + on, (int)n, uio);
	    }
	    if (vp->v_type == VLNK)
		n = 0;
	    if (bp != NULL)
		brelse(bp);
	} while (error == 0 && uio->uio_resid > 0 && n > 0);
	return (error);
}