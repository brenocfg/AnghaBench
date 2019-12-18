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
 int /*<<< orphan*/  RL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RUMP_RFCFDG ; 
 int /*<<< orphan*/  RZ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  atf_tc_expect_signal (int,char*) ; 
 int /*<<< orphan*/  atf_tc_skip (char*) ; 
 int /*<<< orphan*/  pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int quittingtime ; 
 int /*<<< orphan*/  rump_pub_lwproc_rfork (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rump_sys_chdir (char const*) ; 
 int /*<<< orphan*/  rump_sys_getpid () ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  w1_dirs ; 
 int /*<<< orphan*/  w2 ; 
 int /*<<< orphan*/  wrkpid ; 

__attribute__((used)) static void
renamerace_dirs(const atf_tc_t *tc, const char *mp)
{
	pthread_t pt1, pt2;

	if (FSTYPE_SYSVBFS(tc))
		atf_tc_skip("directories not supported by file system");

	if (FSTYPE_RUMPFS(tc))
		atf_tc_skip("rename not supported by file system");

	/* XXX: msdosfs also sometimes hangs */
	if (FSTYPE_MSDOS(tc))
		atf_tc_expect_signal(-1, "PR kern/43626");

	RZ(rump_pub_lwproc_rfork(RUMP_RFCFDG));
	RL(wrkpid = rump_sys_getpid());

	RL(rump_sys_chdir(mp));
	pthread_create(&pt1, NULL, w1_dirs, NULL);
	pthread_create(&pt2, NULL, w2, NULL);

	sleep(5);
	quittingtime = 1;

	pthread_join(pt1, NULL);
	pthread_join(pt2, NULL);
	RL(rump_sys_chdir("/"));

	/*
	 * Doesn't always trigger when run on a slow backend
	 * (i.e. not on tmpfs/mfs).  So do the usual kludge.
	 */
	if (FSTYPE_MSDOS(tc))
		abort();
}