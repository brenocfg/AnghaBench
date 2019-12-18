#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int tv_sec; } ;
struct utmpx {TYPE_1__ ut_tv; int /*<<< orphan*/  ut_line; } ;

/* Variables and functions */
 int /*<<< orphan*/  endutxent () ; 
 struct utmpx* getutxent () ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 
 int time (int /*<<< orphan*/ *) ; 

int Platform_getUptime() {
   int boot_time = 0;
   int curr_time = time(NULL);   
   struct utmpx * ent;

   while (( ent = getutxent() )) {
      if ( !strcmp("system boot", ent->ut_line )) {
         boot_time = ent->ut_tv.tv_sec;
      }
   }

   endutxent();

   return (curr_time-boot_time);
}