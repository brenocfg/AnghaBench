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
typedef  int /*<<< orphan*/  pthread_mutexattr_t ;
typedef  int /*<<< orphan*/  pthread_mutex_t ;

/* Variables and functions */
 int /*<<< orphan*/  PTHREAD_MUTEX_RECURSIVE ; 
 int pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutexattr_destroy (int /*<<< orphan*/ *) ; 
 int pthread_mutexattr_init (int /*<<< orphan*/ *) ; 
 int pthread_mutexattr_settype (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int init_recursive_mutex(pthread_mutex_t *m)
{
#ifndef NO_PTHREADS
	pthread_mutexattr_t a;
	int ret;

	ret = pthread_mutexattr_init(&a);
	if (!ret) {
		ret = pthread_mutexattr_settype(&a, PTHREAD_MUTEX_RECURSIVE);
		if (!ret)
			ret = pthread_mutex_init(m, &a);
		pthread_mutexattr_destroy(&a);
	}
	return ret;
#else
	return 0;
#endif
}