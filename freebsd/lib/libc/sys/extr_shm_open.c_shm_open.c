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
typedef  int /*<<< orphan*/  mode_t ;

/* Variables and functions */
 int O_CLOEXEC ; 
 scalar_t__ SHM_OPEN2_OSREL ; 
 int /*<<< orphan*/  SYS_freebsd12_shm_open ; 
 scalar_t__ __getosreldate () ; 
 int __sys_shm_open2 (char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int syscall (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ) ; 

int
shm_open(const char *path, int flags, mode_t mode)
{

	if (__getosreldate() >= SHM_OPEN2_OSREL)
		return (__sys_shm_open2(path, flags | O_CLOEXEC, mode, 0,
		    NULL));

	/*
	 * Fallback to shm_open(2) on older kernels.  The kernel will enforce
	 * O_CLOEXEC in this interface, unlike the newer shm_open2 which does
	 * not enforce it.  The newer interface allows memfd_create(), for
	 * instance, to not have CLOEXEC on the returned fd.
	 */
	return (syscall(SYS_freebsd12_shm_open, path, flags, mode));
}