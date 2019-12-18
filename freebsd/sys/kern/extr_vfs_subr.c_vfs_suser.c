#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct thread {TYPE_2__* td_ucred; } ;
struct mount {TYPE_3__* mnt_cred; TYPE_1__* mnt_vfc; } ;
struct TYPE_8__ {scalar_t__ cr_uid; } ;
struct TYPE_7__ {scalar_t__ cr_uid; } ;
struct TYPE_6__ {int vfc_flags; int /*<<< orphan*/  vfc_prison_flag; } ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  PRIV_VFS_MOUNT_OWNER ; 
 int VFCF_DELEGADMIN ; 
 scalar_t__ jailed (TYPE_2__*) ; 
 int /*<<< orphan*/  prison_allow (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ prison_check (TYPE_2__*,TYPE_3__*) ; 
 int priv_check (struct thread*,int /*<<< orphan*/ ) ; 

int
vfs_suser(struct mount *mp, struct thread *td)
{
	int error;

	if (jailed(td->td_ucred)) {
		/*
		 * If the jail of the calling thread lacks permission for
		 * this type of file system, deny immediately.
		 */
		if (!prison_allow(td->td_ucred, mp->mnt_vfc->vfc_prison_flag))
			return (EPERM);

		/*
		 * If the file system was mounted outside the jail of the
		 * calling thread, deny immediately.
		 */
		if (prison_check(td->td_ucred, mp->mnt_cred) != 0)
			return (EPERM);
	}

	/*
	 * If file system supports delegated administration, we don't check
	 * for the PRIV_VFS_MOUNT_OWNER privilege - it will be better verified
	 * by the file system itself.
	 * If this is not the user that did original mount, we check for
	 * the PRIV_VFS_MOUNT_OWNER privilege.
	 */
	if (!(mp->mnt_vfc->vfc_flags & VFCF_DELEGADMIN) &&
	    mp->mnt_cred->cr_uid != td->td_ucred->cr_uid) {
		if ((error = priv_check(td, PRIV_VFS_MOUNT_OWNER)) != 0)
			return (error);
	}
	return (0);
}