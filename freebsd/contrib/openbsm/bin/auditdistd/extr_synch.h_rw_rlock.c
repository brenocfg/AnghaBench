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
typedef  int /*<<< orphan*/  pthread_rwlock_t ;

/* Variables and functions */
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 int pthread_rwlock_rdlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __inline void
rw_rlock(pthread_rwlock_t *lock)
{
	int error;

	error = pthread_rwlock_rdlock(lock);
	PJDLOG_ASSERT(error == 0);
}