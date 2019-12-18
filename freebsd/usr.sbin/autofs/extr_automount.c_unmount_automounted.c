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
struct statfs {int f_flags; int /*<<< orphan*/  f_mntonname; int /*<<< orphan*/  f_fstypename; } ;

/* Variables and functions */
 int MNT_AUTOMOUNTED ; 
 int /*<<< orphan*/  MNT_WAIT ; 
 int getmntinfo (struct statfs**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_debugx (char*,...) ; 
 int /*<<< orphan*/  log_err (int,char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  unmount_by_statfs (struct statfs*,int) ; 

__attribute__((used)) static void
unmount_automounted(bool force)
{
	struct statfs *mntbuf;
	int i, nitems;

	nitems = getmntinfo(&mntbuf, MNT_WAIT);
	if (nitems <= 0)
		log_err(1, "getmntinfo");

	log_debugx("unmounting automounted filesystems");

	for (i = 0; i < nitems; i++) {
		if (strcmp(mntbuf[i].f_fstypename, "autofs") == 0) {
			log_debugx("skipping %s, filesystem type is autofs",
			    mntbuf[i].f_mntonname);
			continue;
		}

		if ((mntbuf[i].f_flags & MNT_AUTOMOUNTED) == 0) {
			log_debugx("skipping %s, not automounted",
			    mntbuf[i].f_mntonname);
			continue;
		}

		unmount_by_statfs(&(mntbuf[i]), force);
	}
}