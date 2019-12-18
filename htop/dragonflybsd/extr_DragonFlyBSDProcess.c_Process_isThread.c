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
struct TYPE_2__ {int kernel; } ;
typedef  int /*<<< orphan*/  Process ;
typedef  TYPE_1__ DragonFlyBSDProcess ;

/* Variables and functions */
 int Process_isUserlandThread (int /*<<< orphan*/ *) ; 

bool Process_isThread(Process* this) {
   DragonFlyBSDProcess* fp = (DragonFlyBSDProcess*) this;

   if (fp->kernel == 1 )
      return 1;
   else
      return (Process_isUserlandThread(this));
}