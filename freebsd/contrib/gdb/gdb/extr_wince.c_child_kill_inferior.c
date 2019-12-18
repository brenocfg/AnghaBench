#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  h; } ;
struct TYPE_4__ {scalar_t__ dwDebugEventCode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBG_CONTINUE ; 
 scalar_t__ EXIT_PROCESS_DEBUG_EVENT ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  child_continue (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  close_handle (int /*<<< orphan*/ ) ; 
 TYPE_1__ current_event ; 
 int /*<<< orphan*/  current_process_handle ; 
 TYPE_2__* current_thread ; 
 int /*<<< orphan*/  target_mourn_inferior () ; 
 int /*<<< orphan*/  terminate_process (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_debug_event (TYPE_1__*,int /*<<< orphan*/ ) ; 

void
child_kill_inferior (void)
{
  CHECK (terminate_process (current_process_handle));

  for (;;)
    {
      if (!child_continue (DBG_CONTINUE, -1))
	break;
      if (!wait_for_debug_event (&current_event, INFINITE))
	break;
      if (current_event.dwDebugEventCode == EXIT_PROCESS_DEBUG_EVENT)
	break;
    }

  CHECK (close_handle (current_process_handle));
  close_handle (current_thread->h);
  target_mourn_inferior ();	/* or just child_mourn_inferior? */
}