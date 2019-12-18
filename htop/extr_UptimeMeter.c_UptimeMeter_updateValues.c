#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  daysbuf ;
struct TYPE_3__ {int* values; int total; } ;
typedef  TYPE_1__ Meter ;

/* Variables and functions */
 int Platform_getUptime () ; 
 int /*<<< orphan*/  xSnprintf (char*,int,char*,...) ; 

__attribute__((used)) static void UptimeMeter_updateValues(Meter* this, char* buffer, int len) {
   int totalseconds = Platform_getUptime();
   if (totalseconds == -1) {
      xSnprintf(buffer, len, "(unknown)");
      return;
   }
   int seconds = totalseconds % 60;
   int minutes = (totalseconds/60) % 60;
   int hours = (totalseconds/3600) % 24;
   int days = (totalseconds/86400);
   this->values[0] = days;
   if (days > this->total) {
      this->total = days;
   }
   char daysbuf[32];
   if (days > 100) {
      xSnprintf(daysbuf, sizeof(daysbuf), "%d days(!), ", days);
   } else if (days > 1) {
      xSnprintf(daysbuf, sizeof(daysbuf), "%d days, ", days);
   } else if (days == 1) {
      xSnprintf(daysbuf, sizeof(daysbuf), "1 day, ");
   } else {
      daysbuf[0] = '\0';
   }
   xSnprintf(buffer, len, "%s%02d:%02d:%02d", daysbuf, hours, minutes, seconds);
}