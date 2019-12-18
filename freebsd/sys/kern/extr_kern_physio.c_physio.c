#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_prot_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  scalar_t__ u_int ;
struct vm_page {int dummy; } ;
struct uio {scalar_t__ uio_resid; int uio_iovcnt; scalar_t__ uio_segflg; scalar_t__ uio_rw; int /*<<< orphan*/  uio_offset; TYPE_3__* uio_iov; } ;
struct cdevsw {int /*<<< orphan*/  (* d_strategy ) (struct bio*) ;} ;
struct cdev {scalar_t__ si_iosize_max; int si_flags; struct cdevsw* si_devsw; } ;
struct buf {scalar_t__ b_kvasize; struct vm_page** b_pages; int /*<<< orphan*/ * b_data; } ;
struct bio {int bio_data; scalar_t__ bio_length; scalar_t__ bio_bcount; int bio_ma_n; int bio_flags; scalar_t__ bio_resid; int bio_error; scalar_t__ bio_ma_offset; struct vm_page** bio_ma; struct cdev* bio_dev; int /*<<< orphan*/  bio_offset; int /*<<< orphan*/  bio_cmd; } ;
typedef  int /*<<< orphan*/ * caddr_t ;
struct TYPE_12__ {int /*<<< orphan*/  ru_oublock; int /*<<< orphan*/  ru_inblock; } ;
struct TYPE_15__ {TYPE_2__ td_ru; } ;
struct TYPE_14__ {TYPE_1__* p_vmspace; } ;
struct TYPE_13__ {int iov_len; char* iov_base; } ;
struct TYPE_11__ {int /*<<< orphan*/  vm_map; } ;

