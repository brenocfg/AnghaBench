#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  delete_op ; 
 int /*<<< orphan*/  dont_repeat () ; 
 int /*<<< orphan*/  map_args_over_tracepoints (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  query (char*) ; 
 scalar_t__ tracepoint_chain ; 

__attribute__((used)) static void
delete_trace_command (char *args, int from_tty)
{
  dont_repeat ();
  if (!args || !*args)		/* No args implies all tracepoints; */
    if (from_tty)		/* confirm only if from_tty... */
      if (tracepoint_chain)	/* and if there are tracepoints to delete! */
	if (!query ("Delete all tracepoints? "))
	  return;

  map_args_over_tracepoints (args, from_tty, delete_op);
}