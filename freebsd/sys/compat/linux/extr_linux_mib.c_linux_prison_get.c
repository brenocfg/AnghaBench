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
struct vfsoptlist {int dummy; } ;
struct prison {int /*<<< orphan*/  pr_mtx; } ;
struct linux_prison {char* pr_osname; char* pr_osrelease; int pr_oss_version; } ;
typedef  int /*<<< orphan*/  i ;

/* Variables and functions */
 int ENOENT ; 
 int JAIL_SYS_INHERIT ; 
 int JAIL_SYS_NEW ; 
 struct linux_prison* linux_find_prison (struct prison*,struct prison**) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int vfs_setopt (struct vfsoptlist*,char*,int*,int) ; 
 int vfs_setopts (struct vfsoptlist*,char*,char*) ; 

__attribute__((used)) static int
linux_prison_get(void *obj, void *data)
{
	struct linux_prison *lpr;
	struct prison *ppr;
	struct prison *pr = obj;
	struct vfsoptlist *opts = data;
	int error, i;

	static int version0;

	/* See if this prison is the one with the Linux info. */
	lpr = linux_find_prison(pr, &ppr);
	i = (ppr == pr) ? JAIL_SYS_NEW : JAIL_SYS_INHERIT;
	error = vfs_setopt(opts, "linux", &i, sizeof(i));
	if (error != 0 && error != ENOENT)
		goto done;
	if (i) {
		error = vfs_setopts(opts, "linux.osname", lpr->pr_osname);
		if (error != 0 && error != ENOENT)
			goto done;
		error = vfs_setopts(opts, "linux.osrelease", lpr->pr_osrelease);
		if (error != 0 && error != ENOENT)
			goto done;
		error = vfs_setopt(opts, "linux.oss_version",
		    &lpr->pr_oss_version, sizeof(lpr->pr_oss_version));
		if (error != 0 && error != ENOENT)
			goto done;
	} else {
		/*
		 * If this prison is inheriting its Linux info, report
		 * empty/zero parameters.
		 */
		error = vfs_setopts(opts, "linux.osname", "");
		if (error != 0 && error != ENOENT)
			goto done;
		error = vfs_setopts(opts, "linux.osrelease", "");
		if (error != 0 && error != ENOENT)
			goto done;
		error = vfs_setopt(opts, "linux.oss_version", &version0,
		    sizeof(lpr->pr_oss_version));
		if (error != 0 && error != ENOENT)
			goto done;
	}
	error = 0;

 done:
	mtx_unlock(&ppr->pr_mtx);

	return (error);
}