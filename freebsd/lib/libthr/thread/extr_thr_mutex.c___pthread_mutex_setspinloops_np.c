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
struct pthread_mutex {int m_spinloops; } ;
typedef  int /*<<< orphan*/  pthread_mutex_t ;

/* Variables and functions */
 int check_and_init_mutex (int /*<<< orphan*/ *,struct pthread_mutex**) ; 

int
__pthread_mutex_setspinloops_np(pthread_mutex_t *mutex, int count)
{
	struct pthread_mutex *m;
	int ret;

	ret = check_and_init_mutex(mutex, &m);
	if (ret == 0)
		m->m_spinloops = count;
	return (ret);
}