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
struct vnode {int dummy; } ;
struct thread {int /*<<< orphan*/  td_ucred; } ;
struct smbmount {int sm_caseopt; int sm_uid; int sm_gid; int sm_file_mode; int sm_dir_mode; struct smb_dev* sm_dev; int /*<<< orphan*/  sm_flags; int /*<<< orphan*/ * sm_root; struct smb_share* sm_share; } ;
struct smb_vc {int /*<<< orphan*/  vc_srvname; int /*<<< orphan*/  vc_username; int /*<<< orphan*/  vc_txmax; } ;
struct smb_share {int /*<<< orphan*/  ss_name; } ;
struct smb_dev {int dummy; } ;
struct smb_cred {int dummy; } ;
struct TYPE_2__ {char* f_mntfromname; int /*<<< orphan*/  f_iosize; } ;
struct mount {int mnt_flag; TYPE_1__ mnt_stat; int /*<<< orphan*/  mnt_optnew; struct smbmount* mnt_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  LK_EXCLUSIVE ; 
 int /*<<< orphan*/  MNAMELEN ; 
 int MNT_ROOTFS ; 
 int MNT_UPDATE ; 
 int /*<<< orphan*/  M_SMBFSDATA ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  SMBERROR (char*,struct mount*) ; 
 int /*<<< orphan*/  SMBFS_MOUNT_NO_LONG ; 
 int /*<<< orphan*/  SMBM_EXEC ; 
 int /*<<< orphan*/  SMBVDEBUG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMB_LOCK () ; 
 int /*<<< orphan*/  SMB_UNLOCK () ; 
 struct smb_vc* SSTOVC (struct smb_share*) ; 
 int S_IFDIR ; 
 int S_IFREG ; 
 int S_IRWXG ; 
 int S_IRWXO ; 
 int S_IRWXU ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (char*,int /*<<< orphan*/ ) ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  free (struct smbmount*,int /*<<< orphan*/ ) ; 
 struct smbmount* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int /*<<< orphan*/  sdp_trydestroy (struct smb_dev*) ; 
 int smb_dev2share (int,int /*<<< orphan*/ ,struct smb_cred*,struct smb_share**,struct smb_dev**) ; 
 int /*<<< orphan*/  smb_makescred (struct smb_cred*,struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smb_share_put (struct smb_share*,struct smb_cred*) ; 
 int /*<<< orphan*/  smb_share_unlock (struct smb_share*) ; 
 int /*<<< orphan*/  smbfs_free_scred (struct smb_cred*) ; 
 struct smb_cred* smbfs_malloc_scred () ; 
 int /*<<< orphan*/  smbfs_opts ; 
 int smbfs_root (struct mount*,int /*<<< orphan*/ ,struct vnode**) ; 
 char* strchr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ vfs_filteropt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_flagopt (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_getnewfsid (struct mount*) ; 
 int /*<<< orphan*/  vfs_mount_error (struct mount*,char*,...) ; 
 int vfs_scanopt (int /*<<< orphan*/ ,char*,char*,int*) ; 
 int /*<<< orphan*/  vrefcnt (struct vnode*) ; 

__attribute__((used)) static int
smbfs_mount(struct mount *mp)
{
	struct smbmount *smp = NULL;
	struct smb_vc *vcp;
	struct smb_share *ssp = NULL;
	struct vnode *vp;
	struct thread *td;
	struct smb_dev *dev;
	struct smb_cred *scred;
	int error, v;
	char *pc, *pe;

	dev = NULL;
	td = curthread;
	if (mp->mnt_flag & (MNT_UPDATE | MNT_ROOTFS))
		return EOPNOTSUPP;

	if (vfs_filteropt(mp->mnt_optnew, smbfs_opts)) {
		vfs_mount_error(mp, "%s", "Invalid option");
		return (EINVAL);
	}

	scred = smbfs_malloc_scred();
	smb_makescred(scred, td, td->td_ucred);
	
	/* Ask userspace of `fd`, the file descriptor of this session */
	if (1 != vfs_scanopt(mp->mnt_optnew, "fd", "%d", &v)) {
		vfs_mount_error(mp, "No fd option");
		smbfs_free_scred(scred);
		return (EINVAL);
	}
	error = smb_dev2share(v, SMBM_EXEC, scred, &ssp, &dev);
	smp = malloc(sizeof(*smp), M_SMBFSDATA, M_WAITOK | M_ZERO);
	if (error) {
		printf("invalid device handle %d (%d)\n", v, error);
		vfs_mount_error(mp, "invalid device handle %d %d\n", v, error);
		smbfs_free_scred(scred);
		free(smp, M_SMBFSDATA);
		return error;
	}
	vcp = SSTOVC(ssp);
	smb_share_unlock(ssp);
	mp->mnt_stat.f_iosize = SSTOVC(ssp)->vc_txmax;
	mp->mnt_data = smp;
	smp->sm_share = ssp;
	smp->sm_root = NULL;
	smp->sm_dev = dev;
	if (1 != vfs_scanopt(mp->mnt_optnew,
	    "caseopt", "%d", &smp->sm_caseopt)) {
		vfs_mount_error(mp, "Invalid caseopt");
		error = EINVAL;
		goto bad;
	}
	if (1 != vfs_scanopt(mp->mnt_optnew, "uid", "%d", &v)) {
		vfs_mount_error(mp, "Invalid uid");
		error = EINVAL;
		goto bad;
	}
	smp->sm_uid = v;

	if (1 != vfs_scanopt(mp->mnt_optnew, "gid", "%d", &v)) {
		vfs_mount_error(mp, "Invalid gid");
		error = EINVAL;
		goto bad;
	}
	smp->sm_gid = v;

	if (1 != vfs_scanopt(mp->mnt_optnew, "file_mode", "%d", &v)) {
		vfs_mount_error(mp, "Invalid file_mode");
		error = EINVAL;
		goto bad;
	}
	smp->sm_file_mode = (v & (S_IRWXU|S_IRWXG|S_IRWXO)) | S_IFREG;

	if (1 != vfs_scanopt(mp->mnt_optnew, "dir_mode", "%d", &v)) {
		vfs_mount_error(mp, "Invalid dir_mode");
		error = EINVAL;
		goto bad;
	}
	smp->sm_dir_mode  = (v & (S_IRWXU|S_IRWXG|S_IRWXO)) | S_IFDIR;

	vfs_flagopt(mp->mnt_optnew,
	    "nolong", &smp->sm_flags, SMBFS_MOUNT_NO_LONG);

	pc = mp->mnt_stat.f_mntfromname;
	pe = pc + sizeof(mp->mnt_stat.f_mntfromname);
	bzero(pc, MNAMELEN);
	*pc++ = '/';
	*pc++ = '/';
	pc = strchr(strncpy(pc, vcp->vc_username, pe - pc - 2), 0);
	if (pc < pe-1) {
		*(pc++) = '@';
		pc = strchr(strncpy(pc, vcp->vc_srvname, pe - pc - 2), 0);
		if (pc < pe - 1) {
			*(pc++) = '/';
			strncpy(pc, ssp->ss_name, pe - pc - 2);
		}
	}
	vfs_getnewfsid(mp);
	error = smbfs_root(mp, LK_EXCLUSIVE, &vp);
	if (error) {
		vfs_mount_error(mp, "smbfs_root error: %d", error);
		goto bad;
	}
	VOP_UNLOCK(vp, 0);
	SMBVDEBUG("root.v_usecount = %d\n", vrefcnt(vp));

#ifdef DIAGNOSTIC
	SMBERROR("mp=%p\n", mp);
#endif
	smbfs_free_scred(scred);
	return error;
bad:
	if (ssp)
		smb_share_put(ssp, scred);
	smbfs_free_scred(scred);	
	SMB_LOCK();
	if (error && smp->sm_dev == dev) {
		smp->sm_dev = NULL;
		sdp_trydestroy(dev);
	}
	SMB_UNLOCK();
	free(smp, M_SMBFSDATA);
	return error;
}