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
struct statfs {int f_flags; int /*<<< orphan*/  f_fstypename; int /*<<< orphan*/  f_mntonname; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  MNT_NOWAIT ; 
 int MNT_RDONLY ; 
 int /*<<< orphan*/  VSS_LOG (int /*<<< orphan*/ ,char*) ; 
 char* dev ; 
 int getmntinfo (struct statfs**,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
check(void)
{
	struct statfs *mntbuf, *statfsp;
	int mntsize;
	int i;

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
			return (EPERM); /* only UFS can be freezed */
		}
	}

	return (0);
}