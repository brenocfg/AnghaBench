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
struct statfs {int f_flags; char* f_mntonname; int /*<<< orphan*/  f_mntfromname; } ;

/* Variables and functions */
 int /*<<< orphan*/  MNT_NOWAIT ; 
 long getmntinfo (struct statfs**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static char *
getmntpt(char *name, int *mntflagsp)
{
	long mntsize, i;
	struct statfs *mntbuf;

	mntsize = getmntinfo(&mntbuf, MNT_NOWAIT);
	for (i = 0; i < mntsize; i++) {
		if (!strcmp(mntbuf[i].f_mntfromname, name)) {
			*mntflagsp = mntbuf[i].f_flags;
			return (mntbuf[i].f_mntonname);
		}
	}
	return (0);
}