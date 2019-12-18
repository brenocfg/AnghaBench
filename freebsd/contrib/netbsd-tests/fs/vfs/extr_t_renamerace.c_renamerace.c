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
typedef  int /*<<< orphan*/  pthread_t ;
typedef  int /*<<< orphan*/  atf_tc_t ;

/* Variables and functions */
 scalar_t__ FSTYPE_MSDOS (int /*<<< orphan*/  const*) ; 
 scalar_t__ FSTYPE_RUMPFS (int /*<<< orphan*/  const*) ; 
 scalar_t__ FSTYPE_SYSVBFS (int /*<<< orphan*/  const*) ; 
 scalar_t__ FSTYPE_UDF (int /*<<< orphan*/  const*) ; 
 int NWRK ; 
 int /*<<< orphan*/  RL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RUMP_RFCFDG ; 
 int /*<<< orphan*/  RZ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_tc_expect_fail (char*) ; 
 int /*<<< orphan*/  atf_tc_fail (char*) ; 
 int /*<<< orphan*/  atf_tc_fail_errno (char*) ; 
 int /*<<< orphan*/  atf_tc_skip (char*) ; 
 scalar_t__ msdosfs_fstest_unmount (int /*<<< orphan*/  const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int quittingtime ; 
 int /*<<< orphan*/  rump_pub_lwproc_rfork (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rump_pub_vfs_mount_print (char const*,int) ; 
 int /*<<< orphan*/  rump_sys_chdir (char const*) ; 
 int /*<<< orphan*/  rump_sys_getpid () ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  w1 ; 
 int /*<<< orphan*/  w2 ; 
 int /*<<< orphan*/  wrkpid ; 

__attribute__((used)) static void
renamerace(const atf_tc_t *tc, const char *mp)
{
	pthread_t pt1[NWRK], pt2[NWRK];
	int i;

	/*
	 * Sysvbfs supports only 8 inodes so this test would exhaust
	 * the inode table and creating files would fail with ENOSPC.
	 */
	if (FSTYPE_SYSVBFS(tc))
		atf_tc_skip("filesystem has not enough inodes");
	if (FSTYPE_RUMPFS(tc))
		atf_tc_skip("rename not supported by file system");
	if (FSTYPE_UDF(tc))
		atf_tc_expect_fail("PR kern/49046");

	RZ(rump_pub_lwproc_rfork(RUMP_RFCFDG));
	RL(wrkpid = rump_sys_getpid());

	RL(rump_sys_chdir(mp));
	for (i = 0; i < NWRK; i++)
		pthread_create(&pt1[i], NULL, w1, NULL);

	for (i = 0; i < NWRK; i++)
		pthread_create(&pt2[i], NULL, w2, NULL);

	sleep(5);
	quittingtime = 1;

	for (i = 0; i < NWRK; i++)
		pthread_join(pt1[i], NULL);
	for (i = 0; i < NWRK; i++)
		pthread_join(pt2[i], NULL);
	RL(rump_sys_chdir("/"));

	if (FSTYPE_UDF(tc))
		atf_tc_fail("race did not trigger this time");

	if (FSTYPE_MSDOS(tc)) {
		atf_tc_expect_fail("PR kern/43626");
		/*
		 * XXX: race does not trigger every time at least
		 * on amd64/qemu.
		 */
		if (msdosfs_fstest_unmount(tc, mp, 0) != 0) {
			rump_pub_vfs_mount_print(mp, 1);
			atf_tc_fail_errno("unmount failed");
		}
		atf_tc_fail("race did not trigger this time");
	}
}