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
typedef  int /*<<< orphan*/  swapused ;
struct xsw_usage {int xsu_total; int xsu_used; } ;
struct TYPE_3__ {int total; int* values; } ;
typedef  TYPE_1__ Meter ;

/* Variables and functions */
 int CTL_VM ; 
 int VM_SWAPUSAGE ; 
 int /*<<< orphan*/  sysctl (int*,int,struct xsw_usage*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void Platform_setSwapValues(Meter* mtr) {
  int mib[2] = {CTL_VM, VM_SWAPUSAGE};
  struct xsw_usage swapused;
  size_t swlen = sizeof(swapused);
  sysctl(mib, 2, &swapused, &swlen, NULL, 0);

  mtr->total = swapused.xsu_total / 1024;
  mtr->values[0] = swapused.xsu_used / 1024;
}