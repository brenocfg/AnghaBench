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
struct tm {scalar_t__ tm_gmtoff; scalar_t__ __tm_gmtoff; } ;

/* Variables and functions */
 scalar_t__ _mkgmtime (struct tm*) ; 
 char* getenv (char*) ; 
 scalar_t__ mktime (struct tm*) ; 
 int /*<<< orphan*/  setenv (char*,char*,int) ; 
 char* strdup (char*) ; 
 scalar_t__ timegm (struct tm*) ; 

__attribute__((used)) static time_t my_mktime(struct tm *tm) {
#ifdef HAVE_TIMEGM
  return timegm(tm);
#elif HAVE_TM_TM_GMT_OFF

  time_t t = mktime(tm);
  if (t == (time_t)-1)
    return t;
  return t + tm->tm_gmtoff;
#elif HAVE_TM___TM_GMT_OFF
  time_t t = mktime(tm);
  if (t == (time_t)-1)
    return t;
  return t + tm->__tm_gmtoff;
#elif WIN32
  return _mkgmtime(tm);
#else
  char *tz;

  tz = (tz = getenv("TZ")) != NULL ? strdup(tz) : NULL;
  if (tz != NULL)
    setenv("TZ", "", 1);
  time_t t = mktime(tm);
  if (tz != NULL)
    setenv("TZ", tz, 1);
  return t;
#endif
}