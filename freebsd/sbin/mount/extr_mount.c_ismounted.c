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
struct statfs {int /*<<< orphan*/  f_mntfromname; int /*<<< orphan*/  f_fstypename; int /*<<< orphan*/  f_mntonname; } ;
struct fstab {char* fs_file; char* fs_vfstype; char* fs_spec; } ;
typedef  int /*<<< orphan*/  realfsfile ;

/* Variables and functions */
 int PATH_MAX ; 
 int /*<<< orphan*/  isremountable (char*) ; 
 int /*<<< orphan*/ * realpath (char*,char*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 

int
ismounted(struct fstab *fs, struct statfs *mntbuf, int mntsize)
{
	char realfsfile[PATH_MAX];
	int i;

	if (fs->fs_file[0] == '/' && fs->fs_file[1] == '\0')
		/* the root file system can always be remounted */
		return (0);

	/* The user may have specified a symlink in fstab, resolve the path */
	if (realpath(fs->fs_file, realfsfile) == NULL) {
		/* Cannot resolve the path, use original one */
		strlcpy(realfsfile, fs->fs_file, sizeof(realfsfile));
	}

	/* 
	 * Consider the filesystem to be mounted if:
	 * It has the same mountpoint as a mounted filesytem, and
	 * It has the same type as that same mounted filesystem, and
	 * It has the same device name as that same mounted filesystem, OR
	 *     It is a nonremountable filesystem
	 */
	for (i = mntsize - 1; i >= 0; --i)
		if (strcmp(realfsfile, mntbuf[i].f_mntonname) == 0 &&
		    strcmp(fs->fs_vfstype, mntbuf[i].f_fstypename) == 0 && 
		    (!isremountable(fs->fs_vfstype) ||
		     (strcmp(fs->fs_spec, mntbuf[i].f_mntfromname) == 0)))
			return (1);
	return (0);
}