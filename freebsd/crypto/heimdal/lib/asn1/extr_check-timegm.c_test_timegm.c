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
typedef  int /*<<< orphan*/  tm ;
typedef  int time_t ;
struct tm {int tm_year; int tm_mon; int tm_mday; int tm_hour; int tm_min; scalar_t__ tm_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  _der_gmtime (int,struct tm*) ; 
 int _der_timegm (struct tm*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  memset (struct tm*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
test_timegm(void)
{
    int ret = 0;
    struct tm tm;
    time_t t;

    memset(&tm, 0, sizeof(tm));
    tm.tm_year = 106;
    tm.tm_mon = 9;
    tm.tm_mday = 1;
    tm.tm_hour = 10;
    tm.tm_min = 3;

    t = _der_timegm(&tm);
    if (t != 1159696980)
	ret += 1;

    tm.tm_mday = 0;
    t = _der_timegm(&tm);
    if (t != -1)
	ret += 1;

    _der_gmtime(1159696980, &tm);
    if (tm.tm_year != 106 ||
	tm.tm_mon != 9 ||
	tm.tm_mday != 1 ||
	tm.tm_hour != 10 ||
	tm.tm_min != 3 ||
	tm.tm_sec != 0)
      errx(1, "tmtime failes");

    return ret;
}