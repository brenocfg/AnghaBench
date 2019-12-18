#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct pthread {int dummy; } ;
typedef  TYPE_1__* pthread_t ;
struct TYPE_6__ {int flags; int /*<<< orphan*/ * joiner; } ;

/* Variables and functions */
 int EINVAL ; 
 int THR_FLAGS_DETACHED ; 
 int /*<<< orphan*/  THR_THREAD_UNLOCK (struct pthread*,TYPE_1__*) ; 
 struct pthread* _get_curthread () ; 
 int _thr_find_thread (struct pthread*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  _thr_try_gc (struct pthread*,TYPE_1__*) ; 

int
_thr_detach(pthread_t pthread)
{
	struct pthread *curthread = _get_curthread();
	int rval;

	if (pthread == NULL)
		return (EINVAL);

	if ((rval = _thr_find_thread(curthread, pthread,
			/*include dead*/1)) != 0) {
		return (rval);
	}

	/* Check if the thread is already detached or has a joiner. */
	if ((pthread->flags & THR_FLAGS_DETACHED) != 0 ||
	    (pthread->joiner != NULL)) {
		THR_THREAD_UNLOCK(curthread, pthread);
		return (EINVAL);
	}

	/* Flag the thread as detached. */
	pthread->flags |= THR_FLAGS_DETACHED;
	_thr_try_gc(curthread, pthread); /* thread lock released */

	return (0);
}