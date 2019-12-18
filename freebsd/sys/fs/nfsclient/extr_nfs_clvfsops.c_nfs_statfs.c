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
typedef  scalar_t__ uid_t ;
struct vnode {int dummy; } ;
struct thread {int /*<<< orphan*/  td_ucred; } ;
struct statfs {int /*<<< orphan*/ * f_fstypename; int /*<<< orphan*/  f_mntfromname; int /*<<< orphan*/  f_mntonname; int /*<<< orphan*/  f_iosize; } ;
struct TYPE_3__ {int va_mode; int va_nlink; int va_fileid; int va_gen; int va_size; int /*<<< orphan*/  va_blocksize; scalar_t__ va_gid; scalar_t__ va_uid; int /*<<< orphan*/  va_type; } ;
struct nfsvattr {TYPE_1__ na_vattr; } ;
struct nfsstatfs {int dummy; } ;
struct nfsnode {int dummy; } ;
struct nfsmount {int nm_flag; int /*<<< orphan*/  nm_mtx; int /*<<< orphan*/  nm_fhsize; int /*<<< orphan*/  nm_fh; } ;
struct nfsfsinfo {int dummy; } ;
struct mount {TYPE_2__* mnt_vfc; struct statfs mnt_stat; } ;
typedef  scalar_t__ gid_t ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_4__ {int /*<<< orphan*/  vfc_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  LK_EXCLUSIVE ; 
 int /*<<< orphan*/  MBF_NOWAIT ; 
 int /*<<< orphan*/  MFSNAMELEN ; 
 int /*<<< orphan*/  MNAMELEN ; 
 int /*<<< orphan*/  NFSBZERO (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NFSCL_DEBUG (int,char*,int) ; 
 int /*<<< orphan*/  NFSHASGOTFSINFO (struct nfsmount*) ; 
 scalar_t__ NFSHASNFSV3 (struct nfsmount*) ; 
 int NFSMNT_NFSV4 ; 
 struct vnode* NFSTOV (struct nfsnode*) ; 
 int /*<<< orphan*/  NFS_FABLKSIZE ; 
 scalar_t__ NFS_ISV4 (struct vnode*) ; 
 int /*<<< orphan*/  VDIR ; 
 struct nfsmount* VFSTONFS (struct mount*) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int ncl_nget (struct mount*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nfsnode**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  newnfs_iosize (struct nfsmount*) ; 
 int /*<<< orphan*/  nfscl_loadattrcache (struct vnode**,struct nfsvattr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfscl_loadfsinfo (struct nfsmount*,struct nfsfsinfo*) ; 
 int /*<<< orphan*/  nfscl_loadsbinfo (struct nfsmount*,struct nfsstatfs*,struct statfs*) ; 
 int nfscl_maperr (struct thread*,int,scalar_t__,scalar_t__) ; 
 int nfsrpc_fsinfo (struct vnode*,struct nfsfsinfo*,int /*<<< orphan*/ ,struct thread*,struct nfsvattr*,int*,int /*<<< orphan*/ *) ; 
 int nfsrpc_getattrnovp (struct nfsmount*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct thread*,struct nfsvattr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int nfsrpc_statfs (struct vnode*,struct nfsstatfs*,struct nfsfsinfo*,int /*<<< orphan*/ ,struct thread*,struct nfsvattr*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vfs_busy (struct mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_unbusy (struct mount*) ; 
 int /*<<< orphan*/  vput (struct vnode*) ; 

__attribute__((used)) static int
nfs_statfs(struct mount *mp, struct statfs *sbp)
{
	struct vnode *vp;
	struct thread *td;
	struct nfsmount *nmp = VFSTONFS(mp);
	struct nfsvattr nfsva;
	struct nfsfsinfo fs;
	struct nfsstatfs sb;
	int error = 0, attrflag, gotfsinfo = 0, ret;
	struct nfsnode *np;

	td = curthread;

	error = vfs_busy(mp, MBF_NOWAIT);
	if (error)
		return (error);
	error = ncl_nget(mp, nmp->nm_fh, nmp->nm_fhsize, &np, LK_EXCLUSIVE);
	if (error) {
		vfs_unbusy(mp);
		return (error);
	}
	vp = NFSTOV(np);
	mtx_lock(&nmp->nm_mtx);
	if (NFSHASNFSV3(nmp) && !NFSHASGOTFSINFO(nmp)) {
		mtx_unlock(&nmp->nm_mtx);
		error = nfsrpc_fsinfo(vp, &fs, td->td_ucred, td, &nfsva,
		    &attrflag, NULL);
		if (!error)
			gotfsinfo = 1;
	} else
		mtx_unlock(&nmp->nm_mtx);
	if (!error)
		error = nfsrpc_statfs(vp, &sb, &fs, td->td_ucred, td, &nfsva,
		    &attrflag, NULL);
	if (error != 0)
		NFSCL_DEBUG(2, "statfs=%d\n", error);
	if (attrflag == 0) {
		ret = nfsrpc_getattrnovp(nmp, nmp->nm_fh, nmp->nm_fhsize, 1,
		    td->td_ucred, td, &nfsva, NULL, NULL);
		if (ret) {
			/*
			 * Just set default values to get things going.
			 */
			NFSBZERO((caddr_t)&nfsva, sizeof (struct nfsvattr));
			nfsva.na_vattr.va_type = VDIR;
			nfsva.na_vattr.va_mode = 0777;
			nfsva.na_vattr.va_nlink = 100;
			nfsva.na_vattr.va_uid = (uid_t)0;
			nfsva.na_vattr.va_gid = (gid_t)0;
			nfsva.na_vattr.va_fileid = 2;
			nfsva.na_vattr.va_gen = 1;
			nfsva.na_vattr.va_blocksize = NFS_FABLKSIZE;
			nfsva.na_vattr.va_size = 512 * 1024;
		}
	}
	(void) nfscl_loadattrcache(&vp, &nfsva, NULL, NULL, 0, 1);
	if (!error) {
	    mtx_lock(&nmp->nm_mtx);
	    if (gotfsinfo || (nmp->nm_flag & NFSMNT_NFSV4))
		nfscl_loadfsinfo(nmp, &fs);
	    nfscl_loadsbinfo(nmp, &sb, sbp);
	    sbp->f_iosize = newnfs_iosize(nmp);
	    mtx_unlock(&nmp->nm_mtx);
	    if (sbp != &mp->mnt_stat) {
		bcopy(mp->mnt_stat.f_mntonname, sbp->f_mntonname, MNAMELEN);
		bcopy(mp->mnt_stat.f_mntfromname, sbp->f_mntfromname, MNAMELEN);
	    }
	    strncpy(&sbp->f_fstypename[0], mp->mnt_vfc->vfc_name, MFSNAMELEN);
	} else if (NFS_ISV4(vp)) {
		error = nfscl_maperr(td, error, (uid_t)0, (gid_t)0);
	}
	vput(vp);
	vfs_unbusy(mp);
	return (error);
}