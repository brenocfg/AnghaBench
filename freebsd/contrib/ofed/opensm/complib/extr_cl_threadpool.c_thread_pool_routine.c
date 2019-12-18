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
struct TYPE_3__ {int /*<<< orphan*/  context; int /*<<< orphan*/  (* pfn_callback ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  events; int /*<<< orphan*/  mutex; int /*<<< orphan*/  cond; } ;
typedef  TYPE_1__ cl_thread_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  cleanup_mutex ; 
 int /*<<< orphan*/  pthread_cleanup_pop (int) ; 
 int /*<<< orphan*/  pthread_cleanup_push (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *thread_pool_routine(void *context)
{
	cl_thread_pool_t *p_thread_pool = (cl_thread_pool_t *) context;

	do {
		pthread_mutex_lock(&p_thread_pool->mutex);
		pthread_cleanup_push(cleanup_mutex, p_thread_pool);
		while (!p_thread_pool->events)
			pthread_cond_wait(&p_thread_pool->cond,
					  &p_thread_pool->mutex);
		p_thread_pool->events--;
		pthread_cleanup_pop(1);
		/* The event has been signalled.  Invoke the callback. */
		(*p_thread_pool->pfn_callback) (p_thread_pool->context);
	} while (1);

	return NULL;
}