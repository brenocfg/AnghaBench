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
struct tm {int tm_year; int tm_mon; int tm_mday; int tm_hour; int tm_min; int tm_sec; int tm_isdst; } ;
typedef  int int32_t ;

/* Variables and functions */
 int VAL () ; 
 int mktime (struct tm*) ; 
 char* strchr (char*,char) ; 
 int strlen (char*) ; 
 int strtoul (char*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*) ; 

int
dotime(char *name, time_t *secp, int32_t *nsecp)
{
    char *p, *val;
    struct tm t;
    int32_t nsec;
    p = strchr(name, '.');
    if (p) {
	*p = '\0';
	nsec = strtoul(++p, &val, 0);
	if (val == p || *val != '\0' || nsec >= 1000000000 || nsec < 0) {
		warnx("invalid nanoseconds");
		goto badformat;
	}
    } else
	nsec = 0;
    if (strlen(name) != 14) {
badformat:
	warnx("date format: YYYYMMDDHHMMSS[.nsec]");
	return 1;
    }
    *nsecp = nsec;

    for (p = name; *p; p++)
	if (*p < '0' || *p > '9')
	    goto badformat;
    
    p = name;
#define VAL() ((*p++) - '0')
    t.tm_year = VAL();
    t.tm_year = VAL() + t.tm_year * 10;
    t.tm_year = VAL() + t.tm_year * 10;
    t.tm_year = VAL() + t.tm_year * 10 - 1900;
    t.tm_mon = VAL();
    t.tm_mon = VAL() + t.tm_mon * 10 - 1;
    t.tm_mday = VAL();
    t.tm_mday = VAL() + t.tm_mday * 10;
    t.tm_hour = VAL();
    t.tm_hour = VAL() + t.tm_hour * 10;
    t.tm_min = VAL();
    t.tm_min = VAL() + t.tm_min * 10;
    t.tm_sec = VAL();
    t.tm_sec = VAL() + t.tm_sec * 10;
    t.tm_isdst = -1;

    *secp = mktime(&t);
    if (*secp == -1) {
	warnx("date/time out of range");
	return 1;
    }
    return 0;
}