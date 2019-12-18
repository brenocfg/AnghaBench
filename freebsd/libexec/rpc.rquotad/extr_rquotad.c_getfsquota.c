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
struct quotafile {int dummy; } ;
struct fstab {char* fs_file; char* fs_mntops; char* fs_vfstype; } ;
struct dqblk {int dummy; } ;

/* Variables and functions */
 int GRPQUOTA ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int USRQUOTA ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  quota_close (struct quotafile*) ; 
 struct quotafile* quota_open (struct fstab*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ quota_read (struct quotafile*,struct dqblk*,long) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static int
getfsquota(int type, long id, char *path, struct dqblk *dqblk)
{
	struct quotafile *qf;
	/*
	 * Remote quota checking is limited to mounted filesystems.
	 * Since UFS and ZFS support the quota system calls, we
	 * only need to make an fstab object that has the path, and
	 * a blank name for the filesystem type.
	 * This allows the quota_open() call to work the way we
	 * expect it to.
	 *
	 * The static char declaration is because compiler warnings
	 * don't allow passing a const char * to a char *.
	 */
	int rv;
	static char blank[] = "";
	struct fstab fst;

	fst.fs_file = path;
	fst.fs_mntops = blank;
	fst.fs_vfstype = blank;
	
	if (type != USRQUOTA && type != GRPQUOTA)
		return (0);
	
	qf = quota_open(&fst, type, O_RDONLY);
	if (debug)
		warnx("quota_open(<%s, %s>, %d) returned %p",
		      fst.fs_file, fst.fs_mntops, type,
		      qf);
	if (qf == NULL)
		return (0);

	rv = quota_read(qf, dqblk, id) == 0;
	quota_close(qf);
	if (debug)
		warnx("getfsquota(%d, %ld, %s, %p) -> %d",
		      type, id, path, dqblk, rv);
	return (rv);
}