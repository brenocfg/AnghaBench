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
 scalar_t__ __isthreaded ; 
 struct tm* _pthread_getspecific (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _pthread_once (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _pthread_setspecific (int /*<<< orphan*/ ,struct tm*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  lcl_rwlock ; 
 struct tm* localsub (int /*<<< orphan*/  const* const,long,struct tm*) ; 
 int /*<<< orphan*/  localtime_key ; 
 scalar_t__ localtime_key_error ; 
 int /*<<< orphan*/  localtime_key_init ; 
 int /*<<< orphan*/  localtime_once ; 
 scalar_t__ malloc (int) ; 
 struct tm tm ; 
 int /*<<< orphan*/  tzset_basic (int) ; 

struct tm *
localtime(const time_t *const timep)
{
	struct tm *p_tm;

	if (__isthreaded != 0) {
		_pthread_once(&localtime_once, localtime_key_init);
		if (localtime_key_error != 0) {
			errno = localtime_key_error;
			return(NULL);
		}
		p_tm = _pthread_getspecific(localtime_key);
		if (p_tm == NULL) {
			if ((p_tm = (struct tm *)malloc(sizeof(struct tm)))
			    == NULL)
				return(NULL);
			_pthread_setspecific(localtime_key, p_tm);
		}
		_RWLOCK_RDLOCK(&lcl_rwlock);
		tzset_basic(1);
		p_tm = localsub(timep, 0L, p_tm);
		_RWLOCK_UNLOCK(&lcl_rwlock);
	} else {
		tzset_basic(0);
		p_tm = localsub(timep, 0L, &tm);
	}
	return(p_tm);
}