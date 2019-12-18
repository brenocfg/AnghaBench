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
struct TYPE_4__ {scalar_t__ pid; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* to_mourn_inferior ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  keep_thread_db ; 
 TYPE_2__ proc_handle ; 
 int /*<<< orphan*/  remove_thread_event_breakpoints () ; 
 int /*<<< orphan*/  stub1 () ; 
 TYPE_1__* target_beneath ; 
 int /*<<< orphan*/  thread_db_ops ; 
 int /*<<< orphan*/  unpush_target (int /*<<< orphan*/ *) ; 
 scalar_t__ using_thread_db ; 

__attribute__((used)) static void
thread_db_mourn_inferior (void)
{
  remove_thread_event_breakpoints ();

  /* Forget about the child's process ID.  We shouldn't need it
     anymore.  */
  proc_handle.pid = 0;

  target_beneath->to_mourn_inferior ();

  /* Detach thread_db target ops if not dealing with a statically
     linked threaded program.  This allows a corefile to be debugged
     after finishing debugging of a threaded program.  At present,
     debugging a statically-linked threaded program is broken, but
     the check is added below in the event that it is fixed in the
     future.  */
  if (!keep_thread_db)
    {
      unpush_target (&thread_db_ops);
      using_thread_db = 0;
    }
}