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
struct statfs {int f_mntonname; int f_flags; int f_fstypename; int /*<<< orphan*/  f_fsid; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  MNT_NOWAIT ; 
 int MNT_RDONLY ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  UFSSUSPEND ; 
 int /*<<< orphan*/  VSS_LOG (int /*<<< orphan*/ ,char*,...) ; 
 int _PATH_UFSSUSPEND ; 
 char* dev ; 
 int errno ; 
 int g_ufs_suspend_handle ; 
 int getmntinfo (struct statfs**,int /*<<< orphan*/ ) ; 
 int ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int open (int,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (int,char*,int) ; 

__attribute__((used)) static int
freeze(void)
{
	struct statfs *mntbuf, *statfsp;
	int mntsize;
	int error = 0;
	int i;

	g_ufs_suspend_handle = open(_PATH_UFSSUSPEND, O_RDWR);
	if (g_ufs_suspend_handle == -1) {
		VSS_LOG(LOG_ERR, "unable to open %s", _PATH_UFSSUSPEND);
		return (errno);
	}

	mntsize = getmntinfo(&mntbuf, MNT_NOWAIT);
	if (mntsize == 0) {
		VSS_LOG(LOG_ERR, "There is no mount information\n");
		return (EINVAL);
	}
	for (i = mntsize - 1; i >= 0; --i)
	{
		statfsp = &mntbuf[i];

		if (strncmp(statfsp->f_mntonname, dev, strlen(dev)) == 0) {
			continue; /* skip to freeze '/dev' */
		} else if (statfsp->f_flags & MNT_RDONLY) {
			continue; /* skip to freeze RDONLY partition */
		} else if (strncmp(statfsp->f_fstypename, "ufs", 3) != 0) {
			continue; /* only UFS can be freezed */
		}
		error = ioctl(g_ufs_suspend_handle, UFSSUSPEND, &statfsp->f_fsid);
		if (error != 0) {
			VSS_LOG(LOG_ERR, "error: %d\n", errno);
			error = errno;
		} else {
			VSS_LOG(LOG_INFO, "Successfully suspend fs: %s\n",
			    statfsp->f_mntonname);
		}
	}

	return (error);
}