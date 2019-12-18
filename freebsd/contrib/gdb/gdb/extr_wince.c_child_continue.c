#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int id; int suspend_count; int /*<<< orphan*/  h; struct TYPE_4__* next; } ;
typedef  TYPE_1__ thread_info ;
struct TYPE_5__ {scalar_t__ dwThreadId; scalar_t__ dwProcessId; } ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_EVENTS (char*) ; 
 scalar_t__ continue_debug_event (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_3__ current_event ; 
 int /*<<< orphan*/  resume_thread (int /*<<< orphan*/ ) ; 
 TYPE_1__ thread_head ; 

__attribute__((used)) static BOOL
child_continue (DWORD continue_status, int id)
{
  int i;
  thread_info *th;
  BOOL res;

  DEBUG_EVENTS (("ContinueDebugEvent (cpid=%d, ctid=%d, DBG_CONTINUE);\n",
		 (unsigned) current_event.dwProcessId, (unsigned) current_event.dwThreadId));
  res = continue_debug_event (current_event.dwProcessId,
			      current_event.dwThreadId,
			      continue_status);
  if (res)
    for (th = &thread_head; (th = th->next) != NULL;)
      if (((id == -1) || (id == th->id)) && th->suspend_count)
	{
	  for (i = 0; i < th->suspend_count; i++)
	    (void) resume_thread (th->h);
	  th->suspend_count = 0;
	}

  return res;
}