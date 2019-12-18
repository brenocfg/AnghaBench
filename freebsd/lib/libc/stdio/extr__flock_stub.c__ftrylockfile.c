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
 scalar_t__ _pthread_mutex_trylock (int /*<<< orphan*/ *) ; 
 scalar_t__ _pthread_self () ; 

int
_ftrylockfile(FILE *fp)
{
	pthread_t curthread = _pthread_self();
	int	ret = 0;

	if (fp->_fl_owner == curthread)
		fp->_fl_count++;
	/*
	 * Make sure this mutex is treated as a private
	 * internal mutex:
	 */
	else if (_pthread_mutex_trylock(&fp->_fl_mutex) == 0) {
		fp->_fl_owner = curthread;
		fp->_fl_count = 1;
	}
	else
		ret = -1;
	return (ret);
}