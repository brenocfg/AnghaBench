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
struct tm {int tm_hour; int tm_min; int tm_year; int tm_mon; int tm_mday; scalar_t__ tm_sec; } ;

/* Variables and functions */
 long SECS_PER_DAY ; 
 long date_to_julian (int,int,int) ; 

__attribute__((used)) static int julian_adj(const struct tm *tm, int off_day, long offset_sec,
                      long *pday, int *psec)
{
    int offset_hms, offset_day;
    long time_jd;
    int time_year, time_month, time_day;
    /* split offset into days and day seconds */
    offset_day = offset_sec / SECS_PER_DAY;
    /* Avoid sign issues with % operator */
    offset_hms = offset_sec - (offset_day * SECS_PER_DAY);
    offset_day += off_day;
    /* Add current time seconds to offset */
    offset_hms += tm->tm_hour * 3600 + tm->tm_min * 60 + tm->tm_sec;
    /* Adjust day seconds if overflow */
    if (offset_hms >= SECS_PER_DAY) {
        offset_day++;
        offset_hms -= SECS_PER_DAY;
    } else if (offset_hms < 0) {
        offset_day--;
        offset_hms += SECS_PER_DAY;
    }

    /*
     * Convert date of time structure into a Julian day number.
     */

    time_year = tm->tm_year + 1900;
    time_month = tm->tm_mon + 1;
    time_day = tm->tm_mday;

    time_jd = date_to_julian(time_year, time_month, time_day);

    /* Work out Julian day of new date */
    time_jd += offset_day;

    if (time_jd < 0)
        return 0;

    *pday = time_jd;
    *psec = offset_hms;
    return 1;
}