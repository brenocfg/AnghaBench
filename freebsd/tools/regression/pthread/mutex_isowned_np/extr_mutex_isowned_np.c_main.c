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
typedef  int /*<<< orphan*/  pthread_mutex_t ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_isowned_np (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread ; 

int
main(int argc, char *argv[])
{
	pthread_t thr;
	pthread_mutex_t mtx;

	pthread_mutex_init(&mtx, NULL);
	if (pthread_mutex_isowned_np(&mtx) != 0) {
		printf("pthread_mutex_isowned_np() returned non-zero\n"
		    "for a mutex that is not held\n");
		exit(1);
	}
	pthread_mutex_lock(&mtx);
	if (pthread_mutex_isowned_np(&mtx) == 0) {
		printf("pthread_mutex_isowned_np() returned zero\n"
		    "for a mutex we hold ourselves\n");
		exit(1);
	}
	pthread_create(&thr, NULL, thread, &mtx);
	pthread_join(thr, NULL);
	pthread_mutex_unlock(&mtx);
	if (pthread_mutex_isowned_np(&mtx) != 0) {
		printf("pthread_mutex_isowned_np() returned non-zero\n"
		    "for a mutex that is not held\n");
		exit(1);
	}

	printf("OK\n");
	exit(0);
}