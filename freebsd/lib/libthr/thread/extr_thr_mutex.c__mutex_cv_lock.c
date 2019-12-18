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
 int EOWNERDEAD ; 
 int mutex_lock_common (struct pthread_mutex*,int /*<<< orphan*/ *,int,int) ; 

int
_mutex_cv_lock(struct pthread_mutex *m, int count, bool rb_onlist)
{
	int error;

	error = mutex_lock_common(m, NULL, true, rb_onlist);
	if (error == 0 || error == EOWNERDEAD)
		m->m_count = count;
	return (error);
}