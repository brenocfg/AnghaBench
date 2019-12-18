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
struct TYPE_4__ {long counter; int /*<<< orphan*/  cond; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  HEIMDAL_MUTEX_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dispatch_semaphore_create (long) ; 
 int /*<<< orphan*/  heim_assert (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  pthread_cond_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

heim_isemaphore
heim_ipc_semaphore_create(long value)
{
#ifdef HAVE_GCD
    return (heim_isemaphore)dispatch_semaphore_create(value);
#elif !defined(ENABLE_PTHREAD_SUPPORT)
    heim_assert(0, "no semaphore support w/o pthreads");
    return NULL;
#else
    heim_isemaphore s = malloc(sizeof(*s));
    if (s == NULL)
	return NULL;
    HEIMDAL_MUTEX_init(&s->mutex);
    pthread_cond_init(&s->cond, NULL);
    s->counter = value;
    return s;
#endif
}