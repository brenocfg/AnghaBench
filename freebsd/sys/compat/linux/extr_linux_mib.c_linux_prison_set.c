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
struct linux_prison {int pr_oss_version; int /*<<< orphan*/  pr_osname; int /*<<< orphan*/  pr_osrelease; int /*<<< orphan*/  pr_osrel; } ;
typedef  int /*<<< orphan*/  oss_version ;
typedef  int /*<<< orphan*/  jsys ;

/* Variables and functions */
 int ENOENT ; 
#define  JAIL_SYS_INHERIT 129 
#define  JAIL_SYS_NEW 128 
 int /*<<< orphan*/  LINUX_MAX_UTSNAME ; 
 int /*<<< orphan*/  linux_alloc_prison (struct prison*,struct linux_prison**) ; 
 int /*<<< orphan*/  linux_map_osrel (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  linux_osd_jail_slot ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  osd_jail_del (struct prison*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int vfs_copyopt (struct vfsoptlist*,char*,int*,int) ; 
 int vfs_getopt (struct vfsoptlist*,char*,void**,int*) ; 

__attribute__((used)) static int
linux_prison_set(void *obj, void *data)
{
	struct linux_prison *lpr;
	struct prison *pr = obj;
	struct vfsoptlist *opts = data;
	char *osname, *osrelease;
	int error, gotversion, jsys, len, oss_version;

	/* Set the parameters, which should be correct. */
	error = vfs_copyopt(opts, "linux", &jsys, sizeof(jsys));
	if (error == ENOENT)
		jsys = -1;
	error = vfs_getopt(opts, "linux.osname", (void **)&osname, &len);
	if (error == ENOENT)
		osname = NULL;
	else
		jsys = JAIL_SYS_NEW;
	error = vfs_getopt(opts, "linux.osrelease", (void **)&osrelease, &len);
	if (error == ENOENT)
		osrelease = NULL;
	else
		jsys = JAIL_SYS_NEW;
	error = vfs_copyopt(opts, "linux.oss_version", &oss_version,
	    sizeof(oss_version));
	if (error == ENOENT)
		gotversion = 0;
	else {
		gotversion = 1;
		jsys = JAIL_SYS_NEW;
	}
	switch (jsys) {
	case JAIL_SYS_INHERIT:
		/* "linux=inherit": inherit the parent's Linux info. */
		mtx_lock(&pr->pr_mtx);
		osd_jail_del(pr, linux_osd_jail_slot);
		mtx_unlock(&pr->pr_mtx);
		break;
	case JAIL_SYS_NEW:
		/*
		 * "linux=new" or "linux.*":
		 * the prison gets its own Linux info.
		 */
		linux_alloc_prison(pr, &lpr);
		if (osrelease) {
			(void)linux_map_osrel(osrelease, &lpr->pr_osrel);
			strlcpy(lpr->pr_osrelease, osrelease,
			    LINUX_MAX_UTSNAME);
		}
		if (osname)
			strlcpy(lpr->pr_osname, osname, LINUX_MAX_UTSNAME);
		if (gotversion)
			lpr->pr_oss_version = oss_version;
		mtx_unlock(&pr->pr_mtx);
	}

	return (0);
}