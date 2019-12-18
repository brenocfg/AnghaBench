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
typedef  int /*<<< orphan*/  pthread_mutex_t ;

/* Variables and functions */
 int /*<<< orphan*/  _thr_check_init () ; 
 int check_and_init_mutex (int /*<<< orphan*/ *,struct pthread_mutex**) ; 
 int mutex_lock_common (struct pthread_mutex*,int /*<<< orphan*/ *,int,int) ; 

int
__Tthr_mutex_lock(pthread_mutex_t *mutex)
{
	struct pthread_mutex *m;
	int ret;

	_thr_check_init();
	ret = check_and_init_mutex(mutex, &m);
	if (ret == 0)
		ret = mutex_lock_common(m, NULL, false, false);
	return (ret);
}