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
struct TYPE_2__ {int (* to_insert_breakpoint ) (scalar_t__,char*) ;} ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 TYPE_1__ debug_target ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 int stub1 (scalar_t__,char*) ; 

__attribute__((used)) static int
debug_to_insert_breakpoint (CORE_ADDR addr, char *save)
{
  int retval;

  retval = debug_target.to_insert_breakpoint (addr, save);

  fprintf_unfiltered (gdb_stdlog,
		      "target_insert_breakpoint (0x%lx, xxx) = %ld\n",
		      (unsigned long) addr,
		      (unsigned long) retval);
  return retval;
}