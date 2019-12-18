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
struct vop_readlink_args {struct uio* a_uio; struct vnode* a_vp; } ;
struct vnode {scalar_t__ v_type; struct pfs_vdata* v_data; } ;
struct uio {int dummy; } ;
struct sbuf {int dummy; } ;
struct proc {int p_flag; } ;
struct pfs_vdata {scalar_t__ pvd_pid; struct pfs_node* pvd_pn; } ;
struct pfs_node {int /*<<< orphan*/ * pn_fill; int /*<<< orphan*/  pn_name; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENAMETOOLONG ; 
 int /*<<< orphan*/  KASSERT_PN_IS_LINK (struct pfs_node*) ; 
 int LK_RETRY ; 
 scalar_t__ NO_PID ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  PFS_RETURN (int) ; 
 int /*<<< orphan*/  PFS_TRACE (char*) ; 
 int /*<<< orphan*/  PRELE (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int P_WEXIT ; 
 scalar_t__ VLNK ; 
 int VOP_ISLOCKED (struct vnode*) ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _PHOLD (struct proc*) ; 
 int /*<<< orphan*/  curthread ; 
 struct proc* pfind (scalar_t__) ; 
 int /*<<< orphan*/  pfs_assert_not_owned (struct pfs_node*) ; 
 int pn_fill (int /*<<< orphan*/ ,struct proc*,struct pfs_node*,struct sbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sbuf_data (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_delete (struct sbuf*) ; 
 scalar_t__ sbuf_finish (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_len (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_new (struct sbuf*,char*,int,int /*<<< orphan*/ ) ; 
 int uiomove_frombuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uio*) ; 
 int /*<<< orphan*/  vdrop (struct vnode*) ; 
 int /*<<< orphan*/  vhold (struct vnode*) ; 
 int /*<<< orphan*/  vn_lock (struct vnode*,int) ; 

__attribute__((used)) static int
pfs_readlink(struct vop_readlink_args *va)
{
	struct vnode *vn = va->a_vp;
	struct pfs_vdata *pvd = vn->v_data;
	struct pfs_node *pn = pvd->pvd_pn;
	struct uio *uio = va->a_uio;
	struct proc *proc = NULL;
	char buf[PATH_MAX];
	struct sbuf sb;
	int error, locked;

	PFS_TRACE(("%s", pn->pn_name));
	pfs_assert_not_owned(pn);

	if (vn->v_type != VLNK)
		PFS_RETURN (EINVAL);
	KASSERT_PN_IS_LINK(pn);

	if (pn->pn_fill == NULL)
		PFS_RETURN (EIO);

	if (pvd->pvd_pid != NO_PID) {
		if ((proc = pfind(pvd->pvd_pid)) == NULL)
			PFS_RETURN (EIO);
		if (proc->p_flag & P_WEXIT) {
			PROC_UNLOCK(proc);
			PFS_RETURN (EIO);
		}
		_PHOLD(proc);
		PROC_UNLOCK(proc);
	}
	vhold(vn);
	locked = VOP_ISLOCKED(vn);
	VOP_UNLOCK(vn, 0);

	/* sbuf_new() can't fail with a static buffer */
	sbuf_new(&sb, buf, sizeof buf, 0);

	error = pn_fill(curthread, proc, pn, &sb, NULL);

	if (proc != NULL)
		PRELE(proc);
	vn_lock(vn, locked | LK_RETRY);
	vdrop(vn);

	if (error) {
		sbuf_delete(&sb);
		PFS_RETURN (error);
	}

	if (sbuf_finish(&sb) != 0) {
		sbuf_delete(&sb);
		PFS_RETURN (ENAMETOOLONG);
	}

	error = uiomove_frombuf(sbuf_data(&sb), sbuf_len(&sb), uio);
	sbuf_delete(&sb);
	PFS_RETURN (error);
}