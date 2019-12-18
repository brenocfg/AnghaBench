#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* heim_isemaphore ;
typedef  int /*<<< orphan*/  dispatch_semaphore_t ;
struct TYPE_4__ {scalar_t__ counter; int /*<<< orphan*/  cond; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  HEIMDAL_MUTEX_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  dispatch_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  heim_assert (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pthread_cond_destroy (int /*<<< orphan*/ *) ; 

void
heim_ipc_semaphore_release(heim_isemaphore s)
{
#ifdef HAVE_GCD
    dispatch_release((dispatch_semaphore_t)s);
#elif !defined(ENABLE_PTHREAD_SUPPORT)
    heim_assert(0, "no semaphore support w/o pthreads");
#else
    HEIMDAL_MUTEX_lock(&s->mutex);
    if (s->counter != 0)
	abort();
    HEIMDAL_MUTEX_unlock(&s->mutex);
    HEIMDAL_MUTEX_destroy(&s->mutex);
    pthread_cond_destroy(&s->cond);
    free(s);
#endif
}