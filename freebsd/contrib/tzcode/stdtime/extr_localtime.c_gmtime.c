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
 scalar_t__ __isthreaded ; 
 struct tm* _pthread_getspecific (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _pthread_once (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _pthread_setspecific (int /*<<< orphan*/ ,struct tm*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  gmtime_key ; 
 scalar_t__ gmtime_key_error ; 
 int /*<<< orphan*/  gmtime_key_init ; 
 int /*<<< orphan*/  gmtime_once ; 
 int /*<<< orphan*/  gmtsub (int /*<<< orphan*/  const* const,long,struct tm*) ; 
 scalar_t__ malloc (int) ; 
 struct tm tm ; 

struct tm *
gmtime(const time_t *const timep)
{
	struct tm *p_tm;

	if (__isthreaded != 0) {
		_pthread_once(&gmtime_once, gmtime_key_init);
		if (gmtime_key_error != 0) {
			errno = gmtime_key_error;
			return(NULL);
		}
		/*
		 * Changed to follow POSIX.1 threads standard, which
		 * is what BSD currently has.
		 */
		if ((p_tm = _pthread_getspecific(gmtime_key)) == NULL) {
			if ((p_tm = (struct tm *)malloc(sizeof(struct tm)))
			    == NULL) {
				return(NULL);
			}
			_pthread_setspecific(gmtime_key, p_tm);
		}
		gmtsub(timep, 0L, p_tm);
		return(p_tm);
	}
	else {
		gmtsub(timep, 0L, &tm);
		return(&tm);
	}
}