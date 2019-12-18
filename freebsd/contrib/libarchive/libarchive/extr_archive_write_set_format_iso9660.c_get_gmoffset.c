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
struct tm {scalar_t__ tm_isdst; } ;

/* Variables and functions */
 int /*<<< orphan*/  _get_timezone (long*) ; 
 long _timezone ; 
 long timezone ; 

__attribute__((used)) static long
get_gmoffset(struct tm *tm)
{
	long offset;

#if defined(HAVE__GET_TIMEZONE)
	_get_timezone(&offset);
#elif defined(__CYGWIN__) || defined(__MINGW32__) || defined(__BORLANDC__)
	offset = _timezone;
#else
	offset = timezone;
#endif
	offset *= -1;
	if (tm->tm_isdst)
		offset += 3600;
	return (offset);
}