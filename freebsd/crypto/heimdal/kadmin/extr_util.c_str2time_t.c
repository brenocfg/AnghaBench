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
typedef  int /*<<< orphan*/  tm2 ;
typedef  int /*<<< orphan*/  tm ;
typedef  scalar_t__ time_t ;
struct tm {int tm_hour; int tm_min; int tm_sec; } ;

/* Variables and functions */
 scalar_t__ isspace (unsigned char) ; 
 int /*<<< orphan*/  memset (struct tm*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ parse_time (char const*,char*) ; 
 scalar_t__ strcasecmp (char const*,char*) ; 
 char* strptime (char const*,char*,struct tm*) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 
 scalar_t__ tm2time (struct tm,int /*<<< orphan*/ ) ; 

int
str2time_t (const char *str, time_t *t)
{
    const char *p;
    struct tm tm, tm2;

    memset (&tm, 0, sizeof (tm));
    memset (&tm2, 0, sizeof (tm2));

    while(isspace((unsigned char)*str))
	str++;

    if (str[0] == '+') {
	str++;
	*t = parse_time(str, "month");
	if (*t < 0)
	    return -1;
	*t += time(NULL);
	return 0;
    }

    if(strcasecmp(str, "never") == 0) {
	*t = 0;
	return 0;
    }

    if(strcasecmp(str, "now") == 0) {
	*t = time(NULL);
	return 0;
    }

    p = strptime (str, "%Y-%m-%d", &tm);

    if (p == NULL)
	return -1;

    while(isspace((unsigned char)*p))
	p++;

    /* XXX this is really a bit optimistic, we should really complain
       if there was a problem parsing the time */
    if(p[0] != '\0' && strptime (p, "%H:%M:%S", &tm2) != NULL) {
	tm.tm_hour = tm2.tm_hour;
	tm.tm_min  = tm2.tm_min;
	tm.tm_sec  = tm2.tm_sec;
    } else {
	/* Do it on the end of the day */
	tm.tm_hour = 23;
	tm.tm_min  = 59;
	tm.tm_sec  = 59;
    }

    *t = tm2time (tm, 0);
    return 0;
}