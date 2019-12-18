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
 int PTHREAD_BARRIER_SERIAL_THREAD ; 
 int /*<<< orphan*/  PTHREAD_REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  after_barrier_count ; 
 int /*<<< orphan*/  barrier ; 
 int /*<<< orphan*/  mutex ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 int pthread_barrier_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serial_count ; 

__attribute__((used)) static void *
threadfunc(void *arg)
{
	int which = (int)(long)arg;
	int rv;

	printf("thread %d entering barrier\n", which);
	rv = pthread_barrier_wait(&barrier);
	printf("thread %d leaving barrier -> %d\n", which, rv);

	PTHREAD_REQUIRE(pthread_mutex_lock(&mutex));
	after_barrier_count++;
	if (rv == PTHREAD_BARRIER_SERIAL_THREAD)
		serial_count++;
	PTHREAD_REQUIRE(pthread_mutex_unlock(&mutex));

	return NULL;
}