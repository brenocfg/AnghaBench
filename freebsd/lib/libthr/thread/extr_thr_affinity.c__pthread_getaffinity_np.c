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
struct pthread {int dummy; } ;
typedef  struct pthread* pthread_t ;
typedef  int lwpid_t ;
typedef  int /*<<< orphan*/  cpuset_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_LEVEL_WHICH ; 
 int /*<<< orphan*/  CPU_WHICH_TID ; 
 int /*<<< orphan*/  THR_THREAD_UNLOCK (struct pthread*,struct pthread*) ; 
 int TID (struct pthread*) ; 
 struct pthread* _get_curthread () ; 
 int _thr_find_thread (struct pthread*,struct pthread*,int /*<<< orphan*/ ) ; 
 int cpuset_getaffinity (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,size_t,int /*<<< orphan*/ *) ; 
 int errno ; 

int
_pthread_getaffinity_np(pthread_t td, size_t cpusetsize, cpuset_t *cpusetp)
{
	struct pthread	*curthread = _get_curthread();
	lwpid_t tid;
	int error;

	if (td == curthread) {
		error = cpuset_getaffinity(CPU_LEVEL_WHICH, CPU_WHICH_TID,
			-1, cpusetsize, cpusetp);
		if (error == -1)
			error = errno;
	} else if ((error = _thr_find_thread(curthread, td, 0)) == 0) {
		tid = TID(td);
		error = cpuset_getaffinity(CPU_LEVEL_WHICH, CPU_WHICH_TID, tid,
			    cpusetsize, cpusetp);
		if (error == -1)
			error = errno;
		THR_THREAD_UNLOCK(curthread, td);
	}
	return (error);
}