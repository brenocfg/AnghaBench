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
struct thread {int /*<<< orphan*/  td_ucred; } ;
struct statfs {int /*<<< orphan*/  f_iosize; } ;
struct smbnode {int dummy; } ;
struct smbmount {struct smb_share* sm_share; struct smbnode* sm_root; } ;
struct smb_share {int dummy; } ;
struct smb_cred {int dummy; } ;
struct mount {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  vc_txmax; } ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_1__* SSTOVC (struct smb_share*) ; 
 struct smbmount* VFSTOSMBFS (struct mount*) ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  smb_makescred (struct smb_cred*,struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smbfs_free_scred (struct smb_cred*) ; 
 struct smb_cred* smbfs_malloc_scred () ; 
 int smbfs_smb_statfs (struct smb_share*,struct statfs*,struct smb_cred*) ; 
 int /*<<< orphan*/  vfs_mount_error (struct mount*,char*) ; 

int
smbfs_statfs(struct mount *mp, struct statfs *sbp)
{
	struct thread *td = curthread;
	struct smbmount *smp = VFSTOSMBFS(mp);
	struct smbnode *np = smp->sm_root;
	struct smb_share *ssp = smp->sm_share;
	struct smb_cred *scred;
	int error;

	if (np == NULL) {
		vfs_mount_error(mp, "np == NULL");
		return EINVAL;
	}
	
	sbp->f_iosize = SSTOVC(ssp)->vc_txmax;		/* optimal transfer block size */
	scred = smbfs_malloc_scred();
	smb_makescred(scred, td, td->td_ucred);
	error = smbfs_smb_statfs(ssp, sbp, scred);
	smbfs_free_scred(scred);
	return (error);
}