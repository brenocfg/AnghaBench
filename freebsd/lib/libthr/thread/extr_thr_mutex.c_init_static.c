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
struct pthread {int dummy; } ;
typedef  scalar_t__ pthread_mutex_t ;

/* Variables and functions */
 scalar_t__ THR_ADAPTIVE_MUTEX_INITIALIZER ; 
 int /*<<< orphan*/  THR_LOCK_ACQUIRE (struct pthread*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  THR_LOCK_RELEASE (struct pthread*,int /*<<< orphan*/ *) ; 
 scalar_t__ THR_MUTEX_INITIALIZER ; 
 int /*<<< orphan*/  __thr_calloc ; 
 int /*<<< orphan*/  _mutex_static_lock ; 
 int /*<<< orphan*/  _pthread_mutexattr_adaptive_default ; 
 int /*<<< orphan*/  _pthread_mutexattr_default ; 
 int mutex_init (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
init_static(struct pthread *thread, pthread_mutex_t *mutex)
{
	int ret;

	THR_LOCK_ACQUIRE(thread, &_mutex_static_lock);

	if (*mutex == THR_MUTEX_INITIALIZER)
		ret = mutex_init(mutex, &_pthread_mutexattr_default,
		    __thr_calloc);
	else if (*mutex == THR_ADAPTIVE_MUTEX_INITIALIZER)
		ret = mutex_init(mutex, &_pthread_mutexattr_adaptive_default,
		    __thr_calloc);
	else
		ret = 0;
	THR_LOCK_RELEASE(thread, &_mutex_static_lock);

	return (ret);
}