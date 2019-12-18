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
typedef  scalar_t__ time_t ;
typedef  int /*<<< orphan*/  ACPresence ;

/* Variables and functions */
 int /*<<< orphan*/  AC_ERROR ; 
 scalar_t__ BAT_ERR ; 
 scalar_t__ BAT_PROC ; 
 scalar_t__ BAT_SYS ; 
 int /*<<< orphan*/  Battery_cacheIsOnAC ; 
 double Battery_cacheLevel ; 
 scalar_t__ Battery_cacheTime ; 
 int /*<<< orphan*/  Battery_getProcData (double*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Battery_getSysData (double*,int /*<<< orphan*/ *) ; 
 scalar_t__ Battery_method ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

void Battery_getData(double* level, ACPresence* isOnAC) {
   time_t now = time(NULL);
   // update battery reading is slow. Update it each 10 seconds only.
   if (now < Battery_cacheTime + 10) {
      *level = Battery_cacheLevel;
      *isOnAC = Battery_cacheIsOnAC;
      return;
   }

   if (Battery_method == BAT_PROC) {
      Battery_getProcData(level, isOnAC);
      if (*level == 0) {
         Battery_method = BAT_SYS;
      }
   }
   if (Battery_method == BAT_SYS) {
      Battery_getSysData(level, isOnAC);
      if (*level == 0) {
         Battery_method = BAT_ERR;
      }
   }
   if (Battery_method == BAT_ERR) {
      *level = -1;
      *isOnAC = AC_ERROR;
   }
   if (*level > 100.0) {
      *level = 100.0;
   }
   Battery_cacheLevel = *level;
   Battery_cacheIsOnAC = *isOnAC;
   Battery_cacheTime = now;
}