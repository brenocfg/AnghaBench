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
typedef  int /*<<< orphan*/  pthread_mutexattr_t ;
typedef  void pthread_mutex_t ;

/* Variables and functions */
 unsigned int EVTHREAD_LOCKTYPE_RECURSIVE ; 
 int /*<<< orphan*/  attr_recursive ; 
 int /*<<< orphan*/  mm_free (void*) ; 
 void* mm_malloc (int) ; 
 scalar_t__ pthread_mutex_init (void*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *
evthread_posix_lock_alloc(unsigned locktype)
{
	pthread_mutexattr_t *attr = NULL;
	pthread_mutex_t *lock = mm_malloc(sizeof(pthread_mutex_t));
	if (!lock)
		return NULL;
	if (locktype & EVTHREAD_LOCKTYPE_RECURSIVE)
		attr = &attr_recursive;
	if (pthread_mutex_init(lock, attr)) {
		mm_free(lock);
		return NULL;
	}
	return lock;
}