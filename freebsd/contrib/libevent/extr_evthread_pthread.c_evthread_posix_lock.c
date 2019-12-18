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
typedef  int /*<<< orphan*/  pthread_mutex_t ;

/* Variables and functions */
 unsigned int EVTHREAD_TRY ; 
 int pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int pthread_mutex_trylock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
evthread_posix_lock(unsigned mode, void *lock_)
{
	pthread_mutex_t *lock = lock_;
	if (mode & EVTHREAD_TRY)
		return pthread_mutex_trylock(lock);
	else
		return pthread_mutex_lock(lock);
}