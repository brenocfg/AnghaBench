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
typedef  long u_int ;
struct vnode {int dummy; } ;
struct uio {long uio_resid; scalar_t__ uio_offset; TYPE_1__* uio_iov; struct thread* uio_td; } ;
struct thread {int /*<<< orphan*/  td_proc; } ;
struct buf {long b_bufsize; long b_bcount; long b_resid; int b_ioflags; int b_error; } ;
typedef  scalar_t__ off_t ;
typedef  scalar_t__ caddr_t ;
struct TYPE_2__ {scalar_t__ iov_base; } ;

/* Variables and functions */
 int BIO_ERROR ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  PHOLD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRELE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRIBIO ; 
 int /*<<< orphan*/  bwait (struct buf*,int /*<<< orphan*/ ,char*) ; 
 struct thread* curthread ; 
 int ffs_rawread_readahead (struct vnode*,scalar_t__,scalar_t__,long,struct thread*,struct buf*) ; 
 int /*<<< orphan*/  ffsraw_pbuf_zone ; 
 int /*<<< orphan*/  pbgetvp (struct vnode*,struct buf*) ; 
 int /*<<< orphan*/  pbrelvp (struct buf*) ; 
 scalar_t__ rawreadahead ; 
 struct buf* uma_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct buf*) ; 
 int /*<<< orphan*/  vunmapbuf (struct buf*) ; 

__attribute__((used)) static int
ffs_rawread_main(struct vnode *vp,
		 struct uio *uio)
{
	int error, nerror;
	struct buf *bp, *nbp, *tbp;
	u_int iolen;
	caddr_t udata;
	long resid;
	off_t offset;
	struct thread *td;
	
	td = uio->uio_td ? uio->uio_td : curthread;
	udata = uio->uio_iov->iov_base;
	resid = uio->uio_resid;
	offset = uio->uio_offset;

	/*
	 * keep the process from being swapped
	 */
	PHOLD(td->td_proc);
	
	error = 0;
	nerror = 0;
	
	bp = NULL;
	nbp = NULL;
	
	while (resid > 0) {
		
		if (bp == NULL) { /* Setup first read */
			bp = uma_zalloc(ffsraw_pbuf_zone, M_WAITOK);
			pbgetvp(vp, bp);
			error = ffs_rawread_readahead(vp, udata, offset,
						     resid, td, bp);
			if (error != 0)
				break;
			
			if (resid > bp->b_bufsize) { /* Setup fist readahead */
				if (rawreadahead != 0) 
					nbp = uma_zalloc(ffsraw_pbuf_zone,
					    M_NOWAIT);
				else
					nbp = NULL;
				if (nbp != NULL) {
					pbgetvp(vp, nbp);
					
					nerror = ffs_rawread_readahead(vp, 
								       udata +
								       bp->b_bufsize,
								       offset +
								       bp->b_bufsize,
								       resid -
								       bp->b_bufsize,
								       td,
								       nbp);
					if (nerror) {
						pbrelvp(nbp);
						uma_zfree(ffsraw_pbuf_zone,
						    nbp);
						nbp = NULL;
					}
				}
			}
		}
		
		bwait(bp, PRIBIO, "rawrd");
		vunmapbuf(bp);
		
		iolen = bp->b_bcount - bp->b_resid;
		if (iolen == 0 && (bp->b_ioflags & BIO_ERROR) == 0) {
			nerror = 0;	/* Ignore possible beyond EOF error */
			break; /* EOF */
		}
		
		if ((bp->b_ioflags & BIO_ERROR) != 0) {
			error = bp->b_error;
			break;
		}
		resid -= iolen;
		udata += iolen;
		offset += iolen;
		if (iolen < bp->b_bufsize) {
			/* Incomplete read.  Try to read remaining part */
			error = ffs_rawread_readahead(vp,
						      udata,
						      offset,
						      bp->b_bufsize - iolen,
						      td,
						      bp);
			if (error != 0)
				break;
		} else if (nbp != NULL) { /* Complete read with readahead */
			
			tbp = bp;
			bp = nbp;
			nbp = tbp;
			
			if (resid <= bp->b_bufsize) { /* No more readaheads */
				pbrelvp(nbp);
				uma_zfree(ffsraw_pbuf_zone, nbp);
				nbp = NULL;
			} else { /* Setup next readahead */
				nerror = ffs_rawread_readahead(vp,
							       udata +
							       bp->b_bufsize,
							       offset +
							       bp->b_bufsize,
							       resid -
							       bp->b_bufsize,
							       td,
							       nbp);
				if (nerror != 0) {
					pbrelvp(nbp);
					uma_zfree(ffsraw_pbuf_zone, nbp);
					nbp = NULL;
				}
			}
		} else if (nerror != 0) {/* Deferred Readahead error */
			break;		
		}  else if (resid > 0) { /* More to read, no readahead */
			error = ffs_rawread_readahead(vp, udata, offset,
						      resid, td, bp);
			if (error != 0)
				break;
		}
	}
	
	if (bp != NULL) {
		pbrelvp(bp);
		uma_zfree(ffsraw_pbuf_zone, bp);
	}
	if (nbp != NULL) {			/* Run down readahead buffer */
		bwait(nbp, PRIBIO, "rawrd");
		vunmapbuf(nbp);
		pbrelvp(nbp);
		uma_zfree(ffsraw_pbuf_zone, nbp);
	}
	
	if (error == 0)
		error = nerror;
	PRELE(td->td_proc);
	uio->uio_iov->iov_base = udata;
	uio->uio_resid = resid;
	uio->uio_offset = offset;
	return error;
}