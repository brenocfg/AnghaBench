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
struct tm {int tm_year; int tm_mon; int tm_mday; int tm_wday; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ floor (int) ; 

__attribute__((used)) static void set_tm_wday(struct tm *tm) {
  /*
   * https://en.wikipedia.org/wiki/Determination_of_the_day_of_the_week#Gauss.27s_algorithm
   * https://cs.uwaterloo.ca/~alopez-o/math-faq/node73.html
   *
   * Tested with dates from 1900-01-01 through 2100-01-01.  This
   * algorithm produces the wrong day-of-the-week number for dates in
   * the range 1900-01-01..1900-02-28, and for 2100-01-01..2100-02-28.
   * Since this is only needed on OS X and *BSD, we might just document
   * this.
   */
  int century = (1900 + tm->tm_year) / 100;
  int year = (1900 + tm->tm_year) % 100;
  if (tm->tm_mon < 2)
    year--;
  /*
   * The month value in the wday computation below is shifted so that
   * March is 1, April is 2, .., January is 11, and February is 12.
   */
  int mon = tm->tm_mon - 1;
  if (mon < 1)
    mon += 12;
  int wday =
    (tm->tm_mday + (int)floor((2.6 * mon - 0.2)) + year + (int)floor(year / 4.0) + (int)floor(century / 4.0) - 2 * century) % 7;
  if (wday < 0)
    wday += 7;
#if 0
  /* See commentary above */
  assert(wday == tm->tm_wday || tm->tm_wday == 8);
#endif
  tm->tm_wday = wday;
}