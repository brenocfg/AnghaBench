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

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int* dd ; 
 char* dows ; 
 char* months ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int,char*,int,int,int,int) ; 

void gen_http_date (char date_buffer[29], int time) {
  int day, mon, year, hour, min, sec, xd, i, dow;
  if (time < 0) time = 0;
  sec = time % 60;
  time /= 60;
  min = time % 60;
  time /= 60;
  hour = time % 24;
  time /= 24;
  dow = (time + 4) % 7;
  xd = time % (365 * 3 + 366);
  time /= (365 * 3 + 366);
  year = time * 4 + 1970;
  if (xd >= 365) {
    year++;
    xd -= 365;
    if (xd >= 365) {
      year++;
      xd -= 365;
      if (xd >= 366) {
        year++;
        xd -= 366;
      }
    }
  }
  if (year & 3) {
    dd[1] = 28;
  } else {
    dd[1] = 29;
  }

  for (i = 0; i < 12; i++) {
    if (xd < dd[i]) {
      break;
    }
    xd -= dd[i];
  }

  day = xd + 1;
  mon = i;
  assert (day >= 1 && day <= 31 && mon >=0 && mon <= 11 &&
      year >= 1970 && year <= 2039);

  sprintf (date_buffer, "%.3s, %.2d %.3s %d %.2d:%.2d:%.2d GM", 
      dows + dow * 3, day, months + mon * 3, year,
      hour, min, sec);
  date_buffer[28] = 'T';
}