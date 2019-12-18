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
struct TYPE_2__ {int (* to_region_size_ok_for_hw_watchpoint ) (int) ;} ;
typedef  int CORE_ADDR ;

/* Variables and functions */
 TYPE_1__ debug_target ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 int stub1 (int) ; 

__attribute__((used)) static int
debug_to_region_size_ok_for_hw_watchpoint (int byte_count)
{
  CORE_ADDR retval;

  retval = debug_target.to_region_size_ok_for_hw_watchpoint (byte_count);

  fprintf_unfiltered (gdb_stdlog,
		      "TARGET_REGION_SIZE_OK_FOR_HW_WATCHPOINT (%ld) = 0x%lx\n",
		      (unsigned long) byte_count,
		      (unsigned long) retval);
  return retval;
}