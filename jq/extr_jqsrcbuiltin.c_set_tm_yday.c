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
struct tm {int tm_mon; int tm_year; int const tm_mday; int tm_yday; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void set_tm_yday(struct tm *tm) {
  static const int d[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
  int mon = tm->tm_mon;
  int year = 1900 + tm->tm_year;
  int leap_day = 0;
  if (tm->tm_mon > 1 &&
      ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
    leap_day = 1;

  /* Bound check index into d[] */
  if (mon < 0)
    mon = -mon;
  if (mon > 11)
    mon %= 12;

  int yday = d[mon] + leap_day + tm->tm_mday - 1;
  assert(yday == tm->tm_yday || tm->tm_yday == 367);
  tm->tm_yday = yday;
}