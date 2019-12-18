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
 int NUMCYCLES ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ message_recv (int) ; 
 scalar_t__ message_send (int) ; 
 scalar_t__ pthread_cond_signal (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int threaded_child_ready ; 
 int /*<<< orphan*/  threaded_cond ; 
 int /*<<< orphan*/  threaded_mtx ; 
 int threaded_pipeline ; 

__attribute__((used)) static void *
juggling_thread(void *arg)
{
	int fd2, i, j;

	fd2 = *(int *)arg;

	if (pthread_mutex_lock(&threaded_mtx) != 0)
		err(-1, "juggling_thread: pthread_mutex_lock");

	threaded_child_ready = 1;

	if (pthread_cond_signal(&threaded_cond) != 0)
		err(-1, "juggling_thread: pthread_cond_signal");

	if (pthread_mutex_unlock(&threaded_mtx) != 0)
		err(-1, "juggling_thread: pthread_mutex_unlock");

	for (i = 0; i < NUMCYCLES; i++) {
		for (j = 0; j < threaded_pipeline; j++) {
			if (message_recv(fd2) < 0)
				err(-1, "message_recv fd2");

			if (message_send(fd2) < 0)
				err(-1, "message_send fd2");
		}
	}

	return (NULL);
}