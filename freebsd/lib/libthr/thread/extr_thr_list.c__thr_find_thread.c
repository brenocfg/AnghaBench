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
struct pthread {scalar_t__ state; } ;

/* Variables and functions */
 int EINVAL ; 
 int ESRCH ; 
 scalar_t__ PS_DEAD ; 
 int /*<<< orphan*/  THREAD_LIST_RDLOCK (struct pthread*) ; 
 int /*<<< orphan*/  THREAD_LIST_UNLOCK (struct pthread*) ; 
 int /*<<< orphan*/  THR_THREAD_LOCK (struct pthread*,struct pthread*) ; 
 int /*<<< orphan*/  THR_THREAD_UNLOCK (struct pthread*,struct pthread*) ; 
 struct pthread* _thr_hash_find (struct pthread*) ; 

int
_thr_find_thread(struct pthread *curthread, struct pthread *thread,
    int include_dead)
{
	struct pthread *pthread;
	int ret;

	if (thread == NULL)
		return (EINVAL);

	ret = 0;
	THREAD_LIST_RDLOCK(curthread);
	pthread = _thr_hash_find(thread);
	if (pthread) {
		THR_THREAD_LOCK(curthread, pthread);
		if (include_dead == 0 && pthread->state == PS_DEAD) {
			THR_THREAD_UNLOCK(curthread, pthread);
			ret = ESRCH;
		}
	} else {
		ret = ESRCH;
	}
	THREAD_LIST_UNLOCK(curthread);
	return (ret);
}