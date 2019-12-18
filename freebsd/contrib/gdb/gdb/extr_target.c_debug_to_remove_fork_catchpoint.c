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
struct TYPE_2__ {int (* to_remove_fork_catchpoint ) (int) ;} ;

/* Variables and functions */
 TYPE_1__ debug_target ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 int stub1 (int) ; 

__attribute__((used)) static int
debug_to_remove_fork_catchpoint (int pid)
{
  int retval;

  retval = debug_target.to_remove_fork_catchpoint (pid);

  fprintf_unfiltered (gdb_stdlog, "target_remove_fork_catchpoint (%d) = %d\n",
		      pid, retval);

  return retval;
}