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
typedef  int /*<<< orphan*/  pthread_t ;

/* Variables and functions */
 int NLOOPS ; 
 void* PTHREAD_CANCELED ; 
 int /*<<< orphan*/  cv ; 
 int /*<<< orphan*/  m ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  pthread_cancel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_setconcurrency (int) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int stop ; 
 int /*<<< orphan*/  thr_routine ; 
 int wake ; 

int main(int argc, char **argv)
{
	pthread_t td;
	int i;
	void *result;

	pthread_setconcurrency(1);
	for (i = 0; i < NLOOPS; ++i) {
		stop = 0;
		wake = 0;

		pthread_create(&td, NULL, thr_routine, NULL);
		sleep(1);
		printf("trying: %d\n", i);
		pthread_mutex_lock(&m);
		wake = 1;
		pthread_cond_signal(&cv);
		pthread_cancel(td);
		pthread_mutex_unlock(&m);
		stop = 1;
		result = NULL;
		pthread_join(td, &result);
		if (result == PTHREAD_CANCELED) {
			printf("the condition variable implementation does not\n"
			       "conform to SUSv3, a thread unblocked from\n"
			       "condition variable still can be canceled.\n");
			return (1);
		}
	}

	printf("OK\n");
	return (0);
}