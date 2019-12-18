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
struct vnode {int v_type; int /*<<< orphan*/  v_mount; } ;
struct uio {int uio_iovcnt; scalar_t__ uio_resid; int uio_offset; int /*<<< orphan*/  uio_rw; struct thread* uio_td; int /*<<< orphan*/  uio_segflg; struct iovec* uio_iov; } ;
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
struct smbnode {scalar_t__ n_size; int /*<<< orphan*/  n_fid; } ;
struct smbmount {int /*<<< orphan*/  sm_share; } ;
struct smb_cred {int dummy; } ;
struct iovec {scalar_t__ iov_len; char* iov_base; } ;
struct buf {scalar_t__ b_iocmd; scalar_t__ b_bcount; char* b_data; int b_blkno; int b_error; scalar_t__ b_dirtyend; scalar_t__ b_dirtyoff; int b_flags; scalar_t__ b_resid; int /*<<< orphan*/  b_ioflags; } ;
typedef  int off_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_ERROR ; 
 scalar_t__ BIO_READ ; 
 int B_ASYNC ; 
 int B_DONE ; 
 int B_EINTR ; 
 int B_INVAL ; 
 int B_NEEDCOMMIT ; 
 int B_NOCACHE ; 
 int B_PAGING ; 
 int DEV_BSIZE ; 
 int EINTR ; 
 int /*<<< orphan*/  M_SMBFSDATA ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  UIO_READ ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int /*<<< orphan*/  UIO_WRITE ; 
 struct smbmount* VFSTOSMBFS (int /*<<< orphan*/ ) ; 
#define  VREG 128 
 struct smbnode* VTOSMB (struct vnode*) ; 
 int /*<<< orphan*/  bdirty (struct buf*) ; 
 int /*<<< orphan*/  bufdone (struct buf*) ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int /*<<< orphan*/  free (struct uio*,int /*<<< orphan*/ ) ; 
 struct uio* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  smb_makescred (struct smb_cred*,struct thread*,struct ucred*) ; 
 int smb_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uio*,struct smb_cred*) ; 
 int smb_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uio*,struct smb_cred*) ; 
 int /*<<< orphan*/  smbfs_free_scred (struct smb_cred*) ; 
 struct smb_cred* smbfs_malloc_scred () ; 

int
smbfs_doio(struct vnode *vp, struct buf *bp, struct ucred *cr, struct thread *td)
{
	struct smbmount *smp = VFSTOSMBFS(vp->v_mount);
	struct smbnode *np = VTOSMB(vp);
	struct uio *uiop;
	struct iovec io;
	struct smb_cred *scred;
	int error = 0;

	uiop = malloc(sizeof(struct uio), M_SMBFSDATA, M_WAITOK);
	uiop->uio_iov = &io;
	uiop->uio_iovcnt = 1;
	uiop->uio_segflg = UIO_SYSSPACE;
	uiop->uio_td = td;

	scred = smbfs_malloc_scred();
	smb_makescred(scred, td, cr);

	if (bp->b_iocmd == BIO_READ) {
	    io.iov_len = uiop->uio_resid = bp->b_bcount;
	    io.iov_base = bp->b_data;
	    uiop->uio_rw = UIO_READ;
	    switch (vp->v_type) {
	      case VREG:
		uiop->uio_offset = ((off_t)bp->b_blkno) * DEV_BSIZE;
		error = smb_read(smp->sm_share, np->n_fid, uiop, scred);
		if (error)
			break;
		if (uiop->uio_resid) {
			int left = uiop->uio_resid;
			int nread = bp->b_bcount - left;
			if (left > 0)
			    bzero((char *)bp->b_data + nread, left);
		}
		break;
	    default:
		printf("smbfs_doio:  type %x unexpected\n",vp->v_type);
		break;
	    }
	    if (error) {
		bp->b_error = error;
		bp->b_ioflags |= BIO_ERROR;
	    }
	} else { /* write */
	    if (((bp->b_blkno * DEV_BSIZE) + bp->b_dirtyend) > np->n_size)
		bp->b_dirtyend = np->n_size - (bp->b_blkno * DEV_BSIZE);

	    if (bp->b_dirtyend > bp->b_dirtyoff) {
		io.iov_len = uiop->uio_resid = bp->b_dirtyend - bp->b_dirtyoff;
		uiop->uio_offset = ((off_t)bp->b_blkno) * DEV_BSIZE + bp->b_dirtyoff;
		io.iov_base = (char *)bp->b_data + bp->b_dirtyoff;
		uiop->uio_rw = UIO_WRITE;
		error = smb_write(smp->sm_share, np->n_fid, uiop, scred);

		/*
		 * For an interrupted write, the buffer is still valid
		 * and the write hasn't been pushed to the server yet,
		 * so we can't set BIO_ERROR and report the interruption
		 * by setting B_EINTR. For the B_ASYNC case, B_EINTR
		 * is not relevant, so the rpc attempt is essentially
		 * a noop.  For the case of a V3 write rpc not being
		 * committed to stable storage, the block is still
		 * dirty and requires either a commit rpc or another
		 * write rpc with iomode == NFSV3WRITE_FILESYNC before
		 * the block is reused. This is indicated by setting
		 * the B_DELWRI and B_NEEDCOMMIT flags.
		 */
		if (error == EINTR
		    || (!error && (bp->b_flags & B_NEEDCOMMIT))) {
			bp->b_flags &= ~(B_INVAL|B_NOCACHE);
			if ((bp->b_flags & B_ASYNC) == 0)
			    bp->b_flags |= B_EINTR;
			if ((bp->b_flags & B_PAGING) == 0) {
			    bdirty(bp);
			    bp->b_flags &= ~B_DONE;
			}
			if ((bp->b_flags & B_ASYNC) == 0)
			    bp->b_flags |= B_EINTR;
		} else {
			if (error) {
				bp->b_ioflags |= BIO_ERROR;
				bp->b_error = error;
			}
			bp->b_dirtyoff = bp->b_dirtyend = 0;
		}
	    } else {
		bp->b_resid = 0;
		bufdone(bp);
		free(uiop, M_SMBFSDATA);
		smbfs_free_scred(scred);
		return 0;
	    }
	}
	bp->b_resid = uiop->uio_resid;
	bufdone(bp);
	free(uiop, M_SMBFSDATA);
	smbfs_free_scred(scred);
	return error;
}