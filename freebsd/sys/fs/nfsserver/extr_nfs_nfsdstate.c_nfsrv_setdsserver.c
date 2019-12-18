#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vnode_t ;
struct nfsdevice {int nfsdev_mdsisset; int /*<<< orphan*/  nfsdev_mdsfsid; TYPE_3__** nfsdev_dsdir; int /*<<< orphan*/  nfsdev_nmp; TYPE_3__* nfsdev_dvp; } ;
struct nameidata {TYPE_3__* ni_vp; } ;
struct TYPE_6__ {int /*<<< orphan*/  f_fsid; } ;
struct mount {int mnt_flag; TYPE_2__ mnt_stat; TYPE_1__* mnt_vfc; } ;
struct TYPE_7__ {scalar_t__ v_type; struct mount* v_mount; } ;
struct TYPE_5__ {int /*<<< orphan*/  vfc_name; } ;
typedef  int /*<<< orphan*/  NFSPROC_T ;

/* Variables and functions */
 int ENOTDIR ; 
 int ENXIO ; 
 int FOLLOW ; 
 int LOCKLEAF ; 
 int LOCKSHARED ; 
 int /*<<< orphan*/  LOOKUP ; 
 int MNT_EXPORTED ; 
 int /*<<< orphan*/  M_NFSDSTATE ; 
 int /*<<< orphan*/  M_TEMP ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  NDINIT (struct nameidata*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NFSD_DEBUG (int,char*,...) ; 
 int /*<<< orphan*/  NFSVOPUNLOCK (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct nfsdevice*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 scalar_t__ VDIR ; 
 int /*<<< orphan*/  VFSTONFS (struct mount*) ; 
 int /*<<< orphan*/  atomic_add_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 void* malloc (size_t,int /*<<< orphan*/ ,int) ; 
 int namei (struct nameidata*) ; 
 int /*<<< orphan*/  nfsdev_list ; 
 int /*<<< orphan*/  nfsrv_devidcnt ; 
 int /*<<< orphan*/  nfsrv_devidhead ; 
 int nfsrv_dsdirsize ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  vput (TYPE_3__*) ; 

__attribute__((used)) static int
nfsrv_setdsserver(char *dspathp, char *mdspathp, NFSPROC_T *p,
    struct nfsdevice **dsp)
{
	struct nameidata nd;
	struct nfsdevice *ds;
	struct mount *mp;
	int error, i;
	char *dsdirpath;
	size_t dsdirsize;

	NFSD_DEBUG(4, "setdssrv path=%s\n", dspathp);
	*dsp = NULL;
	NDINIT(&nd, LOOKUP, FOLLOW | LOCKSHARED | LOCKLEAF, UIO_SYSSPACE,
	    dspathp, p);
	error = namei(&nd);
	NFSD_DEBUG(4, "lookup=%d\n", error);
	if (error != 0)
		return (error);
	if (nd.ni_vp->v_type != VDIR) {
		vput(nd.ni_vp);
		NFSD_DEBUG(4, "dspath not dir\n");
		return (ENOTDIR);
	}
	if (strcmp(nd.ni_vp->v_mount->mnt_vfc->vfc_name, "nfs") != 0) {
		vput(nd.ni_vp);
		NFSD_DEBUG(4, "dspath not an NFS mount\n");
		return (ENXIO);
	}

	/*
	 * Allocate a DS server structure with the NFS mounted directory
	 * vnode reference counted, so that a non-forced dismount will
	 * fail with EBUSY.
	 * This structure is always linked into the list, even if an error
	 * is being returned.  The caller will free the entire list upon
	 * an error return.
	 */
	*dsp = ds = malloc(sizeof(*ds) + nfsrv_dsdirsize * sizeof(vnode_t),
	    M_NFSDSTATE, M_WAITOK | M_ZERO);
	ds->nfsdev_dvp = nd.ni_vp;
	ds->nfsdev_nmp = VFSTONFS(nd.ni_vp->v_mount);
	NFSVOPUNLOCK(nd.ni_vp, 0);

	dsdirsize = strlen(dspathp) + 16;
	dsdirpath = malloc(dsdirsize, M_TEMP, M_WAITOK);
	/* Now, create the DS directory structures. */
	for (i = 0; i < nfsrv_dsdirsize; i++) {
		snprintf(dsdirpath, dsdirsize, "%s/ds%d", dspathp, i);
		NDINIT(&nd, LOOKUP, FOLLOW | LOCKSHARED | LOCKLEAF,
		    UIO_SYSSPACE, dsdirpath, p);
		error = namei(&nd);
		NFSD_DEBUG(4, "dsdirpath=%s lookup=%d\n", dsdirpath, error);
		if (error != 0)
			break;
		if (nd.ni_vp->v_type != VDIR) {
			vput(nd.ni_vp);
			error = ENOTDIR;
			NFSD_DEBUG(4, "dsdirpath not a VDIR\n");
			break;
		}
		if (strcmp(nd.ni_vp->v_mount->mnt_vfc->vfc_name, "nfs") != 0) {
			vput(nd.ni_vp);
			error = ENXIO;
			NFSD_DEBUG(4, "dsdirpath not an NFS mount\n");
			break;
		}
		ds->nfsdev_dsdir[i] = nd.ni_vp;
		NFSVOPUNLOCK(nd.ni_vp, 0);
	}
	free(dsdirpath, M_TEMP);

	if (strlen(mdspathp) > 0) {
		/*
		 * This DS stores file for a specific MDS exported file
		 * system.
		 */
		NDINIT(&nd, LOOKUP, FOLLOW | LOCKSHARED | LOCKLEAF,
		    UIO_SYSSPACE, mdspathp, p);
		error = namei(&nd);
		NFSD_DEBUG(4, "mds lookup=%d\n", error);
		if (error != 0)
			goto out;
		if (nd.ni_vp->v_type != VDIR) {
			vput(nd.ni_vp);
			error = ENOTDIR;
			NFSD_DEBUG(4, "mdspath not dir\n");
			goto out;
		}
		mp = nd.ni_vp->v_mount;
		if ((mp->mnt_flag & MNT_EXPORTED) == 0) {
			vput(nd.ni_vp);
			error = ENXIO;
			NFSD_DEBUG(4, "mdspath not an exported fs\n");
			goto out;
		}
		ds->nfsdev_mdsfsid = mp->mnt_stat.f_fsid;
		ds->nfsdev_mdsisset = 1;
		vput(nd.ni_vp);
	}

out:
	TAILQ_INSERT_TAIL(&nfsrv_devidhead, ds, nfsdev_list);
	atomic_add_int(&nfsrv_devidcnt, 1);
	return (error);
}