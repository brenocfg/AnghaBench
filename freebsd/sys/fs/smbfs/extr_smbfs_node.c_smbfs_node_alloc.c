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
struct vnode {scalar_t__ v_type; int v_vflag; struct smbnode* v_data; int /*<<< orphan*/  v_vnlock; } ;
struct vattr {int dummy; } ;
struct thread {int /*<<< orphan*/  td_ucred; } ;
struct smbnode {int n_dosattr; char* n_rpath; int n_rplen; int n_nmlen; int /*<<< orphan*/  n_name; int /*<<< orphan*/  n_flag; int /*<<< orphan*/  n_ino; int /*<<< orphan*/  n_parentino; struct vnode* n_parent; void* n_mount; struct vnode* n_vnode; } ;
struct smbmount {int /*<<< orphan*/ * sm_root; } ;
struct smbfattr {int fa_attr; int /*<<< orphan*/  fa_ino; } ;
struct smbcmp {int n_nmlen; char const* n_name; struct vnode* n_parent; } ;
struct mount {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_VOP_LOCKED (struct vnode*,char*) ; 
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  LK_EXCLUSIVE ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  M_SMBNODE ; 
 int /*<<< orphan*/  M_SMBNODENAME ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  NREFPARENT ; 
 int /*<<< orphan*/  SMBERROR (char*,...) ; 
 int /*<<< orphan*/  SMBVDEBUG (char*) ; 
 int SMB_FA_DIR ; 
 scalar_t__ VDIR ; 
 void* VFSTOSMBFS (struct mount*) ; 
 int /*<<< orphan*/  VOP_GETATTR (struct vnode*,struct vattr*,int /*<<< orphan*/ ) ; 
 scalar_t__ VREG ; 
 struct smbnode* VTOSMB (struct vnode*) ; 
 int VV_ROOT ; 
 scalar_t__ bcmp (char const*,char*,int) ; 
 int /*<<< orphan*/  bcopy (char const*,char*,int) ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  free (struct smbnode*,int /*<<< orphan*/ ) ; 
 int getnewvnode (char*,struct mount*,int /*<<< orphan*/ *,struct vnode**) ; 
 int insmntque (struct vnode*,struct mount*) ; 
 int /*<<< orphan*/  lockmgr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smbfs_hash (char const*,int) ; 
 int /*<<< orphan*/  smbfs_name_alloc (char const*,int) ; 
 int /*<<< orphan*/  smbfs_vnode_cmp ; 
 int /*<<< orphan*/  smbfs_vnodeops ; 
 int vfs_hash_get (struct mount*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct thread*,struct vnode**,int /*<<< orphan*/ ,struct smbcmp*) ; 
 int vfs_hash_insert (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct thread*,struct vnode**,int /*<<< orphan*/ ,struct smbcmp*) ; 
 int vget (struct vnode*,int /*<<< orphan*/ ,struct thread*) ; 
 int /*<<< orphan*/  vgone (struct vnode*) ; 
 int /*<<< orphan*/  vn_printf (struct vnode*,char*) ; 
 int /*<<< orphan*/  vput (struct vnode*) ; 
 int /*<<< orphan*/  vref (struct vnode*) ; 

__attribute__((used)) static int
smbfs_node_alloc(struct mount *mp, struct vnode *dvp, const char *dirnm, 
	int dirlen, const char *name, int nmlen, char sep, 
	struct smbfattr *fap, struct vnode **vpp)
{
	struct vattr vattr;
	struct thread *td = curthread;	/* XXX */
	struct smbmount *smp = VFSTOSMBFS(mp);
	struct smbnode *np, *dnp;
	struct vnode *vp, *vp2;
	struct smbcmp sc;
	char *p, *rpath;
	int error, rplen;

