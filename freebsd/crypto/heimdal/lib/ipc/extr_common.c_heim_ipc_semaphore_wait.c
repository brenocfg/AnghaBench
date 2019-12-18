#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  scalar_t__ time_t ;
struct timespec {scalar_t__ tv_nsec; scalar_t__ tv_sec; } ;
typedef  TYPE_1__* heim_isemaphore ;
typedef  int /*<<< orphan*/  dispatch_semaphore_t ;
struct TYPE_3__ {scalar_t__ counter; int /*<<< orphan*/  mutex; int /*<<< orphan*/  cond; } ;

/* Variables and functions */
 int DISPATCH_TIME_FOREVER ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ HEIM_IPC_WAIT_FOREVER ; 
 int NSEC_PER_SEC ; 
 long dispatch_semaphore_wait (int /*<<< orphan*/ ,int) ; 
 long errno ; 
 int /*<<< orphan*/  heim_assert (int /*<<< orphan*/ ,char*) ; 
 int pthread_cond_timedwait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timespec*) ; 
 int pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

long
heim_ipc_semaphore_wait(heim_isemaphore s, time_t t)
{
#ifdef HAVE_GCD
    uint64_t timeout;
    if (t == HEIM_IPC_WAIT_FOREVER)
	timeout = DISPATCH_TIME_FOREVER;
    else
	timeout = (uint64_t)t * NSEC_PER_SEC;

    return dispatch_semaphore_wait((dispatch_semaphore_t)s, timeout);
#elif !defined(ENABLE_PTHREAD_SUPPORT)
    heim_assert(0, "no semaphore support w/o pthreads");
    return 0;
#else
    HEIMDAL_MUTEX_lock(&s->mutex);
    /* if counter hits below zero, we get to wait */
    if (--s->counter < 0) {
	int ret;

	if (t == HEIM_IPC_WAIT_FOREVER)
	    ret = pthread_cond_wait(&s->cond, &s->mutex);
	else {
	    struct timespec ts;
	    ts.tv_sec = t;
	    ts.tv_nsec = 0;
	    ret = pthread_cond_timedwait(&s->cond, &s->mutex, &ts);
	}
	if (ret) {
	    HEIMDAL_MUTEX_unlock(&s->mutex);
	    return errno;
	}
    }
    HEIMDAL_MUTEX_unlock(&s->mutex);

    return 0;
#endif
}