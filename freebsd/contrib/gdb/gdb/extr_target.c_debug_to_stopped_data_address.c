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
struct TYPE_2__ {scalar_t__ (* to_stopped_data_address ) () ;} ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 TYPE_1__ debug_target ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,unsigned long) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 scalar_t__ stub1 () ; 

__attribute__((used)) static CORE_ADDR
debug_to_stopped_data_address (void)
{
  CORE_ADDR retval;

  retval = debug_target.to_stopped_data_address ();

  fprintf_unfiltered (gdb_stdlog,
		      "target_stopped_data_address () = 0x%lx\n",
		      (unsigned long) retval);
  return retval;
}