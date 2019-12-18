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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  atf_tc_t ;

/* Variables and functions */
 int /*<<< orphan*/  FSTEST_ENTER () ; 
 int /*<<< orphan*/  FSTEST_EXIT () ; 
 char* FSTEST_IMGNAME ; 
 int /*<<< orphan*/  FSTEST_MNTNAME ; 
 int /*<<< orphan*/  MNT_LOG ; 
 int /*<<< orphan*/  MOUNT_FFS ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int /*<<< orphan*/  RL (int) ; 
 int /*<<< orphan*/  RUMP_ETFS_BLK ; 
 int /*<<< orphan*/  __UNCONST (char*) ; 
 int /*<<< orphan*/  atf_tc_expect_pass () ; 
 int /*<<< orphan*/  atf_tc_fail (char*,int) ; 
 int /*<<< orphan*/  atf_tc_fail_errno (char*,...) ; 
 int /*<<< orphan*/  rump_init () ; 
 int /*<<< orphan*/  rump_pub_etfs_register (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rump_pub_vfs_mount_print (int /*<<< orphan*/ ,int) ; 
 int rump_sys_chown (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rump_sys_close (int) ; 
 int rump_sys_fchown (int,int,int) ; 
 int rump_sys_mkdir (int /*<<< orphan*/ ,int) ; 
 int rump_sys_mount (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ufs_args*,int) ; 
 int rump_sys_open (char*,int,int) ; 
 scalar_t__ rump_sys_unmount (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rump_sys_write (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int system (char*) ; 

__attribute__((used)) static void
do_quota(const atf_tc_t *tc, int n, const char *newfs_opts, int log)
{
	int i;
	char buf[1024];
	int res;
	int fd;
	struct ufs_args uargs;
	
	snprintf(buf, sizeof(buf), "newfs -q user -q group -F -s 4000 -n %d "
	    "%s %s", (n + 3),  newfs_opts, FSTEST_IMGNAME);
        if (system(buf) == -1)
                atf_tc_fail_errno("cannot create file system");

	rump_init();
	if (rump_sys_mkdir(FSTEST_MNTNAME, 0777) == -1)
		atf_tc_fail_errno("mount point create");

	rump_pub_etfs_register("/diskdev", FSTEST_IMGNAME, RUMP_ETFS_BLK);

	uargs.fspec = __UNCONST("/diskdev");
	if (rump_sys_mount(MOUNT_FFS, FSTEST_MNTNAME, (log) ? MNT_LOG : 0,
	    &uargs, sizeof(uargs)) == -1)
		atf_tc_fail_errno("mount ffs %s", FSTEST_MNTNAME);

	atf_tc_expect_pass();
	FSTEST_ENTER();
	RL(rump_sys_chown(".", 0, 0));
	for (i = 0 ; i < n; i++) {
		sprintf(buf, "file%d", i);
		RL(fd = rump_sys_open(buf, O_CREAT | O_RDWR, 0755));
		sprintf(buf, "test file no %d", i);
		RL(rump_sys_write(fd, buf, strlen(buf)));
		RL(rump_sys_fchown(fd, i, i+80000));
		rump_sys_close(fd);
	}
	FSTEST_EXIT();
	if (rump_sys_unmount(FSTEST_MNTNAME, 0) != 0) {
		rump_pub_vfs_mount_print(FSTEST_MNTNAME, 1);
		atf_tc_fail_errno("unmount failed");
	}
	snprintf(buf, 1024, "fsck_ffs -fn -F %s",  FSTEST_IMGNAME);
	res = system(buf);
	if (res != 0)
		atf_tc_fail("fsck returned %d", res);
}