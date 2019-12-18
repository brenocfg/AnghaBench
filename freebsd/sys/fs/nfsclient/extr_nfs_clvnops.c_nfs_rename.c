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
struct vop_rename_args {struct vnode* a_tdvp; struct vnode* a_fvp; struct componentname* a_fcnp; struct componentname* a_tcnp; struct vnode* a_fdvp; struct vnode* a_tvp; } ;
struct vnode {scalar_t__ v_mount; scalar_t__ v_type; } ;
struct nfsv4node {int n4_namelen; scalar_t__ n4_fhlen; int /*<<< orphan*/  n4_data; } ;
struct nfsnode {struct nfsv4node* n_v4; TYPE_1__* n_fhp; int /*<<< orphan*/  n_sillyrename; } ;
struct componentname {int cn_flags; int cn_namelen; int /*<<< orphan*/  cn_nameptr; int /*<<< orphan*/  cn_thread; int /*<<< orphan*/  cn_cred; } ;
struct TYPE_2__ {int nfh_len; int /*<<< orphan*/  nfh_fh; } ;

/* Variables and functions */
 int ENOENT ; 
 int EXDEV ; 
 int HASBUF ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  LK_EXCLUSIVE ; 
 int /*<<< orphan*/  MNT_WAIT ; 
 int /*<<< orphan*/  M_NFSV4NODE ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  NFS4NODENAME (struct nfsv4node*) ; 
 scalar_t__ NFSBCMP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NFSBCOPY (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NFSLOCKNODE (struct nfsnode*) ; 
 int /*<<< orphan*/  NFSUNLOCKNODE (struct nfsnode*) ; 
 int NFSVOPLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFSVOPUNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 scalar_t__ NFS_ISV4 (struct vnode*) ; 
 scalar_t__ VDIR ; 
 int VOP_FSYNC (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ VREG ; 
 struct nfsnode* VTONFS (struct vnode*) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  cache_purge (struct vnode*) ; 
 int /*<<< orphan*/  free (struct nfsv4node*,int /*<<< orphan*/ ) ; 
 struct nfsv4node* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nfs_renamerpc (struct vnode*,struct vnode*,int /*<<< orphan*/ ,int,struct vnode*,struct vnode*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_sillyrename (struct vnode*,struct vnode*,struct componentname*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  vput (struct vnode*) ; 
 int vrefcnt (struct vnode*) ; 
 int /*<<< orphan*/  vrele (struct vnode*) ; 

__attribute__((used)) static int
nfs_rename(struct vop_rename_args *ap)
{
	struct vnode *fvp = ap->a_fvp;
	struct vnode *tvp = ap->a_tvp;
	struct vnode *fdvp = ap->a_fdvp;
	struct vnode *tdvp = ap->a_tdvp;
	struct componentname *tcnp = ap->a_tcnp;
	struct componentname *fcnp = ap->a_fcnp;
	struct nfsnode *fnp = VTONFS(ap->a_fvp);
	struct nfsnode *tdnp = VTONFS(ap->a_tdvp);
	struct nfsv4node *newv4 = NULL;
	int error;

	KASSERT((tcnp->cn_flags & HASBUF) != 0 &&
	    (fcnp->cn_flags & HASBUF) != 0, ("nfs_rename: no name"));
	/* Check for cross-device rename */
	if ((fvp->v_mount != tdvp->v_mount) ||
	    (tvp && (fvp->v_mount != tvp->v_mount))) {
		error = EXDEV;
		goto out;
	}

	if (fvp == tvp) {
		printf("nfs_rename: fvp == tvp (can't happen)\n");
		error = 0;
		goto out;
	}
	if ((error = NFSVOPLOCK(fvp, LK_EXCLUSIVE)) != 0)
		goto out;

	/*
	 * We have to flush B_DELWRI data prior to renaming
	 * the file.  If we don't, the delayed-write buffers
	 * can be flushed out later after the file has gone stale
	 * under NFSV3.  NFSV2 does not have this problem because
	 * ( as far as I can tell ) it flushes dirty buffers more
	 * often.
	 * 
	 * Skip the rename operation if the fsync fails, this can happen
	 * due to the server's volume being full, when we pushed out data
	 * that was written back to our cache earlier. Not checking for
	 * this condition can result in potential (silent) data loss.
	 */
	error = VOP_FSYNC(fvp, MNT_WAIT, fcnp->cn_thread);
	NFSVOPUNLOCK(fvp, 0);
	if (!error && tvp)
		error = VOP_FSYNC(tvp, MNT_WAIT, tcnp->cn_thread);
	if (error)
		goto out;

	/*
	 * If the tvp exists and is in use, sillyrename it before doing the
	 * rename of the new file over it.
	 * XXX Can't sillyrename a directory.
	 */
	if (tvp && vrefcnt(tvp) > 1 && !VTONFS(tvp)->n_sillyrename &&
		tvp->v_type != VDIR && !nfs_sillyrename(tdvp, tvp, tcnp)) {
		vput(tvp);
		tvp = NULL;
	}

	error = nfs_renamerpc(fdvp, fvp, fcnp->cn_nameptr, fcnp->cn_namelen,
	    tdvp, tvp, tcnp->cn_nameptr, tcnp->cn_namelen, tcnp->cn_cred,
	    tcnp->cn_thread);

	if (error == 0 && NFS_ISV4(tdvp)) {
		/*
		 * For NFSv4, check to see if it is the same name and
		 * replace the name, if it is different.
		 */
		newv4 = malloc(
		    sizeof (struct nfsv4node) +
		    tdnp->n_fhp->nfh_len + tcnp->cn_namelen - 1,
		    M_NFSV4NODE, M_WAITOK);
		NFSLOCKNODE(tdnp);
		NFSLOCKNODE(fnp);
		if (fnp->n_v4 != NULL && fvp->v_type == VREG &&
		    (fnp->n_v4->n4_namelen != tcnp->cn_namelen ||
		      NFSBCMP(tcnp->cn_nameptr, NFS4NODENAME(fnp->n_v4),
		      tcnp->cn_namelen) ||
		      tdnp->n_fhp->nfh_len != fnp->n_v4->n4_fhlen ||
		      NFSBCMP(tdnp->n_fhp->nfh_fh, fnp->n_v4->n4_data,
			tdnp->n_fhp->nfh_len))) {
#ifdef notdef
{ char nnn[100]; int nnnl;
nnnl = (tcnp->cn_namelen < 100) ? tcnp->cn_namelen : 99;
bcopy(tcnp->cn_nameptr, nnn, nnnl);
nnn[nnnl] = '\0';
printf("ren replace=%s\n",nnn);
}
#endif
			free(fnp->n_v4, M_NFSV4NODE);
			fnp->n_v4 = newv4;
			newv4 = NULL;
			fnp->n_v4->n4_fhlen = tdnp->n_fhp->nfh_len;
			fnp->n_v4->n4_namelen = tcnp->cn_namelen;
			NFSBCOPY(tdnp->n_fhp->nfh_fh, fnp->n_v4->n4_data,
			    tdnp->n_fhp->nfh_len);
			NFSBCOPY(tcnp->cn_nameptr,
			    NFS4NODENAME(fnp->n_v4), tcnp->cn_namelen);
		}
		NFSUNLOCKNODE(tdnp);
		NFSUNLOCKNODE(fnp);
		if (newv4 != NULL)
			free(newv4, M_NFSV4NODE);
	}

	if (fvp->v_type == VDIR) {
		if (tvp != NULL && tvp->v_type == VDIR)
			cache_purge(tdvp);
		cache_purge(fdvp);
	}

out:
	if (tdvp == tvp)
		vrele(tdvp);
	else
		vput(tdvp);
	if (tvp)
		vput(tvp);
	vrele(fdvp);
	vrele(fvp);
	/*
	 * Kludge: Map ENOENT => 0 assuming that it is a reply to a retry.
	 */
	if (error == ENOENT)
		error = 0;
	return (error);
}