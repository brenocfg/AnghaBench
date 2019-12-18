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
typedef  int /*<<< orphan*/  uargs ;
struct ufs_args {int /*<<< orphan*/  fspec; } ;

/* Variables and functions */
 int /*<<< orphan*/  FSTEST_MNTNAME ; 
 int MNT_LOG ; 
 int MNT_UPDATE ; 
 int /*<<< orphan*/  MOUNT_FFS ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int O_RDWR ; 
 int /*<<< orphan*/  RUMP_RB_NOSYNC ; 
 int /*<<< orphan*/  __UNCONST (char*) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int rump_sys_fsync (int) ; 
 int rump_sys_mount (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct ufs_args*,int) ; 
 int rump_sys_open (char*,int,int) ; 
 int /*<<< orphan*/  rump_sys_reboot (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int rump_sys_unlink (char*) ; 
 int /*<<< orphan*/  rump_sys_write (int,char*,unsigned int) ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 
 unsigned int strlen (char const*) ; 

__attribute__((used)) static int
quota_test5(const char *testopts)
{
	static char buf[512];
	int fd;
	int remount = 0;
	int unlnk = 0;
	int log = 0;
	unsigned int i;

	for (i =0; testopts && i < strlen(testopts); i++) {
		switch(testopts[i]) {
		case 'L':
			log++;
			break;
		case 'R':
			remount++;
			break;
		case 'U':
			unlnk++;
			break;
		default:
			errx(1, "test4: unknown option %c", testopts[i]);
		}
	}
	if (remount) {
		struct ufs_args uargs;
		uargs.fspec = __UNCONST("/diskdev");
		/* remount the fs read/write */
		if (rump_sys_mount(MOUNT_FFS, FSTEST_MNTNAME,
		    MNT_UPDATE | (log ? MNT_LOG : 0),
		    &uargs, sizeof(uargs)) == -1)
			err(1, "mount ffs rw %s", FSTEST_MNTNAME);
	}

	if (unlnk) {
		/*
		 * open and unlink a file
		 */

		fd = rump_sys_open("unlinked_file",
		    O_EXCL| O_CREAT | O_RDWR, 0644);
		if (fd < 0)
			err(1, "create %s", "unlinked_file");
		sprintf(buf, "test unlinked_file");
		rump_sys_write(fd, buf, strlen(buf));
		if (rump_sys_unlink("unlinked_file") == -1)
			err(1, "unlink unlinked_file");
		if (rump_sys_fsync(fd) == -1) 
			err(1, "fsync unlinked_file");
		rump_sys_reboot(RUMP_RB_NOSYNC, NULL);
		errx(1, "reboot failed");
		return 1;
	}
	return 0;
}