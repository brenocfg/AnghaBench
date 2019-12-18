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
 struct pthread_mutex* THR_PSHARED_PTR ; 
 struct pthread_mutex* __thr_pshared_offpage (struct pthread_mutex**,int /*<<< orphan*/ ) ; 
 int mutex_unlock_common (struct pthread_mutex*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shared_mutex_init (struct pthread_mutex*,int /*<<< orphan*/ *) ; 

int
_thr_mutex_unlock(pthread_mutex_t *mutex)
{
	struct pthread_mutex *mp;

	if (*mutex == THR_PSHARED_PTR) {
		mp = __thr_pshared_offpage(mutex, 0);
		if (mp == NULL)
			return (EINVAL);
		shared_mutex_init(mp, NULL);
	} else {
		mp = *mutex;
	}
	return (mutex_unlock_common(mp, false, NULL));
}