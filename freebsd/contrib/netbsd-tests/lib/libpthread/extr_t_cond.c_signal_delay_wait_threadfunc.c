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
 int /*<<< orphan*/  PTHREAD_REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cond ; 
 int /*<<< orphan*/  mutex ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *
signal_delay_wait_threadfunc(void *arg)
{
	int *shared = (int *) arg;

	printf("2: Second thread.\n");

	printf("2: Locking mutex\n");
	PTHREAD_REQUIRE(pthread_mutex_lock(&mutex));
	printf("2: Got mutex.\n");
	printf("Shared value: %d. Changing to 0.\n", *shared);
	*shared = 0;

	PTHREAD_REQUIRE(pthread_mutex_unlock(&mutex));
	PTHREAD_REQUIRE(pthread_cond_signal(&cond));

	return NULL;
}