#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pthread_mutex_attr {int m_protocol; scalar_t__ m_pshared; scalar_t__ m_robust; int /*<<< orphan*/  m_ceiling; int /*<<< orphan*/  m_type; } ;
struct TYPE_2__ {int /*<<< orphan*/  m_flags; int /*<<< orphan*/ * m_ceilings; void* m_owner; } ;
struct pthread_mutex {scalar_t__ m_yieldloops; scalar_t__ m_spinloops; int /*<<< orphan*/  m_flags; TYPE_1__ m_lock; scalar_t__ m_count; } ;

/* Variables and functions */
 scalar_t__ MUTEX_ADAPTIVE_SPINS ; 
 scalar_t__ PMUTEX_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ PTHREAD_MUTEX_ADAPTIVE_NP ; 
 scalar_t__ PTHREAD_MUTEX_ROBUST ; 
#define  PTHREAD_PRIO_INHERIT 130 
#define  PTHREAD_PRIO_NONE 129 
#define  PTHREAD_PRIO_PROTECT 128 
 scalar_t__ PTHREAD_PROCESS_SHARED ; 
 void* UMUTEX_CONTESTED ; 
 int /*<<< orphan*/  UMUTEX_PRIO_INHERIT ; 
 int /*<<< orphan*/  UMUTEX_PRIO_PROTECT ; 
 int /*<<< orphan*/  UMUTEX_ROBUST ; 
 void* UMUTEX_UNOWNED ; 
 int /*<<< orphan*/  USYNC_PROCESS_SHARED ; 
 scalar_t__ _thr_spinloops ; 
 scalar_t__ _thr_yieldloops ; 
 int /*<<< orphan*/  mutex_init_link (struct pthread_mutex*) ; 
 int /*<<< orphan*/  mutex_init_robust (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mutex_init_body(struct pthread_mutex *pmutex,
    const struct pthread_mutex_attr *attr)
{

	pmutex->m_flags = attr->m_type;
	pmutex->m_count = 0;
	pmutex->m_spinloops = 0;
	pmutex->m_yieldloops = 0;
	mutex_init_link(pmutex);
	switch (attr->m_protocol) {
	case PTHREAD_PRIO_NONE:
		pmutex->m_lock.m_owner = UMUTEX_UNOWNED;
		pmutex->m_lock.m_flags = 0;
		break;
	case PTHREAD_PRIO_INHERIT:
		pmutex->m_lock.m_owner = UMUTEX_UNOWNED;
		pmutex->m_lock.m_flags = UMUTEX_PRIO_INHERIT;
		break;
	case PTHREAD_PRIO_PROTECT:
		pmutex->m_lock.m_owner = UMUTEX_CONTESTED;
		pmutex->m_lock.m_flags = UMUTEX_PRIO_PROTECT;
		pmutex->m_lock.m_ceilings[0] = attr->m_ceiling;
		break;
	}
	if (attr->m_pshared == PTHREAD_PROCESS_SHARED)
		pmutex->m_lock.m_flags |= USYNC_PROCESS_SHARED;
	if (attr->m_robust == PTHREAD_MUTEX_ROBUST) {
		mutex_init_robust(NULL);
		pmutex->m_lock.m_flags |= UMUTEX_ROBUST;
	}
	if (PMUTEX_TYPE(pmutex->m_flags) == PTHREAD_MUTEX_ADAPTIVE_NP) {
		pmutex->m_spinloops =
		    _thr_spinloops ? _thr_spinloops: MUTEX_ADAPTIVE_SPINS;
		pmutex->m_yieldloops = _thr_yieldloops;
	}
}