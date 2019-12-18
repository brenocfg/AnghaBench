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
typedef  int /*<<< orphan*/  locale_t ;

/* Variables and functions */
 int /*<<< orphan*/  FIX_LOCALE (int /*<<< orphan*/ ) ; 
 char* _strptime (char const*,char const*,struct tm*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  localtime_r (int /*<<< orphan*/ *,struct tm*) ; 
 int /*<<< orphan*/  timegm (struct tm*) ; 

char *
strptime_l(const char * __restrict buf, const char * __restrict fmt,
    struct tm * __restrict tm, locale_t loc)
{
	char *ret;
	int gmt;
	FIX_LOCALE(loc);

	gmt = 0;
	ret = _strptime(buf, fmt, tm, &gmt, loc);
	if (ret && gmt) {
		time_t t = timegm(tm);

		localtime_r(&t, tm);
	}

	return (ret);
}