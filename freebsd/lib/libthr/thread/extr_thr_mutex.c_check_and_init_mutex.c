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
struct pthread_mutex {int dummy; } ;
typedef  struct pthread_mutex* pthread_mutex_t ;

/* Variables and functions */
 int EINVAL ; 
 struct pthread_mutex* THR_MUTEX_DESTROYED ; 
 struct pthread_mutex* THR_PSHARED_PTR ; 
 scalar_t__ __predict_false (int) ; 
 struct pthread_mutex* __thr_pshared_offpage (struct pthread_mutex**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _get_curthread () ; 
 int init_static (int /*<<< orphan*/ ,struct pthread_mutex**) ; 
 int /*<<< orphan*/  shared_mutex_init (struct pthread_mutex*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
check_and_init_mutex(pthread_mutex_t *mutex, struct pthread_mutex **m)
{
	int ret;

	*m = *mutex;
	ret = 0;
	if (*m == THR_PSHARED_PTR) {
		*m = __thr_pshared_offpage(mutex, 0);
		if (*m == NULL)
			ret = EINVAL;
		else
			shared_mutex_init(*m, NULL);
	} else if (__predict_false(*m <= THR_MUTEX_DESTROYED)) {
		if (*m == THR_MUTEX_DESTROYED) {
			ret = EINVAL;
		} else {
			ret = init_static(_get_curthread(), mutex);
			if (ret == 0)
				*m = *mutex;
		}
	}
	return (ret);
}