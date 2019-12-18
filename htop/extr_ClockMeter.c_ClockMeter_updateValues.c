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
typedef  int /*<<< orphan*/  time_t ;
struct tm {int tm_hour; scalar_t__ tm_min; } ;
struct TYPE_3__ {scalar_t__* values; } ;
typedef  TYPE_1__ Meter ;

/* Variables and functions */
 struct tm* localtime_r (int /*<<< orphan*/ *,struct tm*) ; 
 int /*<<< orphan*/  strftime (char*,int,char*,struct tm*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ClockMeter_updateValues(Meter* this, char* buffer, int size) {
   time_t t = time(NULL);
   struct tm result;
   struct tm *lt = localtime_r(&t, &result);
   this->values[0] = lt->tm_hour * 60 + lt->tm_min;
   strftime(buffer, size, "%H:%M:%S", lt);
}