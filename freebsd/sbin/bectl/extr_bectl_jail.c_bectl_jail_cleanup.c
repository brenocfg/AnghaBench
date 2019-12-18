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
struct statfs {char* f_mntonname; scalar_t__ f_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAXPATHLEN ; 
 scalar_t__ MNTTYPE_ZFS ; 
 int /*<<< orphan*/  MNT_NOWAIT ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 size_t getmntinfo (struct statfs**,int /*<<< orphan*/ ) ; 
 scalar_t__ jail_remove (int) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strncmp (char*,char*,size_t) ; 
 size_t strnlen (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ unmount (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bectl_jail_cleanup(char *mountpoint, int jid)
{
	struct statfs *mntbuf;
	size_t i, searchlen, mntsize;

	if (jid >= 0 && jail_remove(jid) != 0) {
		fprintf(stderr, "unable to remove jail");
		return (1);
	}

	searchlen = strnlen(mountpoint, MAXPATHLEN);
	mntsize = getmntinfo(&mntbuf, MNT_NOWAIT);
	for (i = 0; i < mntsize; i++) {
		if (strncmp(mountpoint, mntbuf[i].f_mntonname, searchlen) == 0 &&
		    mntbuf[i].f_type != MNTTYPE_ZFS) {

			if (unmount(mntbuf[i].f_mntonname, 0) != 0) {
				fprintf(stderr, "bectl jail: unable to unmount filesystem %s",
				    mntbuf[i].f_mntonname);
				return (1);
			}
		}
	}

	return (0);
}