#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  TYPE_2__* pthread_mutex_t ;
struct TYPE_12__ {scalar_t__ m_owner; } ;
struct TYPE_13__ {TYPE_1__ m_lock; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ PMUTEX_OWNER_ID (TYPE_2__*) ; 
 TYPE_2__* THR_MUTEX_DESTROYED ; 
 TYPE_2__* THR_PSHARED_PTR ; 
 scalar_t__ UMUTEX_RB_NOTRECOV ; 
 scalar_t__ UMUTEX_RB_OWNERDEAD ; 
 int /*<<< orphan*/  __thr_free (TYPE_2__*) ; 
 int /*<<< orphan*/  __thr_pshared_destroy (TYPE_2__**) ; 
 TYPE_2__* __thr_pshared_offpage (TYPE_2__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _get_curthread () ; 
 int /*<<< orphan*/  mutex_assert_not_owned (int /*<<< orphan*/ ,TYPE_2__*) ; 

int
_thr_mutex_destroy(pthread_mutex_t *mutex)
{
	pthread_mutex_t m, m1;
	int ret;

	m = *mutex;
	if (m < THR_MUTEX_DESTROYED) {
		ret = 0;
	} else if (m == THR_MUTEX_DESTROYED) {
		ret = EINVAL;
	} else {
		if (m == THR_PSHARED_PTR) {
			m1 = __thr_pshared_offpage(mutex, 0);
			if (m1 != NULL) {
				if ((uint32_t)m1->m_lock.m_owner !=
				    UMUTEX_RB_OWNERDEAD) {
					mutex_assert_not_owned(
					    _get_curthread(), m1);
				}
				__thr_pshared_destroy(mutex);
			}
			*mutex = THR_MUTEX_DESTROYED;
			return (0);
		}
		if (PMUTEX_OWNER_ID(m) != 0 &&
		    (uint32_t)m->m_lock.m_owner != UMUTEX_RB_NOTRECOV) {
			ret = EBUSY;
		} else {
			*mutex = THR_MUTEX_DESTROYED;
			mutex_assert_not_owned(_get_curthread(), m);
			__thr_free(m);
			ret = 0;
		}
	}

	return (ret);
}