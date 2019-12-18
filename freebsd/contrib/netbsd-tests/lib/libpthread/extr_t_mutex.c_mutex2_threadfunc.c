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
 int /*<<< orphan*/  global_x ; 
 int /*<<< orphan*/  mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_self () ; 
 int /*<<< orphan*/  ts_lengthy ; 

__attribute__((used)) static void *
mutex2_threadfunc(void *arg)
{
	long count = *(int *)arg;

	printf("2: Second thread (%p). Count is %ld\n", pthread_self(), count);

	while (count--) {
		PTHREAD_REQUIRE(mutex_lock(&mutex, &ts_lengthy));
		global_x++;
		PTHREAD_REQUIRE(pthread_mutex_unlock(&mutex));
	}

	return (void *)count;
}