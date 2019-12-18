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
typedef  int u_long ;
struct thread {int /*<<< orphan*/  td_ucred; } ;
struct mount {int dummy; } ;
struct cdev {int dummy; } ;
typedef  int /*<<< orphan*/  fsid_t ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int ENOENT ; 
 int ENXIO ; 
 int EPERM ; 
#define  UFSRESUME 129 
#define  UFSSUSPEND 128 
 int /*<<< orphan*/  devfs_clear_cdevpriv () ; 
 int devfs_get_cdevpriv (void**) ; 
 int devfs_set_cdevpriv (struct mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ffs_susp_dtor ; 
 int /*<<< orphan*/  ffs_susp_lock ; 
 int ffs_susp_suspend (struct mount*) ; 
 int /*<<< orphan*/  ffs_susp_unsuspend (struct mount*) ; 
 scalar_t__ jailed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 
 int vfs_busy (struct mount*,int /*<<< orphan*/ ) ; 
 struct mount* vfs_getvfs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfs_rel (struct mount*) ; 
 int /*<<< orphan*/  vfs_unbusy (struct mount*) ; 

__attribute__((used)) static int
ffs_susp_ioctl(struct cdev *dev, u_long cmd, caddr_t addr, int flags,
    struct thread *td)
{
	struct mount *mp;
	fsid_t *fsidp;
	int error;

	/*
	 * No suspend inside the jail.  Allowing it would require making
	 * sure that e.g. the devfs ruleset for that jail permits access
	 * to the devvp.
	 */
	if (jailed(td->td_ucred))
		return (EPERM);

	sx_xlock(&ffs_susp_lock);

	switch (cmd) {
	case UFSSUSPEND:
		fsidp = (fsid_t *)addr;
		mp = vfs_getvfs(fsidp);
		if (mp == NULL) {
			error = ENOENT;
			break;
		}
		error = vfs_busy(mp, 0);
		vfs_rel(mp);
		if (error != 0)
			break;
		error = ffs_susp_suspend(mp);
		if (error != 0) {
			vfs_unbusy(mp);
			break;
		}
		error = devfs_set_cdevpriv(mp, ffs_susp_dtor);
		if (error != 0)
			ffs_susp_unsuspend(mp);
		break;
	case UFSRESUME:
		error = devfs_get_cdevpriv((void **)&mp);
		if (error != 0)
			break;
		/*
		 * This calls ffs_susp_dtor, which in turn unsuspends the fs.
		 * The dtor expects to be called without lock held, because
		 * sometimes it's called from here, and sometimes due to the
		 * file being closed or process exiting.
		 */
		sx_xunlock(&ffs_susp_lock);
		devfs_clear_cdevpriv();
		return (0);
	default:
		error = ENXIO;
		break;
	}

	sx_xunlock(&ffs_susp_lock);

	return (error);
}