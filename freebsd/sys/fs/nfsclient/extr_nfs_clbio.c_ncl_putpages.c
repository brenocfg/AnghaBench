#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
struct vop_putpages_args {int a_count; int* a_rtvals; int /*<<< orphan*/  a_sync; TYPE_1__** a_m; struct vnode* a_vp; } ;
struct vnode {scalar_t__ v_type; int /*<<< orphan*/  v_mount; } ;
struct uio {int uio_iovcnt; int uio_resid; struct thread* uio_td; int /*<<< orphan*/  uio_rw; int /*<<< orphan*/  uio_segflg; scalar_t__ uio_offset; struct iovec* uio_iov; } ;
struct ucred {int dummy; } ;
struct thread {int /*<<< orphan*/ * td_ucred; } ;
struct nfsnode {int n_flag; scalar_t__ n_size; int /*<<< orphan*/ * n_writecred; } ;
struct nfsmount {int nm_flag; int nm_state; int /*<<< orphan*/  nm_mtx; } ;
struct iovec {int iov_len; int /*<<< orphan*/  iov_base; } ;
typedef  scalar_t__ off_t ;
struct TYPE_3__ {int /*<<< orphan*/  pindex; } ;

/* Variables and functions */
 scalar_t__ IDX_TO_OFF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFSLOCKNODE (struct nfsnode*) ; 
 int NFSMNT_NFSV3 ; 
 int NFSSTA_GOTFSINFO ; 
 int /*<<< orphan*/  NFSUNLOCKNODE (struct nfsnode*) ; 
 int NNONCACHE ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  UIO_NOCOPY ; 
 int /*<<< orphan*/  UIO_WRITE ; 
 struct nfsmount* VFSTONFS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_CNT_ADD (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VM_CNT_INC (int /*<<< orphan*/ ) ; 
 int VM_PAGER_ERROR ; 
 int VOP_WRITE (struct vnode*,struct uio*,int /*<<< orphan*/ ,struct ucred*) ; 
 scalar_t__ VREG ; 
 struct nfsnode* VTONFS (struct vnode*) ; 
 int btoc (int) ; 
 int /*<<< orphan*/  crfree (struct ucred*) ; 
 struct ucred* crhold (int /*<<< orphan*/ *) ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ncl_fsinfo (struct nfsmount*,struct vnode*,struct ucred*,struct thread*) ; 
 int /*<<< orphan*/  newnfs_directio_allow_mmap ; 
 scalar_t__ newnfs_directio_enable ; 
 int /*<<< orphan*/  nfs_keep_dirty_on_error ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  unmapped_buf ; 
 int /*<<< orphan*/  v_vnodeout ; 
 int /*<<< orphan*/  v_vnodepgsout ; 
 int /*<<< orphan*/  vnode_pager_putpages_ioflags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_pager_undirty_pages (TYPE_1__**,int*,int,scalar_t__,int) ; 

int
ncl_putpages(struct vop_putpages_args *ap)
{
	struct uio uio;
	struct iovec iov;
	int i, error, npages, count;
	off_t offset;
	int *rtvals;
	struct vnode *vp;
	struct thread *td;
	struct ucred *cred;
	struct nfsmount *nmp;
	struct nfsnode *np;
	vm_page_t *pages;

	vp = ap->a_vp;
	np = VTONFS(vp);
	td = curthread;				/* XXX */
	/* Set the cred to n_writecred for the write rpcs. */
	if (np->n_writecred != NULL)
		cred = crhold(np->n_writecred);
	else
		cred = crhold(curthread->td_ucred);	/* XXX */
	nmp = VFSTONFS(vp->v_mount);
	pages = ap->a_m;
	count = ap->a_count;
	rtvals = ap->a_rtvals;
	npages = btoc(count);
	offset = IDX_TO_OFF(pages[0]->pindex);

	mtx_lock(&nmp->nm_mtx);
	if ((nmp->nm_flag & NFSMNT_NFSV3) != 0 &&
	    (nmp->nm_state & NFSSTA_GOTFSINFO) == 0) {
		mtx_unlock(&nmp->nm_mtx);
		(void)ncl_fsinfo(nmp, vp, cred, td);
	} else
		mtx_unlock(&nmp->nm_mtx);

	NFSLOCKNODE(np);
	if (newnfs_directio_enable && !newnfs_directio_allow_mmap &&
	    (np->n_flag & NNONCACHE) && (vp->v_type == VREG)) {
		NFSUNLOCKNODE(np);
		printf("ncl_putpages: called on noncache-able vnode\n");
		NFSLOCKNODE(np);
	}
	/*
	 * When putting pages, do not extend file past EOF.
	 */
	if (offset + count > np->n_size) {
		count = np->n_size - offset;
		if (count < 0)
			count = 0;
	}
	NFSUNLOCKNODE(np);

	for (i = 0; i < npages; i++)
		rtvals[i] = VM_PAGER_ERROR;

	VM_CNT_INC(v_vnodeout);
	VM_CNT_ADD(v_vnodepgsout, count);

	iov.iov_base = unmapped_buf;
	iov.iov_len = count;
	uio.uio_iov = &iov;
	uio.uio_iovcnt = 1;
	uio.uio_offset = offset;
	uio.uio_resid = count;
	uio.uio_segflg = UIO_NOCOPY;
	uio.uio_rw = UIO_WRITE;
	uio.uio_td = td;

	error = VOP_WRITE(vp, &uio, vnode_pager_putpages_ioflags(ap->a_sync),
	    cred);
	crfree(cred);

	if (error == 0 || !nfs_keep_dirty_on_error) {
		vnode_pager_undirty_pages(pages, rtvals, count - uio.uio_resid,
		    np->n_size - offset, npages * PAGE_SIZE);
	}
	return (rtvals[0]);
}