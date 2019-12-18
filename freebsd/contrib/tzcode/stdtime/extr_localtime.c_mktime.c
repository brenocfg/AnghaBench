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
typedef  int /*<<< orphan*/  time_t ;
struct tm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _RWLOCK_RDLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _RWLOCK_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lcl_rwlock ; 
 int /*<<< orphan*/  localsub ; 
 int /*<<< orphan*/  time1 (struct tm* const,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  tzset_basic (int) ; 

time_t
mktime(struct tm *const tmp)
{
	time_t mktime_return_value;
	_RWLOCK_RDLOCK(&lcl_rwlock);
	tzset_basic(1);
	mktime_return_value = time1(tmp, localsub, 0L);
	_RWLOCK_UNLOCK(&lcl_rwlock);
	return(mktime_return_value);
}