/* Variables and functions */
 int BIO_ERROR ; 
 int /*<<< orphan*/  BIO_READ ; 
 int BIO_UNMAPPED ; 
 int /*<<< orphan*/  BIO_WRITE ; 
 int DFLTPHYS ; 
 int EFAULT ; 
 int EFBIG ; 
 int ENXIO ; 
 scalar_t__ MAXPHYS ; 
 scalar_t__ MIN (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_WAITOK ; 
 scalar_t__ PAGE_MASK ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  PHOLD (TYPE_4__*) ; 
 int /*<<< orphan*/  PRELE (TYPE_4__*) ; 
 int /*<<< orphan*/  PROC_LOCK (TYPE_4__*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (TYPE_4__*) ; 
 int /*<<< orphan*/  RACCT_READBPS ; 
 int /*<<< orphan*/  RACCT_READIOPS ; 
 int /*<<< orphan*/  RACCT_WRITEBPS ; 
 int /*<<< orphan*/  RACCT_WRITEIOPS ; 
 int SI_NOSPLIT ; 
 int SI_UNMAPPED ; 
 scalar_t__ UIO_READ ; 
 scalar_t__ UIO_USERSPACE ; 
 int /*<<< orphan*/  VM_PROT_READ ; 
 int /*<<< orphan*/  VM_PROT_WRITE ; 
 int /*<<< orphan*/  biowait (struct bio*,char*) ; 
 int btoc (scalar_t__) ; 
 TYPE_4__* curproc ; 
 TYPE_5__* curthread ; 
 char* devtoname (struct cdev*) ; 
 int /*<<< orphan*/  free (struct vm_page**,int /*<<< orphan*/ ) ; 
 struct bio* g_alloc_bio () ; 
 int /*<<< orphan*/  g_destroy_bio (struct bio*) ; 
 int /*<<< orphan*/  g_reset_bio (struct bio*) ; 
 struct vm_page** malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pbuf_zone ; 
 int /*<<< orphan*/  pmap_qenter (scalar_t__,struct vm_page**,int) ; 
 int /*<<< orphan*/  pmap_qremove (scalar_t__,int) ; 
 int /*<<< orphan*/  printf (char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  racct_add_force (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ racct_enable ; 
 int /*<<< orphan*/  stub1 (struct bio*) ; 
 struct buf* uma_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct buf*) ; 
 int unmapped_buf ; 
 scalar_t__ unmapped_buf_allowed ; 
 int /*<<< orphan*/  uprintf (char*,char*,int,...) ; 
 int vm_fault_quick_hold_pages (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ,struct vm_page**,int) ; 
 int /*<<< orphan*/  vm_page_unhold_pages (struct vm_page**,int) ; 

int
physio(struct cdev *dev, struct uio *uio, int ioflag)
{
	struct cdevsw *csw;
	struct buf *pbuf;
	struct bio *bp;
	struct vm_page **pages;
	caddr_t sa;
	u_int iolen, poff;
	int error, i, npages, maxpages;
	vm_prot_t prot;

	csw = dev->si_devsw;
	npages = 0;
	sa = NULL;
	/* check if character device is being destroyed */
	if (csw == NULL)
		return (ENXIO);

	/* XXX: sanity check */
	if(dev->si_iosize_max < PAGE_SIZE) {
		printf("WARNING: %s si_iosize_max=%d, using DFLTPHYS.\n",
		    devtoname(dev), dev->si_iosize_max);
		dev->si_iosize_max = DFLTPHYS;
	}

	/*
	 * If the driver does not want I/O to be split, that means that we
	 * need to reject any requests that will not fit into one buffer.
	 */
	if (dev->si_flags & SI_NOSPLIT &&
	    (uio->uio_resid > dev->si_iosize_max || uio->uio_resid > MAXPHYS ||
	    uio->uio_iovcnt > 1)) {
		/*
		 * Tell the user why his I/O was rejected.
		 */
		if (uio->uio_resid > dev->si_iosize_max)
			uprintf("%s: request size=%zd > si_iosize_max=%d; "
			    "cannot split request\n", devtoname(dev),
			    uio->uio_resid, dev->si_iosize_max);
		if (uio->uio_resid > MAXPHYS)
			uprintf("%s: request size=%zd > MAXPHYS=%d; "
			    "cannot split request\n", devtoname(dev),
			    uio->uio_resid, MAXPHYS);
		if (uio->uio_iovcnt > 1)
			uprintf("%s: request vectors=%d > 1; "
			    "cannot split request\n", devtoname(dev),
			    uio->uio_iovcnt);
		return (EFBIG);
	}

	/*
	 * Keep the process UPAGES from being swapped.  Processes swapped
	 * out while holding pbufs, used by swapper, may lead to deadlock.
	 */
	PHOLD(curproc);

	bp = g_alloc_bio();
	if (uio->uio_segflg != UIO_USERSPACE) {
		pbuf = NULL;
		pages = NULL;
	} else if ((dev->si_flags & SI_UNMAPPED) && unmapped_buf_allowed) {
		pbuf = NULL;
		maxpages = btoc(MIN(uio->uio_resid, MAXPHYS)) + 1;
		pages = malloc(sizeof(*pages) * maxpages, M_DEVBUF, M_WAITOK);
	} else {
		pbuf = uma_zalloc(pbuf_zone, M_WAITOK);
		sa = pbuf->b_data;
		maxpages = btoc(MAXPHYS);
		pages = pbuf->b_pages;
	}
	prot = VM_PROT_READ;
	if (uio->uio_rw == UIO_READ)
		prot |= VM_PROT_WRITE;	/* Less backwards than it looks */
	error = 0;
	for (i = 0; i < uio->uio_iovcnt; i++) {
#ifdef RACCT
		if (racct_enable) {
			PROC_LOCK(curproc);
			if (uio->uio_rw == UIO_READ) {
				racct_add_force(curproc, RACCT_READBPS,
				    uio->uio_iov[i].iov_len);
				racct_add_force(curproc, RACCT_READIOPS, 1);
			} else {
				racct_add_force(curproc, RACCT_WRITEBPS,
				    uio->uio_iov[i].iov_len);
				racct_add_force(curproc, RACCT_WRITEIOPS, 1);
			}
			PROC_UNLOCK(curproc);
		}
#endif /* RACCT */

		while (uio->uio_iov[i].iov_len) {
			g_reset_bio(bp);
			if (uio->uio_rw == UIO_READ) {
				bp->bio_cmd = BIO_READ;
				curthread->td_ru.ru_inblock++;
			} else {
				bp->bio_cmd = BIO_WRITE;
				curthread->td_ru.ru_oublock++;
			}
			bp->bio_offset = uio->uio_offset;
			bp->bio_data = uio->uio_iov[i].iov_base;
			bp->bio_length = uio->uio_iov[i].iov_len;
			if (bp->bio_length > dev->si_iosize_max)
				bp->bio_length = dev->si_iosize_max;
			if (bp->bio_length > MAXPHYS)
				bp->bio_length = MAXPHYS;

			/*
			 * Make sure the pbuf can map the request.
			 * The pbuf has kvasize = MAXPHYS, so a request
			 * larger than MAXPHYS - PAGE_SIZE must be
			 * page aligned or it will be fragmented.
			 */
			poff = (vm_offset_t)bp->bio_data & PAGE_MASK;
			if (pbuf && bp->bio_length + poff > pbuf->b_kvasize) {
				if (dev->si_flags & SI_NOSPLIT) {
					uprintf("%s: request ptr %p is not "
					    "on a page boundary; cannot split "
					    "request\n", devtoname(dev),
					    bp->bio_data);
					error = EFBIG;
					goto doerror;
				}
				bp->bio_length = pbuf->b_kvasize;
				if (poff != 0)
					bp->bio_length -= PAGE_SIZE;
			}

			bp->bio_bcount = bp->bio_length;
			bp->bio_dev = dev;

			if (pages) {
				if ((npages = vm_fault_quick_hold_pages(
				    &curproc->p_vmspace->vm_map,
				    (vm_offset_t)bp->bio_data, bp->bio_length,
				    prot, pages, maxpages)) < 0) {
					error = EFAULT;
					goto doerror;
				}
				if (pbuf && sa) {
					pmap_qenter((vm_offset_t)sa,
					    pages, npages);
					bp->bio_data = sa + poff;
				} else {
					bp->bio_ma = pages;
					bp->bio_ma_n = npages;
					bp->bio_ma_offset = poff;
					bp->bio_data = unmapped_buf;
					bp->bio_flags |= BIO_UNMAPPED;
				}
			}

			csw->d_strategy(bp);
			if (uio->uio_rw == UIO_READ)
				biowait(bp, "physrd");
			else
				biowait(bp, "physwr");

			if (pages) {
				if (pbuf)
					pmap_qremove((vm_offset_t)sa, npages);
				vm_page_unhold_pages(pages, npages);
			}

			iolen = bp->bio_length - bp->bio_resid;
			if (iolen == 0 && !(bp->bio_flags & BIO_ERROR))
				goto doerror;	/* EOF */
			uio->uio_iov[i].iov_len -= iolen;
			uio->uio_iov[i].iov_base =
			    (char *)uio->uio_iov[i].iov_base + iolen;
			uio->uio_resid -= iolen;
			uio->uio_offset += iolen;
			if (bp->bio_flags & BIO_ERROR) {
				error = bp->bio_error;
				goto doerror;
			}
		}
	}
doerror:
	if (pbuf)
		uma_zfree(pbuf_zone, pbuf);
	else if (pages)
		free(pages, M_DEVBUF);
	g_destroy_bio(bp);
	PRELE(curproc);
	return (error);
}