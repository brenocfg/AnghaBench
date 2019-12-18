#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {long jid; char* jname; } ;
struct TYPE_5__ {TYPE_1__* settings; } ;
struct TYPE_4__ {int direction; scalar_t__ sortKey; } ;
typedef  TYPE_1__ Settings ;
typedef  TYPE_2__ Process ;
typedef  TYPE_3__ DragonFlyBSDProcess ;

/* Variables and functions */
#define  JAIL 129 
#define  JID 128 
 long Process_compare (void const*,void const*) ; 
 long strcmp (char*,char*) ; 

long DragonFlyBSDProcess_compare(const void* v1, const void* v2) {
   DragonFlyBSDProcess *p1, *p2;
   Settings *settings = ((Process*)v1)->settings;
   if (settings->direction == 1) {
      p1 = (DragonFlyBSDProcess*)v1;
      p2 = (DragonFlyBSDProcess*)v2;
   } else {
      p2 = (DragonFlyBSDProcess*)v1;
      p1 = (DragonFlyBSDProcess*)v2;
   }
   switch ((int) settings->sortKey) {
   // add Platform-specific fields here
   case JID:
      return (p1->jid - p2->jid);
   case JAIL:
      return strcmp(p1->jname ? p1->jname : "", p2->jname ? p2->jname : "");
   default:
      return Process_compare(v1, v2);
   }
}