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
struct pthread {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  THR_CRITICAL_ENTER (struct pthread*) ; 
 int /*<<< orphan*/  THR_THREAD_UNLOCK (struct pthread*,struct pthread*) ; 
 int _thr_find_thread (struct pthread*,struct pthread*,int) ; 

int
_thr_ref_add(struct pthread *curthread, struct pthread *thread,
    int include_dead)
{
	int ret;

	if (thread == NULL)
		/* Invalid thread: */
		return (EINVAL);

	if ((ret = _thr_find_thread(curthread, thread, include_dead)) == 0) {
		thread->refcount++;
		THR_CRITICAL_ENTER(curthread);
		THR_THREAD_UNLOCK(curthread, thread);
	}

	/* Return zero if the thread exists: */
	return (ret);
}