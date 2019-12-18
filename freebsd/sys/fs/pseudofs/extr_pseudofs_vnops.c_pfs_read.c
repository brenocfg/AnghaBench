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
struct vop_read_args {struct uio* a_uio; struct vnode* a_vp; } ;
struct vnode {scalar_t__ v_type; struct pfs_vdata* v_data; } ;
struct uio {scalar_t__ uio_resid; scalar_t__ uio_offset; } ;
struct sbuf {int dummy; } ;
struct proc {int dummy; } ;
struct pfs_vdata {int /*<<< orphan*/  pvd_pid; struct pfs_node* pvd_pn; } ;
struct pfs_node {int pn_flags; int /*<<< orphan*/ * pn_fill; int /*<<< orphan*/  pn_name; } ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int EBADF ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  KASSERT_PN_IS_FILE (struct pfs_node*) ; 
 int LK_RETRY ; 
 scalar_t__ MAXPHYS ; 
 scalar_t__ OFF_MAX ; 
 int PFS_RAWRD ; 
 int PFS_RD ; 
 int /*<<< orphan*/  PFS_RETURN (int) ; 
 int /*<<< orphan*/  PFS_TRACE (char*) ; 
 int /*<<< orphan*/  PRELE (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int VOP_ISLOCKED (struct vnode*) ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 scalar_t__ VREG ; 
 int /*<<< orphan*/  _PHOLD (struct proc*) ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  pfs_assert_not_owned (struct pfs_node*) ; 
 int /*<<< orphan*/  pfs_visible (int /*<<< orphan*/ ,struct pfs_node*,int /*<<< orphan*/ ,struct proc**) ; 
 int pn_fill (int /*<<< orphan*/ ,struct proc*,struct pfs_node*,struct sbuf*,struct uio*) ; 
 int /*<<< orphan*/  sbuf_data (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_delete (struct sbuf*) ; 
 scalar_t__ sbuf_finish (struct sbuf*) ; 
 scalar_t__ sbuf_len (struct sbuf*) ; 
 struct sbuf* sbuf_new (struct sbuf*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int uiomove_frombuf (int /*<<< orphan*/ ,scalar_t__,struct uio*) ; 
 int /*<<< orphan*/  vdrop (struct vnode*) ; 
 int /*<<< orphan*/  vhold (struct vnode*) ; 
 int /*<<< orphan*/  vn_lock (struct vnode*,int) ; 

__attribute__((used)) static int
pfs_read(struct vop_read_args *va)
{
	struct vnode *vn = va->a_vp;
	struct pfs_vdata *pvd = vn->v_data;
	struct pfs_node *pn = pvd->pvd_pn;
	struct uio *uio = va->a_uio;
	struct proc *proc;
	struct sbuf *sb = NULL;
	int error, locked;
	off_t buflen;

	PFS_TRACE(("%s", pn->pn_name));
	pfs_assert_not_owned(pn);

	if (vn->v_type != VREG)
		PFS_RETURN (EINVAL);
	KASSERT_PN_IS_FILE(pn);

	if (!(pn->pn_flags & PFS_RD))
		PFS_RETURN (EBADF);

	if (pn->pn_fill == NULL)
		PFS_RETURN (EIO);

	/*
	 * This is necessary because either process' privileges may
	 * have changed since the open() call.
	 */
	if (!pfs_visible(curthread, pn, pvd->pvd_pid, &proc))
		PFS_RETURN (EIO);
	if (proc != NULL) {
		_PHOLD(proc);
		PROC_UNLOCK(proc);
	}

	vhold(vn);
	locked = VOP_ISLOCKED(vn);
	VOP_UNLOCK(vn, 0);

	if (pn->pn_flags & PFS_RAWRD) {
		PFS_TRACE(("%zd resid", uio->uio_resid));
		error = pn_fill(curthread, proc, pn, NULL, uio);
		PFS_TRACE(("%zd resid", uio->uio_resid));
		goto ret;
	}

	if (uio->uio_resid < 0 || uio->uio_offset < 0 ||
	    uio->uio_resid > OFF_MAX - uio->uio_offset) {
		error = EINVAL;
		goto ret;
	}
	buflen = uio->uio_offset + uio->uio_resid;
	if (buflen > MAXPHYS)
		buflen = MAXPHYS;

	sb = sbuf_new(sb, NULL, buflen + 1, 0);
	if (sb == NULL) {
		error = EIO;
		goto ret;
	}

	error = pn_fill(curthread, proc, pn, sb, uio);

	if (error) {
		sbuf_delete(sb);
		goto ret;
	}

	/*
	 * XXX: If the buffer overflowed, sbuf_len() will not return
	 * the data length. Then just use the full length because an
	 * overflowed sbuf must be full.
	 */
	if (sbuf_finish(sb) == 0)
		buflen = sbuf_len(sb);
	error = uiomove_frombuf(sbuf_data(sb), buflen, uio);
	sbuf_delete(sb);
ret:
	vn_lock(vn, locked | LK_RETRY);
	vdrop(vn);
	if (proc != NULL)
		PRELE(proc);
	PFS_RETURN (error);
}