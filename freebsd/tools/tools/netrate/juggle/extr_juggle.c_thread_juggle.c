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
struct timespec {int dummy; } ;
typedef  int /*<<< orphan*/  pthread_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int NUMCYCLES ; 
 scalar_t__ clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  juggling_thread ; 
 scalar_t__ message_recv (int) ; 
 scalar_t__ message_send (int) ; 
 scalar_t__ pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  threaded_child_ready ; 
 int /*<<< orphan*/  threaded_cond ; 
 int /*<<< orphan*/  threaded_mtx ; 
 int threaded_pipeline ; 
 int /*<<< orphan*/  timespecsub (struct timespec*,struct timespec*,struct timespec*) ; 

__attribute__((used)) static struct timespec
thread_juggle(int fd1, int fd2, int pipeline)
{
	struct timespec tstart, tfinish;
	pthread_t thread;
	int i, j;

	threaded_pipeline = pipeline;

	if (pthread_mutex_init(&threaded_mtx, NULL) != 0)
		err(-1, "thread_juggle: pthread_mutex_init");

	if (pthread_create(&thread, NULL, juggling_thread, &fd2) != 0)
		err(-1, "thread_juggle: pthread_create");

	if (pthread_mutex_lock(&threaded_mtx) != 0)
		err(-1, "thread_juggle: pthread_mutex_lock");

	while (!threaded_child_ready) {
		if (pthread_cond_wait(&threaded_cond, &threaded_mtx) != 0)
			err(-1, "thread_juggle: pthread_cond_wait");
	}

	if (pthread_mutex_unlock(&threaded_mtx) != 0)
		err(-1, "thread_juggle: pthread_mutex_unlock");

	if (clock_gettime(CLOCK_REALTIME, &tstart) < 0)
		err(-1, "thread_juggle: clock_gettime");

	for (i = 0; i < NUMCYCLES; i++) {
		for (j = 0; j < pipeline; j++) {
			if (message_send(fd1) < 0)
				err(-1, "message_send fd1");
		}

		for (j = 0; j < pipeline; j++) {
			if (message_recv(fd1) < 0)
				err(-1, "message_recv fd1");
		}
	}

	if (clock_gettime(CLOCK_REALTIME, &tfinish) < 0)
		err(-1, "thread_juggle: clock_gettime");

	if (pthread_join(thread, NULL) != 0)
		err(-1, "thread_juggle: pthread_join");

	timespecsub(&tfinish, &tstart, &tfinish);

	return (tfinish);
}