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
typedef  int /*<<< orphan*/ * CFTypeRef ;
typedef  scalar_t__ CFStringRef ;
typedef  int /*<<< orphan*/ * CFDictionaryRef ;
typedef  int /*<<< orphan*/ * CFArrayRef ;
typedef  int /*<<< orphan*/  ACPresence ;

/* Variables and functions */
 int /*<<< orphan*/  AC_ABSENT ; 
 int /*<<< orphan*/  AC_ERROR ; 
 int /*<<< orphan*/  AC_PRESENT ; 
 int CFArrayGetCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CFArrayGetValueAtIndex (int /*<<< orphan*/ *,int) ; 
 scalar_t__ CFDictionaryGetValue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFNumberGetValue (scalar_t__,int /*<<< orphan*/ ,double*) ; 
 int /*<<< orphan*/  CFRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CFRetain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CFSTR (int /*<<< orphan*/ ) ; 
 scalar_t__ CFStringCompare (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * IOPSCopyPowerSourcesInfo () ; 
 int /*<<< orphan*/ * IOPSCopyPowerSourcesList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * IOPSGetPowerSourceDescription (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ kCFCompareEqualTo ; 
 int /*<<< orphan*/  kCFNumberDoubleType ; 
 int /*<<< orphan*/  kIOPSACPowerValue ; 
 int /*<<< orphan*/  kIOPSCurrentCapacityKey ; 
 int /*<<< orphan*/  kIOPSInternalType ; 
 int /*<<< orphan*/  kIOPSMaxCapacityKey ; 
 int /*<<< orphan*/  kIOPSPowerSourceStateKey ; 
 int /*<<< orphan*/  kIOPSTransportTypeKey ; 

void Battery_getData(double* level, ACPresence* isOnAC) {
   CFTypeRef power_sources = IOPSCopyPowerSourcesInfo();

   *level = -1;
   *isOnAC = AC_ERROR;

   if(NULL == power_sources) {
      return;
   }

   if(power_sources != NULL) {
      CFArrayRef list = IOPSCopyPowerSourcesList(power_sources);
      CFDictionaryRef battery = NULL;
      int len;

      if(NULL == list) {
         CFRelease(power_sources);

         return;
      }

      len = CFArrayGetCount(list);

      /* Get the battery */
      for(int i = 0; i < len && battery == NULL; ++i) {
         CFDictionaryRef candidate = IOPSGetPowerSourceDescription(power_sources,
                                     CFArrayGetValueAtIndex(list, i)); /* GET rule */
         CFStringRef type;

         if(NULL != candidate) {
            type = (CFStringRef) CFDictionaryGetValue(candidate,
                   CFSTR(kIOPSTransportTypeKey)); /* GET rule */

            if(kCFCompareEqualTo == CFStringCompare(type, CFSTR(kIOPSInternalType), 0)) {
               CFRetain(candidate);
               battery = candidate;
            }
         }
      }

      if(NULL != battery) {
         /* Determine the AC state */
         CFStringRef power_state = CFDictionaryGetValue(battery, CFSTR(kIOPSPowerSourceStateKey));

         *isOnAC = (kCFCompareEqualTo == CFStringCompare(power_state, CFSTR(kIOPSACPowerValue), 0))
                 ? AC_PRESENT
                 : AC_ABSENT;

         /* Get the percentage remaining */
         double current;
         double max;

         CFNumberGetValue(CFDictionaryGetValue(battery, CFSTR(kIOPSCurrentCapacityKey)),
                 kCFNumberDoubleType, &current);
         CFNumberGetValue(CFDictionaryGetValue(battery, CFSTR(kIOPSMaxCapacityKey)),
                 kCFNumberDoubleType, &max);

         *level = (current * 100.0) / max;

         CFRelease(battery);
      }

      CFRelease(list);
      CFRelease(power_sources);
   }
}