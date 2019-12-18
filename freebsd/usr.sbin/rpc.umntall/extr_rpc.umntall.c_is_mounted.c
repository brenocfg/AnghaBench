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
struct statfs {int /*<<< orphan*/  f_mntfromname; } ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int MNAMELEN ; 
 int /*<<< orphan*/  MNT_NOWAIT ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  free (struct statfs*) ; 
 int getfsstat (struct statfs*,long,int /*<<< orphan*/ ) ; 
 struct statfs* malloc (size_t) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int strlen (char*) ; 

int
is_mounted(char *hostname, char *dirp) {
	struct statfs *mntbuf;
	char name[MNAMELEN + 1];
	size_t bufsize;
	int mntsize, i;

	if (strlen(hostname) + strlen(dirp) >= MNAMELEN)
		return (0);
	snprintf(name, sizeof(name), "%s:%s", hostname, dirp);
	mntsize = getfsstat(NULL, 0, MNT_NOWAIT);
	if (mntsize <= 0)
		return (0);
	bufsize = (mntsize + 1) * sizeof(struct statfs);
	if ((mntbuf = malloc(bufsize)) == NULL)
		err(1, "malloc");
	mntsize = getfsstat(mntbuf, (long)bufsize, MNT_NOWAIT);
	for (i = mntsize - 1; i >= 0; i--) {
		if (strcmp(mntbuf[i].f_mntfromname, name) == 0) {
			free(mntbuf);
			return (1);
		}
	}
	free(mntbuf);
	return (0);
}