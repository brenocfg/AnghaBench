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
struct TYPE_5__ {scalar_t__ dwDebugEventCode; } ;
struct TYPE_4__ {scalar_t__ h; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  DBG_CONTINUE ; 
 scalar_t__ EXIT_PROCESS_DEBUG_EVENT ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  TerminateProcess (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WaitForDebugEvent (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  child_continue (int /*<<< orphan*/ ,int) ; 
 TYPE_2__ current_event ; 
 scalar_t__ current_process_handle ; 
 TYPE_1__* current_thread ; 
 int /*<<< orphan*/  target_mourn_inferior () ; 

void
child_kill_inferior (void)
{
  CHECK (TerminateProcess (current_process_handle, 0));

  for (;;)
    {
      if (!child_continue (DBG_CONTINUE, -1))
	break;
      if (!WaitForDebugEvent (&current_event, INFINITE))
	break;
      if (current_event.dwDebugEventCode == EXIT_PROCESS_DEBUG_EVENT)
	break;
    }

  CHECK (CloseHandle (current_process_handle));

  /* this may fail in an attached process so don't check. */
  if (current_thread && current_thread->h)
    (void) CloseHandle (current_thread->h);
  target_mourn_inferior ();	/* or just child_mourn_inferior? */
}