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
struct task {int dummy; } ;
typedef  scalar_t__ pid_t_ ;
typedef  int /*<<< orphan*/  int_t ;
typedef  int dword_t ;
typedef  int /*<<< orphan*/  cpuset ;
typedef  int /*<<< orphan*/  addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  STRACE (char*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _EFAULT ; 
 int /*<<< orphan*/  _ESRCH ; 
 int /*<<< orphan*/  _SC_NPROCESSORS_ONLN ; 
 int /*<<< orphan*/  bit_set (unsigned int,char*) ; 
 int /*<<< orphan*/  lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 struct task* pid_get_task (scalar_t__) ; 
 int /*<<< orphan*/  pids_lock ; 
 unsigned int sysconf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ user_write (int /*<<< orphan*/ ,char*,int) ; 

int_t sys_sched_getaffinity(pid_t_ pid, dword_t cpusetsize, addr_t cpuset_addr) {
    STRACE("sched_getaffinity(%d, %d, %#x)", pid, cpusetsize, cpuset_addr);
    if (pid != 0) {
        lock(&pids_lock);
        struct task *task = pid_get_task(pid);
        unlock(&pids_lock);
        if (task == NULL)
            return _ESRCH;
    }

    unsigned cpus = sysconf(_SC_NPROCESSORS_ONLN);
    if (cpus > cpusetsize * 8)
        cpus = cpusetsize * 8;
    char cpuset[cpusetsize];
    memset(cpuset, 0, sizeof(cpuset));
    for (unsigned i = 0; i < cpus; i++)
        bit_set(i, cpuset);
    if (user_write(cpuset_addr, cpuset, cpusetsize))
        return _EFAULT;
    return 0;
}