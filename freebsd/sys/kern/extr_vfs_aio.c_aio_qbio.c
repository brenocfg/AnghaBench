#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_prot_t ;
typedef  int vm_offset_t ;
struct TYPE_4__ {int bo_bsize; } ;
struct vnode {scalar_t__ v_type; TYPE_1__ v_bufobj; } ;
struct proc {struct kaioinfo* p_aioinfo; } ;
struct kaioinfo {scalar_t__ kaio_buffer_count; } ;
struct aiocb {scalar_t__ aio_lio_opcode; int aio_nbytes; int /*<<< orphan*/  aio_offset; scalar_t__ aio_buf; } ;
struct kaiocb {struct bio* bp; struct buf* pbuf; int /*<<< orphan*/  npages; int /*<<< orphan*/  pages; struct file* fd_file; struct aiocb uaiocb; } ;
struct file {scalar_t__ f_type; struct vnode* f_vnode; } ;
struct cdevsw {int d_flags; int /*<<< orphan*/  (* d_strategy ) (struct bio*) ;} ;
struct cdev {int si_iosize_max; int si_flags; } ;
struct buf {void* b_data; } ;
struct bio {int bio_length; int bio_bcount; int bio_ma_offset; int /*<<< orphan*/  bio_flags; void* bio_data; int /*<<< orphan*/  bio_ma_n; int /*<<< orphan*/  bio_ma; void* bio_caller1; struct cdev* bio_dev; int /*<<< orphan*/  bio_cmd; int /*<<< orphan*/  bio_offset; int /*<<< orphan*/  bio_done; } ;
struct TYPE_6__ {TYPE_2__* p_vmspace; } ;
struct TYPE_5__ {int /*<<< orphan*/  vm_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  AIO_LOCK (struct kaioinfo*) ; 
 int /*<<< orphan*/  AIO_UNLOCK (struct kaioinfo*) ; 
 int /*<<< orphan*/  BIO_READ ; 
 int /*<<< orphan*/  BIO_UNMAPPED ; 
 int /*<<< orphan*/  BIO_WRITE ; 
 int /*<<< orphan*/  BUF_KERNPROC (struct buf*) ; 
 scalar_t__ DTYPE_VNODE ; 
 int D_DISK ; 
 int EAGAIN ; 
 int EFAULT ; 
 int ENXIO ; 
 scalar_t__ LIO_READ ; 
 scalar_t__ LIO_WRITE ; 
 int MAXPHYS ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int PAGE_MASK ; 
 int SI_UNMAPPED ; 
 scalar_t__ VCHR ; 
 int /*<<< orphan*/  VM_PROT_READ ; 
 int /*<<< orphan*/  VM_PROT_WRITE ; 
 int /*<<< orphan*/  aio_biowakeup ; 
 int /*<<< orphan*/  atomic_add_int (int /*<<< orphan*/ *,int) ; 
 TYPE_3__* curproc ; 
 int /*<<< orphan*/  dev_relthread (struct cdev*,int) ; 
 struct cdevsw* devvn_refthread (struct vnode*,struct cdev**,int*) ; 
 struct bio* g_alloc_bio () ; 
 int /*<<< orphan*/  g_destroy_bio (struct bio*) ; 
 scalar_t__ max_buf_aio ; 
 int /*<<< orphan*/  nitems (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  num_buf_aio ; 
 int /*<<< orphan*/  num_unmapped_aio ; 
 int /*<<< orphan*/  pbuf_zone ; 
 int /*<<< orphan*/  pmap_qenter (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct bio*) ; 
 struct buf* uma_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct buf*) ; 
 void* unmapped_buf ; 
 scalar_t__ unmapped_buf_allowed ; 
 int /*<<< orphan*/  vm_fault_quick_hold_pages (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aio_qbio(struct proc *p, struct kaiocb *job)
{
	struct aiocb *cb;
	struct file *fp;
	struct bio *bp;
	struct buf *pbuf;
	struct vnode *vp;
	struct cdevsw *csw;
	struct cdev *dev;
	struct kaioinfo *ki;
	int error, ref, poff;
	vm_prot_t prot;

	cb = &job->uaiocb;
	fp = job->fd_file;

	if (!(cb->aio_lio_opcode == LIO_WRITE ||
	    cb->aio_lio_opcode == LIO_READ))
		return (-1);
	if (fp == NULL || fp->f_type != DTYPE_VNODE)
		return (-1);

	vp = fp->f_vnode;
	if (vp->v_type != VCHR)
		return (-1);
	if (vp->v_bufobj.bo_bsize == 0)
		return (-1);
	if (cb->aio_nbytes % vp->v_bufobj.bo_bsize)
		return (-1);

	ref = 0;
	csw = devvn_refthread(vp, &dev, &ref);
	if (csw == NULL)
		return (ENXIO);

	if ((csw->d_flags & D_DISK) == 0) {
		error = -1;
		goto unref;
	}
	if (cb->aio_nbytes > dev->si_iosize_max) {
		error = -1;
		goto unref;
	}

	ki = p->p_aioinfo;
	poff = (vm_offset_t)cb->aio_buf & PAGE_MASK;
	if ((dev->si_flags & SI_UNMAPPED) && unmapped_buf_allowed) {
		if (cb->aio_nbytes > MAXPHYS) {
			error = -1;
			goto unref;
		}

		pbuf = NULL;
	} else {
		if (cb->aio_nbytes > MAXPHYS - poff) {
			error = -1;
			goto unref;
		}
		if (ki->kaio_buffer_count >= max_buf_aio) {
			error = EAGAIN;
			goto unref;
		}

		job->pbuf = pbuf = uma_zalloc(pbuf_zone, M_WAITOK);
		BUF_KERNPROC(pbuf);
		AIO_LOCK(ki);
		ki->kaio_buffer_count++;
		AIO_UNLOCK(ki);
	}
	job->bp = bp = g_alloc_bio();

	bp->bio_length = cb->aio_nbytes;
	bp->bio_bcount = cb->aio_nbytes;
	bp->bio_done = aio_biowakeup;
	bp->bio_data = (void *)(uintptr_t)cb->aio_buf;
	bp->bio_offset = cb->aio_offset;
	bp->bio_cmd = cb->aio_lio_opcode == LIO_WRITE ? BIO_WRITE : BIO_READ;
	bp->bio_dev = dev;
	bp->bio_caller1 = (void *)job;

	prot = VM_PROT_READ;
	if (cb->aio_lio_opcode == LIO_READ)
		prot |= VM_PROT_WRITE;	/* Less backwards than it looks */
	job->npages = vm_fault_quick_hold_pages(&curproc->p_vmspace->vm_map,
	    (vm_offset_t)bp->bio_data, bp->bio_length, prot, job->pages,
	    nitems(job->pages));
	if (job->npages < 0) {
		error = EFAULT;
		goto doerror;
	}
	if (pbuf != NULL) {
		pmap_qenter((vm_offset_t)pbuf->b_data,
		    job->pages, job->npages);
		bp->bio_data = pbuf->b_data + poff;
		atomic_add_int(&num_buf_aio, 1);
	} else {
		bp->bio_ma = job->pages;
		bp->bio_ma_n = job->npages;
		bp->bio_ma_offset = poff;
		bp->bio_data = unmapped_buf;
		bp->bio_flags |= BIO_UNMAPPED;
		atomic_add_int(&num_unmapped_aio, 1);
	}

	/* Perform transfer. */
	csw->d_strategy(bp);
	dev_relthread(dev, ref);
	return (0);

doerror:
	if (pbuf != NULL) {
		AIO_LOCK(ki);
		ki->kaio_buffer_count--;
		AIO_UNLOCK(ki);
		uma_zfree(pbuf_zone, pbuf);
		job->pbuf = NULL;
	}
	g_destroy_bio(bp);
	job->bp = NULL;
unref:
	dev_relthread(dev, ref);
	return (error);
}