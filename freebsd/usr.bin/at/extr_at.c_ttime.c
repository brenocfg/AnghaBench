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
typedef  int time_t ;
struct tm {int tm_year; int tm_isdst; void* tm_min; void* tm_hour; void* tm_mday; void* tm_mon; void* tm_sec; } ;
struct timeval {int tv_sec; } ;

/* Variables and functions */
 void* ATOI2 (char const*) ; 
 scalar_t__ gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 struct tm* localtime (int*) ; 
 int mktime (struct tm*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 char* strchr (char const*,char) ; 
 int strlen (char const*) ; 

__attribute__((used)) static time_t
ttime(const char *arg)
{
    /*
     * This is pretty much a copy of stime_arg1() from touch.c.  I changed
     * the return value and the argument list because it's more convenient
     * (IMO) to do everything in one place. - Joe Halpin
     */
    struct timeval tv[2];
    time_t now;
    struct tm *t;
    int yearset;
    char *p;
    
    if (gettimeofday(&tv[0], NULL))
	panic("Cannot get current time");
    
    /* Start with the current time. */
    now = tv[0].tv_sec;
    if ((t = localtime(&now)) == NULL)
	panic("localtime");
    /* [[CC]YY]MMDDhhmm[.SS] */
    if ((p = strchr(arg, '.')) == NULL)
	t->tm_sec = 0;		/* Seconds defaults to 0. */
    else {
	if (strlen(p + 1) != 2)
	    goto terr;
	*p++ = '\0';
	t->tm_sec = ATOI2(p);
    }
    
    yearset = 0;
    switch(strlen(arg)) {
    case 12:			/* CCYYMMDDhhmm */
	t->tm_year = ATOI2(arg);
	t->tm_year *= 100;
	yearset = 1;
	/* FALLTHROUGH */
    case 10:			/* YYMMDDhhmm */
	if (yearset) {
	    yearset = ATOI2(arg);
	    t->tm_year += yearset;
	} else {
	    yearset = ATOI2(arg);
	    t->tm_year = yearset + 2000;
	}
	t->tm_year -= 1900;	/* Convert to UNIX time. */
	/* FALLTHROUGH */
    case 8:				/* MMDDhhmm */
	t->tm_mon = ATOI2(arg);
	--t->tm_mon;		/* Convert from 01-12 to 00-11 */
	t->tm_mday = ATOI2(arg);
	t->tm_hour = ATOI2(arg);
	t->tm_min = ATOI2(arg);
	break;
    default:
	goto terr;
    }
    
    t->tm_isdst = -1;		/* Figure out DST. */
    tv[0].tv_sec = tv[1].tv_sec = mktime(t);
    if (tv[0].tv_sec != -1)
	return tv[0].tv_sec;
    else
terr:
	panic(
	   "out of range or illegal time specification: [[CC]YY]MMDDhhmm[.SS]");
}