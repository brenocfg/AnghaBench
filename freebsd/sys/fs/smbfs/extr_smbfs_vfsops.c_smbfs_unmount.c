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
struct thread {int /*<<< orphan*/  td_ucred; } ;
struct smbmount {scalar_t__ sm_didrele; struct smb_dev* sm_dev; int /*<<< orphan*/  sm_share; } ;
struct smb_dev {int dummy; } ;
struct smb_cred {int dummy; } ;
struct mount {int /*<<< orphan*/  mnt_flag; int /*<<< orphan*/ * mnt_data; } ;

/* Variables and functions */
 int EBUSY ; 
 int FORCECLOSE ; 
 int MNT_FORCE ; 
 int /*<<< orphan*/  MNT_ILOCK (struct mount*) ; 
 int /*<<< orphan*/  MNT_IUNLOCK (struct mount*) ; 
 int /*<<< orphan*/  MNT_LOCAL ; 
 int /*<<< orphan*/  M_SMBFSDATA ; 
 int /*<<< orphan*/  SMBVDEBUG (char*,int) ; 
 int /*<<< orphan*/  SMB_LOCK () ; 
 int /*<<< orphan*/  SMB_UNLOCK () ; 
 struct smbmount* VFSTOSMBFS (struct mount*) ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  free (struct smbmount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  sdp_trydestroy (struct smb_dev*) ; 
 int /*<<< orphan*/  smb_makescred (struct smb_cred*,struct thread*,int /*<<< orphan*/ ) ; 
 int smb_share_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smb_share_put (int /*<<< orphan*/ ,struct smb_cred*) ; 
 int /*<<< orphan*/  smbfs_free_scred (struct smb_cred*) ; 
 struct smb_cred* smbfs_malloc_scred () ; 
 int vflush (struct mount*,int,int,struct thread*) ; 

__attribute__((used)) static int
smbfs_unmount(struct mount *mp, int mntflags)
{
	struct thread *td;
	struct smbmount *smp = VFSTOSMBFS(mp);
	struct smb_cred *scred;
	struct smb_dev *dev;
	int error, flags;

	SMBVDEBUG("smbfs_unmount: flags=%04x\n", mntflags);
	td = curthread;
	flags = 0;
	if (mntflags & MNT_FORCE)
		flags |= FORCECLOSE;
	/*
	 * Keep trying to flush the vnode list for the mount while 
	 * some are still busy and we are making progress towards
	 * making them not busy. This is needed because smbfs vnodes
	 * reference their parent directory but may appear after their
	 * parent in the list; one pass over the vnode list is not
	 * sufficient in this case.
	 */
	do {
		smp->sm_didrele = 0;
		/* There is 1 extra root vnode reference from smbfs_mount(). */
		error = vflush(mp, 1, flags, td);
	} while (error == EBUSY && smp->sm_didrele != 0);
	if (error)
		return error;
	scred = smbfs_malloc_scred();
	smb_makescred(scred, td, td->td_ucred);
	error = smb_share_lock(smp->sm_share);
	if (error)
		goto out;
	smb_share_put(smp->sm_share, scred);
	SMB_LOCK();
	dev = smp->sm_dev;
	if (!dev)
		panic("No private data for mount point");
	sdp_trydestroy(dev);
	mp->mnt_data = NULL;
	SMB_UNLOCK();
	free(smp, M_SMBFSDATA);
	MNT_ILOCK(mp);
	mp->mnt_flag &= ~MNT_LOCAL;
	MNT_IUNLOCK(mp);
out:
	smbfs_free_scred(scred);
	return error;
}