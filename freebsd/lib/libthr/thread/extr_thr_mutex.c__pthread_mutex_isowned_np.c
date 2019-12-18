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
struct pthread_mutex {int dummy; } ;
typedef  struct pthread_mutex* pthread_mutex_t ;

/* Variables and functions */
 scalar_t__ PMUTEX_OWNER_ID (struct pthread_mutex*) ; 
 struct pthread_mutex* THR_MUTEX_DESTROYED ; 
 struct pthread_mutex* THR_PSHARED_PTR ; 
 scalar_t__ TID (int /*<<< orphan*/ ) ; 
 struct pthread_mutex* __thr_pshared_offpage (struct pthread_mutex**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _get_curthread () ; 
 int /*<<< orphan*/  shared_mutex_init (struct pthread_mutex*,int /*<<< orphan*/ *) ; 

int
_pthread_mutex_isowned_np(pthread_mutex_t *mutex)
{
	struct pthread_mutex *m;

	if (*mutex == THR_PSHARED_PTR) {
		m = __thr_pshared_offpage(mutex, 0);
		if (m == NULL)
			return (0);
		shared_mutex_init(m, NULL);
	} else {
		m = *mutex;
		if (m <= THR_MUTEX_DESTROYED)
			return (0);
	}
	return (PMUTEX_OWNER_ID(m) == TID(_get_curthread()));
}