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
struct tm {int tm_mday; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 struct tm* gmtime (int /*<<< orphan*/ *) ; 

int get_prev_month_end (int day) {
  long t1  = day * 86400  + 43200 ;
  assert (sizeof (time_t) == sizeof (long));
  //struct tm *t = localtime ((time_t *)&t1);
  struct tm *t = gmtime ((time_t *)&t1);
  return day - t->tm_mday;
}