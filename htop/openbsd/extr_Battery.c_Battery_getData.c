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
struct sensordev {int dummy; } ;
struct sensor {double value; } ;
typedef  double ACPresence ;

/* Variables and functions */
 double AC_ERROR ; 
#define  CTL_HW 129 
#define  HW_SENSORS 128 
 int findDevice (char*,int*,struct sensordev*,size_t*) ; 
 int sysctl (int*,int,struct sensor*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void Battery_getData(double* level, ACPresence* isOnAC) {
   static int mib[] = {CTL_HW, HW_SENSORS, 0, 0, 0};
   struct sensor s;
   size_t slen = sizeof(struct sensor);
   struct sensordev snsrdev;
   size_t sdlen = sizeof(struct sensordev);

   bool found = findDevice("acpibat0", mib, &snsrdev, &sdlen);
   
   *level = -1;
   if (found) {
      /* last full capacity */
      mib[3] = 7;
      mib[4] = 0;
      double last_full_capacity = 0;
      if (sysctl(mib, 5, &s, &slen, NULL, 0) != -1) {
         last_full_capacity = s.value;
      }
      if (last_full_capacity > 0) {
         /*  remaining capacity */
         mib[3] = 7;
         mib[4] = 3;
         if (sysctl(mib, 5, &s, &slen, NULL, 0) != -1) {
            double charge = s.value;
            *level = 100*(charge / last_full_capacity);
            if (charge >= last_full_capacity) {
               *level = 100;
            }
         }
      }
   }
   
   found = findDevice("acpiac0", mib, &snsrdev, &sdlen);
   
   *isOnAC = AC_ERROR;
   if (found) {
      mib[3] = 9;
      mib[4] = 0;
      if (sysctl(mib, 5, &s, &slen, NULL, 0) != -1) {
         *isOnAC = s.value;
      }
   }
}