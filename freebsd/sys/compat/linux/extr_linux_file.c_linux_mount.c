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
struct thread {int dummy; } ;
struct linux_mount_args {int rwflag; int /*<<< orphan*/  dir; int /*<<< orphan*/  specialfile; int /*<<< orphan*/  filesystemtype; } ;

/* Variables and functions */
 int LINUX_MS_NOEXEC ; 
 int LINUX_MS_NOSUID ; 
 int LINUX_MS_RDONLY ; 
 int LINUX_MS_REMOUNT ; 
 int MFSNAMELEN ; 
 int MNAMELEN ; 
 int MNT_NOEXEC ; 
 int MNT_NOSUID ; 
 int MNT_RDONLY ; 
 int MNT_UPDATE ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int copyinstr (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 int kernel_vmount (int,char*,char*,char*,char*,char*,char*,int /*<<< orphan*/ *) ; 
 char* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

int
linux_mount(struct thread *td, struct linux_mount_args *args)
{
	char fstypename[MFSNAMELEN];
	char *mntonname, *mntfromname;
	int error, fsflags;

	mntonname = malloc(MNAMELEN, M_TEMP, M_WAITOK);
	mntfromname = malloc(MNAMELEN, M_TEMP, M_WAITOK);
	error = copyinstr(args->filesystemtype, fstypename, MFSNAMELEN - 1,
	    NULL);
	if (error != 0)
		goto out;
	error = copyinstr(args->specialfile, mntfromname, MNAMELEN - 1, NULL);
	if (error != 0)
		goto out;
	error = copyinstr(args->dir, mntonname, MNAMELEN - 1, NULL);
	if (error != 0)
		goto out;

	if (strcmp(fstypename, "ext2") == 0) {
		strcpy(fstypename, "ext2fs");
	} else if (strcmp(fstypename, "proc") == 0) {
		strcpy(fstypename, "linprocfs");
	} else if (strcmp(fstypename, "vfat") == 0) {
		strcpy(fstypename, "msdosfs");
	}

	fsflags = 0;

	if ((args->rwflag & 0xffff0000) == 0xc0ed0000) {
		/*
		 * Linux SYNC flag is not included; the closest equivalent
		 * FreeBSD has is !ASYNC, which is our default.
		 */
		if (args->rwflag & LINUX_MS_RDONLY)
			fsflags |= MNT_RDONLY;
		if (args->rwflag & LINUX_MS_NOSUID)
			fsflags |= MNT_NOSUID;
		if (args->rwflag & LINUX_MS_NOEXEC)
			fsflags |= MNT_NOEXEC;
		if (args->rwflag & LINUX_MS_REMOUNT)
			fsflags |= MNT_UPDATE;
	}

	error = kernel_vmount(fsflags,
	    "fstype", fstypename,
	    "fspath", mntonname,
	    "from", mntfromname,
	    NULL);
out:
	free(mntonname, M_TEMP);
	free(mntfromname, M_TEMP);
	return (error);
}