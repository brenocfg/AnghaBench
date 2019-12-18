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
struct netexport {int dummy; } ;
struct mount {int mnt_flag; int /*<<< orphan*/  mnt_opt; int /*<<< orphan*/  mnt_optnew; int /*<<< orphan*/  mnt_explock; struct netexport* mnt_export; } ;
struct export_args {scalar_t__ ex_numsecflavors; int ex_flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  LK_EXCLUSIVE ; 
 int /*<<< orphan*/  LK_RELEASE ; 
 scalar_t__ MAXSECFLAVORS ; 
 int MNT_DEFEXPORTED ; 
 int MNT_DELEXPORT ; 
 int MNT_EXPORTED ; 
 int MNT_EXPUBLIC ; 
 int /*<<< orphan*/  MNT_ILOCK (struct mount*) ; 
 int /*<<< orphan*/  MNT_IUNLOCK (struct mount*) ; 
 int /*<<< orphan*/  M_MOUNT ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  free (struct netexport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockmgr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct netexport* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vfs_deleteopt (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  vfs_free_addrlist (struct netexport*) ; 
 int vfs_hang_addrlist (struct mount*,struct netexport*,struct export_args*) ; 
 int vfs_setpublicfs (struct mount*,struct netexport*,struct export_args*) ; 

int
vfs_export(struct mount *mp, struct export_args *argp)
{
	struct netexport *nep;
	int error;

	if (argp->ex_numsecflavors < 0
	    || argp->ex_numsecflavors >= MAXSECFLAVORS)
		return (EINVAL);

	error = 0;
	lockmgr(&mp->mnt_explock, LK_EXCLUSIVE, NULL);
	nep = mp->mnt_export;
	if (argp->ex_flags & MNT_DELEXPORT) {
		if (nep == NULL) {
			error = ENOENT;
			goto out;
		}
		if (mp->mnt_flag & MNT_EXPUBLIC) {
			vfs_setpublicfs(NULL, NULL, NULL);
			MNT_ILOCK(mp);
			mp->mnt_flag &= ~MNT_EXPUBLIC;
			MNT_IUNLOCK(mp);
		}
		vfs_free_addrlist(nep);
		mp->mnt_export = NULL;
		free(nep, M_MOUNT);
		nep = NULL;
		MNT_ILOCK(mp);
		mp->mnt_flag &= ~(MNT_EXPORTED | MNT_DEFEXPORTED);
		MNT_IUNLOCK(mp);
	}
	if (argp->ex_flags & MNT_EXPORTED) {
		if (nep == NULL) {
			nep = malloc(sizeof(struct netexport), M_MOUNT, M_WAITOK | M_ZERO);
			mp->mnt_export = nep;
		}
		if (argp->ex_flags & MNT_EXPUBLIC) {
			if ((error = vfs_setpublicfs(mp, nep, argp)) != 0)
				goto out;
			MNT_ILOCK(mp);
			mp->mnt_flag |= MNT_EXPUBLIC;
			MNT_IUNLOCK(mp);
		}
		if ((error = vfs_hang_addrlist(mp, nep, argp)))
			goto out;
		MNT_ILOCK(mp);
		mp->mnt_flag |= MNT_EXPORTED;
		MNT_IUNLOCK(mp);
	}

out:
	lockmgr(&mp->mnt_explock, LK_RELEASE, NULL);
	/*
	 * Once we have executed the vfs_export() command, we do
	 * not want to keep the "export" option around in the
	 * options list, since that will cause subsequent MNT_UPDATE
	 * calls to fail.  The export information is saved in
	 * mp->mnt_export, so we can safely delete the "export" mount option
	 * here.
	 */
	vfs_deleteopt(mp->mnt_optnew, "export");
	vfs_deleteopt(mp->mnt_opt, "export");
	return (error);
}