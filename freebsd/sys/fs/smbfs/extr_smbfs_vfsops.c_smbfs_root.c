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
struct vnode {int /*<<< orphan*/  v_vflag; } ;
struct ucred {int dummy; } ;
struct thread {struct ucred* td_ucred; } ;
struct smbnode {int dummy; } ;
struct smbmount {struct smbnode* sm_root; } ;
struct smbfattr {int dummy; } ;
struct smb_cred {int dummy; } ;
struct mount {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_VOP_LOCKED (struct vnode*,char*) ; 
 int LK_EXCLUSIVE ; 
 int LK_RETRY ; 
 struct vnode* SMBTOV (struct smbnode*) ; 
 struct smbmount* VFSTOSMBFS (struct mount*) ; 
 struct smbnode* VTOSMB (struct vnode*) ; 
 int /*<<< orphan*/  VV_ROOT ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  smb_makescred (struct smb_cred*,struct thread*,struct ucred*) ; 
 int /*<<< orphan*/  smbfs_free_scred (struct smb_cred*) ; 
 struct smb_cred* smbfs_malloc_scred () ; 
 int smbfs_nget (struct mount*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct smbfattr*,struct vnode**) ; 
 int smbfs_smb_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct smbfattr*,struct smb_cred*) ; 
 int vget (struct vnode*,int,struct thread*) ; 

__attribute__((used)) static int
smbfs_root(struct mount *mp, int flags, struct vnode **vpp)
{
	struct smbmount *smp = VFSTOSMBFS(mp);
	struct vnode *vp;
	struct smbnode *np;
	struct smbfattr fattr;
	struct thread *td;
	struct ucred *cred;
	struct smb_cred *scred;
	int error;

	td = curthread;
	cred = td->td_ucred;

	if (smp->sm_root) {
		*vpp = SMBTOV(smp->sm_root);
		return vget(*vpp, LK_EXCLUSIVE | LK_RETRY, td);
	}
	scred = smbfs_malloc_scred();
	smb_makescred(scred, td, cred);
	error = smbfs_smb_lookup(NULL, NULL, 0, &fattr, scred);
	if (error)
		goto out;
	error = smbfs_nget(mp, NULL, NULL, 0, &fattr, &vp);
	if (error)
		goto out;
	ASSERT_VOP_LOCKED(vp, "smbfs_root");
	vp->v_vflag |= VV_ROOT;
	np = VTOSMB(vp);
	smp->sm_root = np;
	*vpp = vp;
out:
	smbfs_free_scred(scred);
	return error;
}