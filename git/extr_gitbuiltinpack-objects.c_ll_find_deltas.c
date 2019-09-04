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
struct thread_params {int window; int depth; unsigned int* processed; int working; int data_ready; unsigned int list_size; unsigned int remaining; int /*<<< orphan*/  mutex; int /*<<< orphan*/  cond; int /*<<< orphan*/  thread; struct object_entry** list; } ;
struct object_entry {scalar_t__ hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  cleanup_threaded_search () ; 
 int delta_search_threads ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_deltas (struct object_entry**,unsigned int*,int,int,unsigned int*) ; 
 int /*<<< orphan*/  fprintf_ln (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free (struct thread_params*) ; 
 int /*<<< orphan*/  init_threaded_search () ; 
 scalar_t__ pack_to_stdout ; 
 scalar_t__ progress ; 
 int /*<<< orphan*/  progress_cond ; 
 int /*<<< orphan*/  progress_lock () ; 
 int /*<<< orphan*/  progress_mutex ; 
 int /*<<< orphan*/  progress_unlock () ; 
 int /*<<< orphan*/  pthread_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct thread_params*) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strerror (int) ; 
 int /*<<< orphan*/  threaded_find_deltas ; 
 struct thread_params* xcalloc (int,int) ; 

__attribute__((used)) static void ll_find_deltas(struct object_entry **list, unsigned list_size,
			   int window, int depth, unsigned *processed)
{
	struct thread_params *p;
	int i, ret, active_threads = 0;

	init_threaded_search();

	if (delta_search_threads <= 1) {
		find_deltas(list, &list_size, window, depth, processed);
		cleanup_threaded_search();
		return;
	}
	if (progress > pack_to_stdout)
		fprintf_ln(stderr, _("Delta compression using up to %d threads"),
			   delta_search_threads);
	p = xcalloc(delta_search_threads, sizeof(*p));

	/* Partition the work amongst work threads. */
	for (i = 0; i < delta_search_threads; i++) {
		unsigned sub_size = list_size / (delta_search_threads - i);

		/* don't use too small segments or no deltas will be found */
		if (sub_size < 2*window && i+1 < delta_search_threads)
			sub_size = 0;

		p[i].window = window;
		p[i].depth = depth;
		p[i].processed = processed;
		p[i].working = 1;
		p[i].data_ready = 0;

		/* try to split chunks on "path" boundaries */
		while (sub_size && sub_size < list_size &&
		       list[sub_size]->hash &&
		       list[sub_size]->hash == list[sub_size-1]->hash)
			sub_size++;

		p[i].list = list;
		p[i].list_size = sub_size;
		p[i].remaining = sub_size;

		list += sub_size;
		list_size -= sub_size;
	}

	/* Start work threads. */
	for (i = 0; i < delta_search_threads; i++) {
		if (!p[i].list_size)
			continue;
		pthread_mutex_init(&p[i].mutex, NULL);
		pthread_cond_init(&p[i].cond, NULL);
		ret = pthread_create(&p[i].thread, NULL,
				     threaded_find_deltas, &p[i]);
		if (ret)
			die(_("unable to create thread: %s"), strerror(ret));
		active_threads++;
	}

	/*
	 * Now let's wait for work completion.  Each time a thread is done
	 * with its work, we steal half of the remaining work from the
	 * thread with the largest number of unprocessed objects and give
	 * it to that newly idle thread.  This ensure good load balancing
	 * until the remaining object list segments are simply too short
	 * to be worth splitting anymore.
	 */
	while (active_threads) {
		struct thread_params *target = NULL;
		struct thread_params *victim = NULL;
		unsigned sub_size = 0;

		progress_lock();
		for (;;) {
			for (i = 0; !target && i < delta_search_threads; i++)
				if (!p[i].working)
					target = &p[i];
			if (target)
				break;
			pthread_cond_wait(&progress_cond, &progress_mutex);
		}

		for (i = 0; i < delta_search_threads; i++)
			if (p[i].remaining > 2*window &&
			    (!victim || victim->remaining < p[i].remaining))
				victim = &p[i];
		if (victim) {
			sub_size = victim->remaining / 2;
			list = victim->list + victim->list_size - sub_size;
			while (sub_size && list[0]->hash &&
			       list[0]->hash == list[-1]->hash) {
				list++;
				sub_size--;
			}
			if (!sub_size) {
				/*
				 * It is possible for some "paths" to have
				 * so many objects that no hash boundary
				 * might be found.  Let's just steal the
				 * exact half in that case.
				 */
				sub_size = victim->remaining / 2;
				list -= sub_size;
			}
			target->list = list;
			victim->list_size -= sub_size;
			victim->remaining -= sub_size;
		}
		target->list_size = sub_size;
		target->remaining = sub_size;
		target->working = 1;
		progress_unlock();

		pthread_mutex_lock(&target->mutex);
		target->data_ready = 1;
		pthread_cond_signal(&target->cond);
		pthread_mutex_unlock(&target->mutex);

		if (!sub_size) {
			pthread_join(target->thread, NULL);
			pthread_cond_destroy(&target->cond);
			pthread_mutex_destroy(&target->mutex);
			active_threads--;
		}
	}
	cleanup_threaded_search();
	free(p);
}