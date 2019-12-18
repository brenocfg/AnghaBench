#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vnode {scalar_t__ v_type; TYPE_2__* v_mount; } ;
struct pnfsdsfile {int dsf_dir; int /*<<< orphan*/  dsf_filename; } ;
struct nfsmount {int dummy; } ;
struct nfsdevice {int dummy; } ;
struct nameidata {struct vnode* ni_vp; } ;
struct TYPE_4__ {TYPE_1__* mnt_vfc; } ;
struct TYPE_3__ {int /*<<< orphan*/  vfc_name; } ;
typedef  int /*<<< orphan*/  NFSPROC_T ;

/* Variables and functions */
 int EISDIR ; 
 int ENOTDIR ; 
 int ENXIO ; 
 int EPERM ; 
 int FOLLOW ; 
 int LOCKLEAF ; 
 int LOCKSHARED ; 
 int /*<<< orphan*/  LOOKUP ; 
 int /*<<< orphan*/  NDINIT (struct nameidata*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NFSDDSLOCK () ; 
 int /*<<< orphan*/  NFSDDSUNLOCK () ; 
 int /*<<< orphan*/  NFSD_DEBUG (int,char*,...) ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 scalar_t__ VDIR ; 
 struct nfsmount* VFSTONFS (TYPE_2__*) ; 
 scalar_t__ VREG ; 
 int namei (struct nameidata*) ; 
 int nfsrv_dsgetsockmnt (struct vnode*,int /*<<< orphan*/ ,char*,int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,struct vnode**,struct nfsmount**,struct nfsmount*,int*,int*) ; 
 struct nfsdevice* nfsrv_findmirroredds (struct nfsmount*) ; 
 struct nfsdevice* nfsv4_findmirror (struct nfsmount*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  vput (struct vnode*) ; 

int
nfsrv_mdscopymr(char *mdspathp, char *dspathp, char *curdspathp, char *buf,
    int *buflenp, char *fname, NFSPROC_T *p, struct vnode **vpp,
    struct vnode **nvpp, struct pnfsdsfile **pfp, struct nfsdevice **dsp,
    struct nfsdevice **fdsp)
{
	struct nameidata nd;
	struct vnode *vp, *curvp;
	struct pnfsdsfile *pf;
	struct nfsmount *nmp, *curnmp;
	int dsdir, error, mirrorcnt, ippos;

	vp = NULL;
	curvp = NULL;
	curnmp = NULL;
	*dsp = NULL;
	*fdsp = NULL;
	if (dspathp == NULL && curdspathp != NULL)
		return (EPERM);

	/*
	 * Look up the MDS file shared locked.  The lock will be upgraded
	 * to an exclusive lock after any rw layouts have been returned.
	 */
	NFSD_DEBUG(4, "mdsopen path=%s\n", mdspathp);
	NDINIT(&nd, LOOKUP, FOLLOW | LOCKSHARED | LOCKLEAF, UIO_SYSSPACE,
	    mdspathp, p);
	error = namei(&nd);
	NFSD_DEBUG(4, "lookup=%d\n", error);
	if (error != 0)
		return (error);
	if (nd.ni_vp->v_type != VREG) {
		vput(nd.ni_vp);
		NFSD_DEBUG(4, "mdspath not reg\n");
		return (EISDIR);
	}
	vp = nd.ni_vp;

	if (curdspathp != NULL) {
		/*
		 * Look up the current DS path and find the nfsdev structure for
		 * it.
		 */
		NFSD_DEBUG(4, "curmdsdev path=%s\n", curdspathp);
		NDINIT(&nd, LOOKUP, FOLLOW | LOCKSHARED | LOCKLEAF,
		    UIO_SYSSPACE, curdspathp, p);
		error = namei(&nd);
		NFSD_DEBUG(4, "ds lookup=%d\n", error);
		if (error != 0) {
			vput(vp);
			return (error);
		}
		if (nd.ni_vp->v_type != VDIR) {
			vput(nd.ni_vp);
			vput(vp);
			NFSD_DEBUG(4, "curdspath not dir\n");
			return (ENOTDIR);
		}
		if (strcmp(nd.ni_vp->v_mount->mnt_vfc->vfc_name, "nfs") != 0) {
			vput(nd.ni_vp);
			vput(vp);
			NFSD_DEBUG(4, "curdspath not an NFS mount\n");
			return (ENXIO);
		}
		curnmp = VFSTONFS(nd.ni_vp->v_mount);
	
		/* Search the nfsdev list for a match. */
		NFSDDSLOCK();
		*fdsp = nfsv4_findmirror(curnmp);
		NFSDDSUNLOCK();
		if (*fdsp == NULL)
			curnmp = NULL;
		if (curnmp == NULL) {
			vput(nd.ni_vp);
			vput(vp);
			NFSD_DEBUG(4, "mdscopymr: no current ds\n");
			return (ENXIO);
		}
		curvp = nd.ni_vp;
	}

	if (dspathp != NULL) {
		/* Look up the nfsdev path and find the nfsdev structure. */
		NFSD_DEBUG(4, "mdsdev path=%s\n", dspathp);
		NDINIT(&nd, LOOKUP, FOLLOW | LOCKSHARED | LOCKLEAF,
		    UIO_SYSSPACE, dspathp, p);
		error = namei(&nd);
		NFSD_DEBUG(4, "ds lookup=%d\n", error);
		if (error != 0) {
			vput(vp);
			if (curvp != NULL)
				vput(curvp);
			return (error);
		}
		if (nd.ni_vp->v_type != VDIR || nd.ni_vp == curvp) {
			vput(nd.ni_vp);
			vput(vp);
			if (curvp != NULL)
				vput(curvp);
			NFSD_DEBUG(4, "dspath not dir\n");
			if (nd.ni_vp == curvp)
				return (EPERM);
			return (ENOTDIR);
		}
		if (strcmp(nd.ni_vp->v_mount->mnt_vfc->vfc_name, "nfs") != 0) {
			vput(nd.ni_vp);
			vput(vp);
			if (curvp != NULL)
				vput(curvp);
			NFSD_DEBUG(4, "dspath not an NFS mount\n");
			return (ENXIO);
		}
		nmp = VFSTONFS(nd.ni_vp->v_mount);
	
		/*
		 * Search the nfsdevice list for a match.  If curnmp == NULL,
		 * this is a recovery and there must be a mirror.
		 */
		NFSDDSLOCK();
		if (curnmp == NULL)
			*dsp = nfsrv_findmirroredds(nmp);
		else
			*dsp = nfsv4_findmirror(nmp);
		NFSDDSUNLOCK();
		if (*dsp == NULL) {
			vput(nd.ni_vp);
			vput(vp);
			if (curvp != NULL)
				vput(curvp);
			NFSD_DEBUG(4, "mdscopymr: no ds\n");
			return (ENXIO);
		}
	} else {
		nd.ni_vp = NULL;
		nmp = NULL;
	}

	/*
	 * Get a vp for an available DS data file using the extended
	 * attribute on the MDS file.
	 * If there is a valid entry for the new DS in the extended attribute
	 * on the MDS file (as checked via the nmp argument),
	 * nfsrv_dsgetsockmnt() returns EEXIST, so no copying will occur.
	 */
	error = nfsrv_dsgetsockmnt(vp, 0, buf, buflenp, &mirrorcnt, p,
	    NULL, NULL, NULL, fname, nvpp, &nmp, curnmp, &ippos, &dsdir);
	if (curvp != NULL)
		vput(curvp);
	if (nd.ni_vp == NULL) {
		if (error == 0 && nmp != NULL) {
			/* Search the nfsdev list for a match. */
			NFSDDSLOCK();
			*dsp = nfsrv_findmirroredds(nmp);
			NFSDDSUNLOCK();
		}
		if (error == 0 && (nmp == NULL || *dsp == NULL)) {
			if (nvpp != NULL && *nvpp != NULL) {
				vput(*nvpp);
				*nvpp = NULL;
			}
			error = ENXIO;
		}
	} else
		vput(nd.ni_vp);

	/*
	 * When dspathp != NULL and curdspathp == NULL, this is a recovery
	 * and is only allowed if there is a 0.0.0.0 IP address entry.
	 * When curdspathp != NULL, the ippos will be set to that entry.
	 */
	if (error == 0 && dspathp != NULL && ippos == -1) {
		if (nvpp != NULL && *nvpp != NULL) {
			vput(*nvpp);
			*nvpp = NULL;
		}
		error = ENXIO;
	}
	if (error == 0) {
		*vpp = vp;

		pf = (struct pnfsdsfile *)buf;
		if (ippos == -1) {
			/* If no zeroip pnfsdsfile, add one. */
			ippos = *buflenp / sizeof(*pf);
			*buflenp += sizeof(*pf);
			pf += ippos;
			pf->dsf_dir = dsdir;
			strlcpy(pf->dsf_filename, fname,
			    sizeof(pf->dsf_filename));
		} else
			pf += ippos;
		*pfp = pf;
	} else
		vput(vp);
	return (error);
}