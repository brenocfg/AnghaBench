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
typedef  TYPE_1__* heim_isemaphore ;
typedef  int /*<<< orphan*/  dispatch_semaphore_t ;
struct TYPE_3__ {scalar_t__ counter; int /*<<< orphan*/  cond; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 long EINVAL ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_unlock (int /*<<< orphan*/ *) ; 
 long dispatch_semaphore_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heim_assert (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 

long
heim_ipc_semaphore_signal(heim_isemaphore s)
{
#ifdef HAVE_GCD
    return dispatch_semaphore_signal((dispatch_semaphore_t)s);
#elif !defined(ENABLE_PTHREAD_SUPPORT)
    heim_assert(0, "no semaphore support w/o pthreads");
    return EINVAL;
#else
    int wakeup;
    HEIMDAL_MUTEX_lock(&s->mutex);
    wakeup = (++s->counter == 0) ;
    HEIMDAL_MUTEX_unlock(&s->mutex);
    if (wakeup)
	pthread_cond_signal(&s->cond);
    return 0;
#endif
}