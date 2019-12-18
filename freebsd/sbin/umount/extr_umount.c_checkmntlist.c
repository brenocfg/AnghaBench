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
struct statfs {int dummy; } ;
typedef  int /*<<< orphan*/  fsid_t ;

/* Variables and functions */
 int /*<<< orphan*/  FIND ; 
 struct statfs* getmntentry (char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ parsehexfsid (char*,int /*<<< orphan*/ *) ; 

struct statfs *
checkmntlist(char *mntname)
{
	struct statfs *sfs;
	fsid_t fsid;

	sfs = NULL;
	if (parsehexfsid(mntname, &fsid) == 0)
		sfs = getmntentry(NULL, NULL, &fsid, FIND);
	if (sfs == NULL)
		sfs = getmntentry(NULL, mntname, NULL, FIND);
	if (sfs == NULL)
		sfs = getmntentry(mntname, NULL, NULL, FIND);
	return (sfs);
}