	sc.n_parent = dvp;
	sc.n_nmlen = nmlen;
	sc.n_name = name;	
	if (smp->sm_root != NULL && dvp == NULL) {
		SMBERROR("do not allocate root vnode twice!\n");
		return EINVAL;
	}
	if (nmlen == 2 && bcmp(name, "..", 2) == 0) {
		if (dvp == NULL)
			return EINVAL;
		vp = VTOSMB(VTOSMB(dvp)->n_parent)->n_vnode;
		error = vget(vp, LK_EXCLUSIVE, td);
		if (error == 0)
			*vpp = vp;
		return error;
	} else if (nmlen == 1 && name[0] == '.') {
		SMBERROR("do not call me with dot!\n");
		return EINVAL;
	}
	dnp = dvp ? VTOSMB(dvp) : NULL;
	if (dnp == NULL && dvp != NULL) {
		vn_printf(dvp, "smbfs_node_alloc: dead parent vnode ");
		return EINVAL;
	}
	error = vfs_hash_get(mp, smbfs_hash(name, nmlen), LK_EXCLUSIVE, td,
	    vpp, smbfs_vnode_cmp, &sc);
	if (error)
		return (error);
	if (*vpp) {
		np = VTOSMB(*vpp);
		/* Force cached attributes to be refreshed if stale. */
		(void)VOP_GETATTR(*vpp, &vattr, td->td_ucred);
		/*
		 * If the file type on the server is inconsistent with
		 * what it was when we created the vnode, kill the
		 * bogus vnode now and fall through to the code below
		 * to create a new one with the right type.
		 */
		if (((*vpp)->v_type == VDIR && 
		    (np->n_dosattr & SMB_FA_DIR) == 0) ||
	    	    ((*vpp)->v_type == VREG && 
		    (np->n_dosattr & SMB_FA_DIR) != 0)) {
			vgone(*vpp);
			vput(*vpp);
		}
		else {
			SMBVDEBUG("vnode taken from the hashtable\n");
			return (0);
		}
	}
	/*
	 * If we don't have node attributes, then it is an explicit lookup
	 * for an existing vnode.
	 */
	if (fap == NULL)
		return ENOENT;

	error = getnewvnode("smbfs", mp, &smbfs_vnodeops, vpp);
	if (error)
		return (error);
	vp = *vpp;
	np = malloc(sizeof *np, M_SMBNODE, M_WAITOK | M_ZERO);
	rplen = dirlen;
	if (sep != '\0')
		rplen++;
	rplen += nmlen;
	rpath = malloc(rplen + 1, M_SMBNODENAME, M_WAITOK);
	p = rpath;
	bcopy(dirnm, p, dirlen);
	p += dirlen;
	if (sep != '\0')
		*p++ = sep;
	if (name != NULL) {
		bcopy(name, p, nmlen);
		p += nmlen;
	}
	*p = '\0';
	MPASS(p == rpath + rplen);
	lockmgr(vp->v_vnlock, LK_EXCLUSIVE, NULL);
	/* Vnode initialization */
	vp->v_type = fap->fa_attr & SMB_FA_DIR ? VDIR : VREG;
	vp->v_data = np;
	np->n_vnode = vp;
	np->n_mount = VFSTOSMBFS(mp);
	np->n_rpath = rpath;
	np->n_rplen = rplen;
	np->n_nmlen = nmlen;
	np->n_name = smbfs_name_alloc(name, nmlen);
	np->n_ino = fap->fa_ino;
	if (dvp) {
		ASSERT_VOP_LOCKED(dvp, "smbfs_node_alloc");
		np->n_parent = dvp;
		np->n_parentino = VTOSMB(dvp)->n_ino;
		if (/*vp->v_type == VDIR &&*/ (dvp->v_vflag & VV_ROOT) == 0) {
			vref(dvp);
			np->n_flag |= NREFPARENT;
		}
	} else if (vp->v_type == VREG)
		SMBERROR("new vnode '%s' born without parent ?\n", np->n_name);
	error = insmntque(vp, mp);
	if (error) {
		free(np, M_SMBNODE);
		return (error);
	}
	error = vfs_hash_insert(vp, smbfs_hash(name, nmlen), LK_EXCLUSIVE,
	    td, &vp2, smbfs_vnode_cmp, &sc);
	if (error) 
		return (error);
	if (vp2 != NULL)
		*vpp = vp2;
	return (0);
}