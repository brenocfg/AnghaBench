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
struct vop_vptocnp_args {char* a_buf; int* a_buflen; struct vnode** a_vpp; struct vnode* a_vp; } ;
struct vnode {scalar_t__ v_type; struct mount* v_mount; struct pfs_vdata* v_data; } ;
struct pfs_vdata {int pvd_pid; struct pfs_node* pvd_pn; } ;
struct pfs_node {scalar_t__ pn_type; char* pn_name; struct pfs_node* pn_parent; } ;
struct mount {int dummy; } ;
typedef  int /*<<< orphan*/  pidbuf ;
typedef  int pid_t ;

/* Variables and functions */
 int ENOMEM ; 
 int LK_RETRY ; 
 int PFS_NAMELEN ; 
 int /*<<< orphan*/  PFS_RETURN (int) ; 
 scalar_t__ VDIR ; 
 int VOP_ISLOCKED (struct vnode*) ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (char*,char*,int) ; 
 int /*<<< orphan*/  pfs_lock (struct pfs_node*) ; 
 int /*<<< orphan*/  pfs_unlock (struct pfs_node*) ; 
 int pfs_vncache_alloc (struct mount*,struct vnode**,struct pfs_node*,int) ; 
 scalar_t__ pfstype_procdir ; 
 scalar_t__ pfstype_root ; 
 int snprintf (char*,int,char*,int) ; 
 int strlen (char*) ; 
 int vfs_busy (struct mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_unbusy (struct mount*) ; 
 int /*<<< orphan*/  vhold (struct vnode*) ; 
 int /*<<< orphan*/  vn_lock (struct vnode*,int) ; 

__attribute__((used)) static int
pfs_vptocnp(struct vop_vptocnp_args *ap)
{
	struct vnode *vp = ap->a_vp;
	struct vnode **dvp = ap->a_vpp;
	struct pfs_vdata *pvd = vp->v_data;
	struct pfs_node *pd = pvd->pvd_pn;
	struct pfs_node *pn;
	struct mount *mp;
	char *buf = ap->a_buf;
	int *buflen = ap->a_buflen;
	char pidbuf[PFS_NAMELEN];
	pid_t pid = pvd->pvd_pid;
	int len, i, error, locked;

	i = *buflen;
	error = 0;

	pfs_lock(pd);

	if (vp->v_type == VDIR && pd->pn_type == pfstype_root) {
		*dvp = vp;
		vhold(*dvp);
		pfs_unlock(pd);
		PFS_RETURN (0);
	} else if (vp->v_type == VDIR && pd->pn_type == pfstype_procdir) {
		len = snprintf(pidbuf, sizeof(pidbuf), "%d", pid);
		i -= len;
		if (i < 0) {
			error = ENOMEM;
			goto failed;
		}
		bcopy(pidbuf, buf + i, len);
	} else {
		len = strlen(pd->pn_name);
		i -= len;
		if (i < 0) {
			error = ENOMEM;
			goto failed;
		}
		bcopy(pd->pn_name, buf + i, len);
	}

	pn = pd->pn_parent;
	pfs_unlock(pd);

	mp = vp->v_mount;
	error = vfs_busy(mp, 0);
	if (error)
		return (error);

	/*
	 * vp is held by caller.
	 */
	locked = VOP_ISLOCKED(vp);
	VOP_UNLOCK(vp, 0);

	error = pfs_vncache_alloc(mp, dvp, pn, pid);
	if (error) {
		vn_lock(vp, locked | LK_RETRY);
		vfs_unbusy(mp);
		PFS_RETURN(error);
	}

	*buflen = i;
	VOP_UNLOCK(*dvp, 0);
	vn_lock(vp, locked | LK_RETRY);
	vfs_unbusy(mp);

	PFS_RETURN (0);
failed:
	pfs_unlock(pd);
	PFS_RETURN(error);
}