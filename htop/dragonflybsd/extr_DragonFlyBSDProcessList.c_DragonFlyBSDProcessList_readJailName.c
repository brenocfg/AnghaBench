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
struct TYPE_3__ {scalar_t__ jails; } ;
typedef  TYPE_1__ DragonFlyBSDProcessList ;

/* Variables and functions */
 scalar_t__ Hashtable_get (scalar_t__,int) ; 
 char* xStrdup (char*) ; 

char* DragonFlyBSDProcessList_readJailName(DragonFlyBSDProcessList* dfpl, int jailid) {
   char*  hostname;
   char*  jname;

   if (jailid != 0 && dfpl->jails && (hostname = (char *)Hashtable_get(dfpl->jails, jailid))) {
      jname = xStrdup(hostname);
   } else {
      jname = xStrdup("-");
   }
   return jname;
}