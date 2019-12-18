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
 scalar_t__ count ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  static_cond ; 
 int /*<<< orphan*/  static_mutex ; 
 int toggle ; 
 int /*<<< orphan*/  total ; 

__attribute__((used)) static void *
signal_wait_race_threadfunc(void *arg)
{
	printf("2: Second thread.\n");
	PTHREAD_REQUIRE(pthread_mutex_lock(&static_mutex));
	printf("2: Before the loop.\n");
	while (count>0) {
		count--;
		total++;
		toggle = 0;
		/* printf("2: Before signal %d.\n", count); */
		PTHREAD_REQUIRE(pthread_cond_signal(&static_cond));
		do {
			PTHREAD_REQUIRE(pthread_cond_wait(&static_cond,
			    &static_mutex));
		} while (toggle != 1);
	}
	printf("2: After the loop.\n");
	PTHREAD_REQUIRE(pthread_mutex_unlock(&static_mutex));

	return NULL;
}