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
struct pthread_mutex {int m_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_unlock_common (struct pthread_mutex*,int,int*) ; 

int
_mutex_cv_unlock(struct pthread_mutex *m, int *count, int *defer)
{

	/*
	 * Clear the count in case this is a recursive mutex.
	 */
	*count = m->m_count;
	m->m_count = 0;
	(void)mutex_unlock_common(m, true, defer);
        return (0);
}