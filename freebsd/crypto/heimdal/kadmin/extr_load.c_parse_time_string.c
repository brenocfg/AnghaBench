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
struct tm {int tm_year; int tm_mon; int tm_mday; int tm_hour; int tm_min; int tm_sec; scalar_t__ tm_isdst; } ;

/* Variables and functions */
 int sscanf (char const*,char*,int*,int*,int*,int*,int*,int*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  timegm (struct tm*) ; 

__attribute__((used)) static int
parse_time_string(time_t *t, const char *s)
{
    int year, month, date, hour, minute, second;
    struct tm tm;

    if(strcmp(s, "-") == 0)
	return 0;
    if(sscanf(s, "%04d%02d%02d%02d%02d%02d",
	      &year, &month, &date, &hour, &minute, &second) != 6)
	return -1;
    tm.tm_year  = year - 1900;
    tm.tm_mon   = month - 1;
    tm.tm_mday  = date;
    tm.tm_hour  = hour;
    tm.tm_min   = minute;
    tm.tm_sec   = second;
    tm.tm_isdst = 0;
    *t = timegm(&tm);
    return 1;
}