#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* settings; } ;
struct TYPE_3__ {int direction; int sortKey; } ;
typedef  TYPE_1__ Settings ;
typedef  TYPE_2__ Process ;
typedef  int /*<<< orphan*/  OpenBSDProcess ;

/* Variables and functions */
 long Process_compare (void const*,void const*) ; 

long OpenBSDProcess_compare(const void* v1, const void* v2) {
   OpenBSDProcess *p1, *p2;
   Settings *settings = ((Process*)v1)->settings;
   if (settings->direction == 1) {
      p1 = (OpenBSDProcess*)v1;
      p2 = (OpenBSDProcess*)v2;
   } else {
      p2 = (OpenBSDProcess*)v1;
      p1 = (OpenBSDProcess*)v2;
   }
   switch (settings->sortKey) {
   // add OpenBSD-specific fields here
   default:
      return Process_compare(v1, v2);
   }
}