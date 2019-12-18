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
struct TYPE_2__ {scalar_t__* val; } ;
struct statfs {TYPE_1__ f_fsid; } ;
struct mount {int dummy; } ;

/* Variables and functions */
 int EBADF ; 
 int /*<<< orphan*/  PRIV_VFS_GENERATION ; 
 int VFS_STATFS (struct mount*,struct statfs*) ; 
 int mac_mount_check_stat (int /*<<< orphan*/ ,struct mount*) ; 
 int /*<<< orphan*/  prison_enforce_statfs (int /*<<< orphan*/ ,struct mount*,struct statfs*) ; 
 scalar_t__ priv_check (struct thread*,int /*<<< orphan*/ ) ; 
 int vfs_busy (struct mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_rel (struct mount*) ; 
 int /*<<< orphan*/  vfs_unbusy (struct mount*) ; 

__attribute__((used)) static int
kern_do_statfs(struct thread *td, struct mount *mp, struct statfs *buf)
{
	int error;

	if (mp == NULL)
		return (EBADF);
	error = vfs_busy(mp, 0);
	vfs_rel(mp);
	if (error != 0)
		return (error);
#ifdef MAC
	error = mac_mount_check_stat(td->td_ucred, mp);
	if (error != 0)
		goto out;
#endif
	error = VFS_STATFS(mp, buf);
	if (error != 0)
		goto out;
	if (priv_check(td, PRIV_VFS_GENERATION)) {
		buf->f_fsid.val[0] = buf->f_fsid.val[1] = 0;
		prison_enforce_statfs(td->td_ucred, mp, buf);
	}
out:
	vfs_unbusy(mp);
	return (error);
}