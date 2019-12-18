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
typedef  int /*<<< orphan*/  time_t ;
struct tm {int tm_year; int tm_mon; int /*<<< orphan*/  tm_sec; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_mday; } ;

/* Variables and functions */
 int ASN1_BAD_TIMEFORMAT ; 
 int /*<<< orphan*/  _der_timegm (struct tm*) ; 
 int /*<<< orphan*/  memset (struct tm*,int /*<<< orphan*/ ,int) ; 
 int sscanf (char const*,char*,int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
generalizedtime2time (const char *s, time_t *t)
{
    struct tm tm;

    memset(&tm, 0, sizeof(tm));
    if (sscanf (s, "%04d%02d%02d%02d%02d%02dZ",
		&tm.tm_year, &tm.tm_mon, &tm.tm_mday, &tm.tm_hour,
		&tm.tm_min, &tm.tm_sec) != 6) {
	if (sscanf (s, "%02d%02d%02d%02d%02d%02dZ",
		    &tm.tm_year, &tm.tm_mon, &tm.tm_mday, &tm.tm_hour,
		    &tm.tm_min, &tm.tm_sec) != 6)
	    return ASN1_BAD_TIMEFORMAT;
	if (tm.tm_year < 50)
	    tm.tm_year += 2000;
	else
	    tm.tm_year += 1900;
    }
    tm.tm_year -= 1900;
    tm.tm_mon -= 1;
    *t = _der_timegm (&tm);
    return 0;
}