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
typedef  int /*<<< orphan*/  life ;
typedef  int /*<<< orphan*/  acline ;
typedef  int /*<<< orphan*/  ACPresence ;

/* Variables and functions */
 int /*<<< orphan*/  AC_ABSENT ; 
 int /*<<< orphan*/  AC_ERROR ; 
 int /*<<< orphan*/  AC_PRESENT ; 
 int sysctlbyname (char*,int*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void Battery_getData(double* level, ACPresence* isOnAC) {
   int life;
   size_t life_len = sizeof(life);
   if (sysctlbyname("hw.acpi.battery.life", &life, &life_len, NULL, 0) == -1)
      *level = -1;
   else
      *level = life;

   int acline;
   size_t acline_len = sizeof(acline);
   if (sysctlbyname("hw.acpi.acline", &acline, &acline_len, NULL, 0) == -1)
      *isOnAC = AC_ERROR;
   else
      *isOnAC = acline == 0 ? AC_ABSENT : AC_PRESENT;
}