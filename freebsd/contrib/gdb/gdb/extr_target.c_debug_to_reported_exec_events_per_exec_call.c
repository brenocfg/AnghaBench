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
struct TYPE_2__ {int (* to_reported_exec_events_per_exec_call ) () ;} ;

/* Variables and functions */
 TYPE_1__ debug_target ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 int stub1 () ; 

__attribute__((used)) static int
debug_to_reported_exec_events_per_exec_call (void)
{
  int reported_exec_events;

  reported_exec_events = debug_target.to_reported_exec_events_per_exec_call ();

  fprintf_unfiltered (gdb_stdlog,
		      "target_reported_exec_events_per_exec_call () = %d\n",
		      reported_exec_events);

  return reported_exec_events;
}