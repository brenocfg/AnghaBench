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
typedef  scalar_t__ time_t ;
struct tm {int tm_sec; int tm_min; int tm_hour; int tm_yday; int tm_year; } ;

/* Variables and functions */
 scalar_t__ _mkgmtime64 (struct tm*) ; 
 scalar_t__ mktime (struct tm*) ; 
 scalar_t__ timegm (struct tm*) ; 

__attribute__((used)) static time_t
time_from_tm(struct tm *t)
{
#if HAVE_TIMEGM
        /* Use platform timegm() if available. */
        return (timegm(t));
#elif HAVE__MKGMTIME64
        return (_mkgmtime64(t));
#else
        /* Else use direct calculation using POSIX assumptions. */
        /* First, fix up tm_yday based on the year/month/day. */
        if (mktime(t) == (time_t)-1)
                return ((time_t)-1);
        /* Then we can compute timegm() from first principles. */
        return (t->tm_sec
            + t->tm_min * 60
            + t->tm_hour * 3600
            + t->tm_yday * 86400
            + (t->tm_year - 70) * 31536000
            + ((t->tm_year - 69) / 4) * 86400
            - ((t->tm_year - 1) / 100) * 86400
            + ((t->tm_year + 299) / 400) * 86400);
#endif
}