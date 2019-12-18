#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ptr_t ;
struct TYPE_2__ {int /*<<< orphan*/ * abbrev_wkday; int /*<<< orphan*/ * abbrev_month; } ;

/* Variables and functions */
 int /*<<< orphan*/  LC_TIME ; 
 TYPE_1__* _time_info ; 
 char** day_list ; 
 char** month_list ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 void* strsave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfree (int /*<<< orphan*/ ) ; 

void
dateinit(void)
{
#ifdef notyet
  int i;

  setlocale(LC_TIME, "");

  for (i = 0; i < 12; i++)
      xfree((ptr_t) month_list[i]);
  month_list[0] = strsave(_time_info->abbrev_month[0]);
  month_list[1] = strsave(_time_info->abbrev_month[1]);
  month_list[2] = strsave(_time_info->abbrev_month[2]);
  month_list[3] = strsave(_time_info->abbrev_month[3]);
  month_list[4] = strsave(_time_info->abbrev_month[4]);
  month_list[5] = strsave(_time_info->abbrev_month[5]);
  month_list[6] = strsave(_time_info->abbrev_month[6]);
  month_list[7] = strsave(_time_info->abbrev_month[7]);
  month_list[8] = strsave(_time_info->abbrev_month[8]);
  month_list[9] = strsave(_time_info->abbrev_month[9]);
  month_list[10] = strsave(_time_info->abbrev_month[10]);
  month_list[11] = strsave(_time_info->abbrev_month[11]);

  for (i = 0; i < 7; i++)
      xfree((ptr_t) day_list[i]);
  day_list[0] = strsave(_time_info->abbrev_wkday[0]);
  day_list[1] = strsave(_time_info->abbrev_wkday[1]);
  day_list[2] = strsave(_time_info->abbrev_wkday[2]);
  day_list[3] = strsave(_time_info->abbrev_wkday[3]);
  day_list[4] = strsave(_time_info->abbrev_wkday[4]);
  day_list[5] = strsave(_time_info->abbrev_wkday[5]);
  day_list[6] = strsave(_time_info->abbrev_wkday[6]);
#else
  month_list[0] = "Jan";
  month_list[1] = "Feb";
  month_list[2] = "Mar";
  month_list[3] = "Apr";
  month_list[4] = "May";
  month_list[5] = "Jun";
  month_list[6] = "Jul";
  month_list[7] = "Aug";
  month_list[8] = "Sep";
  month_list[9] = "Oct";
  month_list[10] = "Nov";
  month_list[11] = "Dec";

  day_list[0] = "Sun";
  day_list[1] = "Mon";
  day_list[2] = "Tue";
  day_list[3] = "Wed";
  day_list[4] = "Thu";
  day_list[5] = "Fri";
  day_list[6] = "Sat";
#endif
}