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

/* Variables and functions */
 int /*<<< orphan*/  DFLDSIZ ; 
 int /*<<< orphan*/  DFLSSIZ ; 
 int HZ ; 
 int HZ_VM ; 
 scalar_t__ INT_MAX ; 
 int /*<<< orphan*/  MAXDSIZ ; 
 int /*<<< orphan*/  MAXSSIZ ; 
 int /*<<< orphan*/  MAXTSIZ ; 
 int MSGBUF_SIZE ; 
 scalar_t__ NGROUPS_MAX ; 
 int PID_MAX ; 
 int SBT_1S ; 
 int /*<<< orphan*/  SGROWSIZ ; 
 int /*<<< orphan*/  TUNABLE_INT_FETCH (char*,...) ; 
 int /*<<< orphan*/  TUNABLE_LONG_FETCH (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TUNABLE_ULONG_FETCH (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VM_BCACHE_SIZE_MAX ; 
 scalar_t__ VM_GUEST_NO ; 
 int /*<<< orphan*/  VM_SWZONE_SIZE_MAX ; 
 int /*<<< orphan*/  dfldsiz ; 
 int /*<<< orphan*/  dflssiz ; 
 int hz ; 
 int kstack_pages ; 
 int /*<<< orphan*/  maxbcache ; 
 int /*<<< orphan*/  maxdsiz ; 
 int /*<<< orphan*/  maxssiz ; 
 int /*<<< orphan*/  maxswzone ; 
 int /*<<< orphan*/  maxtsiz ; 
 int msgbufsize ; 
 scalar_t__ ngroups_max ; 
 int pid_max ; 
 int /*<<< orphan*/  sbttobt (int) ; 
 int /*<<< orphan*/  sgrowsiz ; 
 int tick ; 
 int /*<<< orphan*/  tick_bt ; 
 int tick_sbt ; 
 scalar_t__ ticks ; 
 int unmapped_buf_allowed ; 
 scalar_t__ vm_guest ; 

void
init_param1(void)
{

#if !defined(__mips__) && !defined(__arm64__) && !defined(__sparc64__)
	TUNABLE_INT_FETCH("kern.kstack_pages", &kstack_pages);
#endif
	hz = -1;
	TUNABLE_INT_FETCH("kern.hz", &hz);
	if (hz == -1)
		hz = vm_guest > VM_GUEST_NO ? HZ_VM : HZ;
	tick = 1000000 / hz;
	tick_sbt = SBT_1S / hz;
	tick_bt = sbttobt(tick_sbt);

	/*
	 * Arrange for ticks to wrap 10 minutes after boot to help catch
	 * sign problems sooner.
	 */
	ticks = INT_MAX - (hz * 10 * 60);

#ifdef VM_SWZONE_SIZE_MAX
	maxswzone = VM_SWZONE_SIZE_MAX;
#endif
	TUNABLE_LONG_FETCH("kern.maxswzone", &maxswzone);
#ifdef VM_BCACHE_SIZE_MAX
	maxbcache = VM_BCACHE_SIZE_MAX;
#endif
	TUNABLE_LONG_FETCH("kern.maxbcache", &maxbcache);
	msgbufsize = MSGBUF_SIZE;
	TUNABLE_INT_FETCH("kern.msgbufsize", &msgbufsize);

	maxtsiz = MAXTSIZ;
	TUNABLE_ULONG_FETCH("kern.maxtsiz", &maxtsiz);
	dfldsiz = DFLDSIZ;
	TUNABLE_ULONG_FETCH("kern.dfldsiz", &dfldsiz);
	maxdsiz = MAXDSIZ;
	TUNABLE_ULONG_FETCH("kern.maxdsiz", &maxdsiz);
	dflssiz = DFLSSIZ;
	TUNABLE_ULONG_FETCH("kern.dflssiz", &dflssiz);
	maxssiz = MAXSSIZ;
	TUNABLE_ULONG_FETCH("kern.maxssiz", &maxssiz);
	sgrowsiz = SGROWSIZ;
	TUNABLE_ULONG_FETCH("kern.sgrowsiz", &sgrowsiz);

	/*
	 * Let the administrator set {NGROUPS_MAX}, but disallow values
	 * less than NGROUPS_MAX which would violate POSIX.1-2008 or
	 * greater than INT_MAX-1 which would result in overflow.
	 */
	ngroups_max = NGROUPS_MAX;
	TUNABLE_INT_FETCH("kern.ngroups", &ngroups_max);
	if (ngroups_max < NGROUPS_MAX)
		ngroups_max = NGROUPS_MAX;

	/*
	 * Only allow to lower the maximal pid.
	 * Prevent setting up a non-bootable system if pid_max is too low.
	 */
	TUNABLE_INT_FETCH("kern.pid_max", &pid_max);
	if (pid_max > PID_MAX)
		pid_max = PID_MAX;
	else if (pid_max < 300)
		pid_max = 300;

	TUNABLE_INT_FETCH("vfs.unmapped_buf_allowed", &unmapped_buf_allowed);
}