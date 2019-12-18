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
struct tm {int tm_year; int tm_mon; int tm_mday; int tm_hour; int tm_min; int tm_sec; int tm_wday; int tm_yday; } ;
typedef  int /*<<< orphan*/  jv ;

/* Variables and functions */
 int /*<<< orphan*/  TO_TM_FIELD (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  jv_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct tm*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int jv2tm(jv a, struct tm *tm) {
  memset(tm, 0, sizeof(*tm));
  TO_TM_FIELD(tm->tm_year, a, 0);
  tm->tm_year -= 1900;
  TO_TM_FIELD(tm->tm_mon,  a, 1);
  TO_TM_FIELD(tm->tm_mday, a, 2);
  TO_TM_FIELD(tm->tm_hour, a, 3);
  TO_TM_FIELD(tm->tm_min,  a, 4);
  TO_TM_FIELD(tm->tm_sec,  a, 5);
  TO_TM_FIELD(tm->tm_wday, a, 6);
  TO_TM_FIELD(tm->tm_yday, a, 7);
  jv_free(a);

  // We use UTC everywhere (gettimeofday, gmtime) and UTC does not do DST.
  // Setting tm_isdst to 0 is done by the memset.
  // tm->tm_isdst = 0;

  // The standard permits the tm structure to contain additional members. We
  // hope it is okay to initialize them to zero, because the standard does not
  // provide an alternative.

  return 1;
}