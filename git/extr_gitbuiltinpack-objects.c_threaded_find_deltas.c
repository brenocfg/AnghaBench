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
struct thread_params {int /*<<< orphan*/  mutex; scalar_t__ data_ready; int /*<<< orphan*/  cond; scalar_t__ working; int /*<<< orphan*/  processed; int /*<<< orphan*/  depth; int /*<<< orphan*/  window; scalar_t__ remaining; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  find_deltas (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  progress_cond ; 
 int /*<<< orphan*/  progress_lock () ; 
 int /*<<< orphan*/  progress_unlock () ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *threaded_find_deltas(void *arg)
{
	struct thread_params *me = arg;

	progress_lock();
	while (me->remaining) {
		progress_unlock();

		find_deltas(me->list, &me->remaining,
			    me->window, me->depth, me->processed);

		progress_lock();
		me->working = 0;
		pthread_cond_signal(&progress_cond);
		progress_unlock();

		/*
		 * We must not set ->data_ready before we wait on the
		 * condition because the main thread may have set it to 1
		 * before we get here. In order to be sure that new
		 * work is available if we see 1 in ->data_ready, it
		 * was initialized to 0 before this thread was spawned
		 * and we reset it to 0 right away.
		 */
		pthread_mutex_lock(&me->mutex);
		while (!me->data_ready)
			pthread_cond_wait(&me->cond, &me->mutex);
		me->data_ready = 0;
		pthread_mutex_unlock(&me->mutex);

		progress_lock();
	}
	progress_unlock();
	/* leave ->working 1 so that this doesn't get more work assigned */
	return NULL;
}