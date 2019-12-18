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

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 int /*<<< orphan*/  HAVE_THREADS ; 
 int all_work_added ; 
 int /*<<< orphan*/  cond_add ; 
 int /*<<< orphan*/  cond_result ; 
 int /*<<< orphan*/  cond_write ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  grep_attr_mutex ; 
 int /*<<< orphan*/  grep_lock () ; 
 int /*<<< orphan*/  grep_mutex ; 
 int /*<<< orphan*/  grep_read_mutex ; 
 int /*<<< orphan*/  grep_unlock () ; 
 scalar_t__ grep_use_locks ; 
 int num_threads ; 
 int /*<<< orphan*/  pthread_cond_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * threads ; 
 scalar_t__ todo_done ; 
 scalar_t__ todo_end ; 

__attribute__((used)) static int wait_all(void)
{
	int hit = 0;
	int i;

	if (!HAVE_THREADS)
		BUG("Never call this function unless you have started threads");

	grep_lock();
	all_work_added = 1;

	/* Wait until all work is done. */
	while (todo_done != todo_end)
		pthread_cond_wait(&cond_result, &grep_mutex);

	/* Wake up all the consumer threads so they can see that there
	 * is no more work to do.
	 */
	pthread_cond_broadcast(&cond_add);
	grep_unlock();

	for (i = 0; i < num_threads; i++) {
		void *h;
		pthread_join(threads[i], &h);
		hit |= (int) (intptr_t) h;
	}

	free(threads);

	pthread_mutex_destroy(&grep_mutex);
	pthread_mutex_destroy(&grep_read_mutex);
	pthread_mutex_destroy(&grep_attr_mutex);
	pthread_cond_destroy(&cond_add);
	pthread_cond_destroy(&cond_write);
	pthread_cond_destroy(&cond_result);
	grep_use_locks = 0;

	return hit;
}