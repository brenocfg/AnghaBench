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
struct pthread_mutex {int /*<<< orphan*/  m_count; int /*<<< orphan*/  m_flags; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EBUSY ; 
 int EINVAL ; 
 int PMUTEX_TYPE (int /*<<< orphan*/ ) ; 
#define  PTHREAD_MUTEX_ADAPTIVE_NP 131 
#define  PTHREAD_MUTEX_ERRORCHECK 130 
#define  PTHREAD_MUTEX_NORMAL 129 
#define  PTHREAD_MUTEX_RECURSIVE 128 

__attribute__((used)) static int
mutex_self_trylock(struct pthread_mutex *m)
{
	int ret;

	switch (PMUTEX_TYPE(m->m_flags)) {
	case PTHREAD_MUTEX_ERRORCHECK:
	case PTHREAD_MUTEX_NORMAL:
	case PTHREAD_MUTEX_ADAPTIVE_NP:
		ret = EBUSY;
		break;

	case PTHREAD_MUTEX_RECURSIVE:
		/* Increment the lock count: */
		if (m->m_count + 1 > 0) {
			m->m_count++;
			ret = 0;
		} else
			ret = EAGAIN;
		break;

	default:
		/* Trap invalid mutex types; */
		ret = EINVAL;
	}

	return (ret);
}