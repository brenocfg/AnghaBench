#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ step; int running; scalar_t__ data; TYPE_2__* pl; } ;
typedef  TYPE_1__ ktp_worker_t ;
struct TYPE_4__ {scalar_t__ n_steps; int n_workers; int /*<<< orphan*/  mutex; int /*<<< orphan*/  cv; int /*<<< orphan*/  shared; scalar_t__ (* func ) (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ;TYPE_1__* workers; } ;
typedef  TYPE_2__ ktp_t ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_cond_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void *ktp_worker(void *data)
{
	ktp_worker_t *w = (ktp_worker_t*)data;
	ktp_t *p = w->pl;
	while (w->step < p->n_steps) {
		// test whether we can kick off the job with this worker
		pthread_mutex_lock(&p->mutex);
		for (;;) {
			int i;
			// test whether another worker is doing the same step
			for (i = 0; i < p->n_workers; ++i) {
				if (w == &p->workers[i]) continue; // ignore itself
				if (p->workers[i].running && p->workers[i].step == w->step)
					break;
			}
			if (i == p->n_workers) break; // no other workers doing w->step; then this worker will
			pthread_cond_wait(&p->cv, &p->mutex);
		}
		w->running = 1;
		pthread_mutex_unlock(&p->mutex);

		// working on w->step
		w->data = p->func(p->shared, w->step, w->step? w->data : 0); // for the first step, input is NULL

		// update step and let other workers know
		pthread_mutex_lock(&p->mutex);
		w->step = w->step == p->n_steps - 1 || w->data? (w->step + 1) % p->n_steps : p->n_steps;
		w->running = 0;
		pthread_cond_broadcast(&p->cv);
		pthread_mutex_unlock(&p->mutex);
	}
	pthread_exit(0);
}