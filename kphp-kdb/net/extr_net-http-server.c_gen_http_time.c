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
 int* dd ; 
 int /*<<< orphan*/  memcmp (scalar_t__,char*,int) ; 
 scalar_t__ months ; 
 int sscanf (char*,char*,char*,int*,char*,int*,int*,int*,int*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 

int gen_http_time (char *date_buffer, int *time) {
  char dow[4];
  char month[4];
  char tz[16];
  int i, year, mon, day, hour, min, sec;
  int argc = sscanf (date_buffer, "%3s, %d %3s %d %d:%d:%d %15s", dow, &day, month, &year, &hour, &min, &sec, tz);
  if (argc != 8) {
    return (argc > 0) ? -argc : -8;
  }
  for (mon = 0; mon < 12; mon++) {
    if (!memcmp (months + mon * 3, month, 3)) {
      break;
    }
  }
  if (mon == 12) {
    return -11;
  }
  if (year < 1970 || year > 2039) {
    return -12;
  }
  if (hour < 0 || hour >= 24) {
    return -13;
  }
  if (min < 0 || min >= 60) {
    return -14;
  }
  if (sec < 0 || sec >= 60) {
    return -15;
  }
  if (strcmp (tz, "GMT")) {
    return -16;
  }
  int d = (year - 1970) * 365 + ((year - 1969) >> 2) + (day - 1);
  if (!(year & 3) && mon >= 2) {
    d++;
  }
  dd[1] = 28;
  for (i = 0; i < mon; i++) { 
    d += dd[i];
  }
  *time = (((d * 24 + hour) * 60 + min) * 60) + sec;
  return 0;
}