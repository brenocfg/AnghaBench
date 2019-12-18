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
struct statfs {int /*<<< orphan*/  f_fsid; int /*<<< orphan*/  f_mntonname; int /*<<< orphan*/  f_mntfromname; } ;
typedef  int /*<<< orphan*/  fsid_t ;
typedef  int dowhat ;

/* Variables and functions */
#define  CHECKUNIQUE 129 
#define  REMOVE 128 
 scalar_t__ bcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int* calloc (size_t,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 size_t mntinfo (struct statfs**) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

struct statfs *
getmntentry(const char *fromname, const char *onname, fsid_t *fsid, dowhat what)
{
	static struct statfs *mntbuf;
	static size_t mntsize = 0;
	static int *mntcheck = NULL;
	struct statfs *sfs, *foundsfs;
	int i, count;

	if (mntsize <= 0) {
		if ((mntsize = mntinfo(&mntbuf)) <= 0)
			return (NULL);
	}
	if (mntcheck == NULL) {
		if ((mntcheck = calloc(mntsize + 1, sizeof(int))) == NULL)
			err(1, "calloc");
	}
	/*
	 * We want to get the file systems in the reverse order
	 * that they were mounted. Unmounted file systems are marked
	 * in a table called 'mntcheck'.
	 */
	count = 0;
	foundsfs = NULL;
	for (i = mntsize - 1; i >= 0; i--) {
		if (mntcheck[i])
			continue;
		sfs = &mntbuf[i];
		if (fromname != NULL && strcmp(sfs->f_mntfromname,
		    fromname) != 0)
			continue;
		if (onname != NULL && strcmp(sfs->f_mntonname, onname) != 0)
			continue;
		if (fsid != NULL && bcmp(&sfs->f_fsid, fsid,
		    sizeof(*fsid)) != 0)
			continue;

		switch (what) {
		case CHECKUNIQUE:
			foundsfs = sfs;
			count++;
			continue;
		case REMOVE:
			mntcheck[i] = 1;
			break;
		default:
			break;
		}
		return (sfs);
	}

	if (what == CHECKUNIQUE && count == 1)
		return (foundsfs);
	return (NULL);
}