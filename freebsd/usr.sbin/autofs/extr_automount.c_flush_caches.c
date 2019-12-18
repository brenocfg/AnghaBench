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
struct statfs {int /*<<< orphan*/  f_mntonname; int /*<<< orphan*/  f_fstypename; } ;

/* Variables and functions */
 int /*<<< orphan*/  MNT_WAIT ; 
 int /*<<< orphan*/  flush_autofs (int /*<<< orphan*/ ) ; 
 int getmntinfo (struct statfs**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_debugx (char*,...) ; 
 int /*<<< orphan*/  log_err (int,char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
flush_caches(void)
{
	struct statfs *mntbuf;
	int i, nitems;

	nitems = getmntinfo(&mntbuf, MNT_WAIT);
	if (nitems <= 0)
		log_err(1, "getmntinfo");

	log_debugx("flushing autofs caches");

	for (i = 0; i < nitems; i++) {
		if (strcmp(mntbuf[i].f_fstypename, "autofs") != 0) {
			log_debugx("skipping %s, filesystem type is not autofs",
			    mntbuf[i].f_mntonname);
			continue;
		}

		flush_autofs(mntbuf[i].f_mntonname);
	}
}