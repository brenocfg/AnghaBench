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
typedef  struct statfs {char* f_mntfromname; } const statfs ;
struct stat {scalar_t__ st_rdev; int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 int MAXPATHLEN ; 
 int /*<<< orphan*/  MNT_NOWAIT ; 
 int /*<<< orphan*/  S_ISBLK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISCHR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _PATH_DEV ; 
 int getmntinfo (struct statfs const**,int /*<<< orphan*/ ) ; 
 scalar_t__ stat (char const*,struct stat*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct statfs *
dev_to_statfs(const char *dev)
{
	struct stat devstat, mntdevstat;
	struct statfs *mntbuf, *statfsp;
	char device[MAXPATHLEN];
	char *mntdevname;
	int i, mntsize;

	/*
	 * First check the mounted filesystems.
	 */
	if (stat(dev, &devstat) != 0)
		return (NULL);
	if (!S_ISCHR(devstat.st_mode) && !S_ISBLK(devstat.st_mode))
		return (NULL);

	mntsize = getmntinfo(&mntbuf, MNT_NOWAIT);
	for (i = 0; i < mntsize; i++) {
		statfsp = &mntbuf[i];
		mntdevname = statfsp->f_mntfromname;
		if (*mntdevname != '/') {
			strcpy(device, _PATH_DEV);
			strcat(device, mntdevname);
			mntdevname = device;
		}
		if (stat(mntdevname, &mntdevstat) == 0 &&
		    mntdevstat.st_rdev == devstat.st_rdev)
			return (statfsp);
	}

	return (NULL);
}