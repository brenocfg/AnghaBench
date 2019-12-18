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
struct statfs {char const* f_mntfromname; int /*<<< orphan*/  f_mntonname; } ;
struct fstab {char const* fs_spec; } ;

/* Variables and functions */
 int /*<<< orphan*/  MNT_NOWAIT ; 
 struct fstab* getfsfile (char const*) ; 
 int getmntinfo (struct statfs**,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static const char *
mountpoint_to_dev(const char *mountpoint)
{
	struct statfs *mntbuf, *statfsp;
	struct fstab *fs;
	int i, mntsize;

	/*
	 * First check the mounted filesystems.
	 */
	mntsize = getmntinfo(&mntbuf, MNT_NOWAIT);
	for (i = 0; i < mntsize; i++) {
		statfsp = &mntbuf[i];

		if (strcmp(statfsp->f_mntonname, mountpoint) == 0)
			return (statfsp->f_mntfromname);
	}

	/*
	 * Check the fstab.
	 */
	fs = getfsfile(mountpoint);
	if (fs != NULL)
		return (fs->fs_spec);

	return (NULL);
}