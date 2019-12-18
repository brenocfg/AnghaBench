#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ pthread_t ;
struct TYPE_3__ {scalar_t__ _fl_owner; int _fl_count; int /*<<< orphan*/  _fl_mutex; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int /*<<< orphan*/  _pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ _pthread_self () ; 

void 
_funlockfile(FILE *fp)
{
	pthread_t	curthread = _pthread_self();

	/*
	 * Check if this file is owned by the current thread:
	 */
	if (fp->_fl_owner == curthread) {
		/*
		 * Check if this thread has locked the FILE
		 * more than once:
		 */
		if (fp->_fl_count > 1)
			/*
			 * Decrement the count of the number of
			 * times the running thread has locked this
			 * file:
			 */
			fp->_fl_count--;
		else {
			/*
			 * The running thread will release the
			 * lock now:
			 */
			fp->_fl_count = 0;
			fp->_fl_owner = NULL;
			_pthread_mutex_unlock(&fp->_fl_mutex);
		}
	}
}