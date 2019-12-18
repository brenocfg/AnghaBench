#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ ContextFlags; void* Dr7; void* Dr3; void* Dr2; void* Dr1; void* Dr0; } ;
struct TYPE_5__ {int suspend_count; TYPE_4__ context; int /*<<< orphan*/  h; scalar_t__ id; struct TYPE_5__* next; } ;
typedef  TYPE_1__ thread_info ;
struct TYPE_6__ {int /*<<< orphan*/  dwThreadId; int /*<<< orphan*/  dwProcessId; } ;
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int /*<<< orphan*/ ) ; 
 scalar_t__ CONTEXT_DEBUG_REGISTERS ; 
 scalar_t__ ContinueDebugEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ DBG_CONTINUE ; 
 int /*<<< orphan*/  DEBUG_EVENTS (char*) ; 
 int /*<<< orphan*/  ResumeThread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetThreadContext (int /*<<< orphan*/ ,TYPE_4__*) ; 
 TYPE_3__ current_event ; 
 scalar_t__ debug_registers_changed ; 
 void** dr ; 
 TYPE_1__ thread_head ; 

__attribute__((used)) static BOOL
child_continue (DWORD continue_status, int id)
{
  int i;
  thread_info *th;
  BOOL res;

  DEBUG_EVENTS (("ContinueDebugEvent (cpid=%ld, ctid=%ld, %s);\n",
		  current_event.dwProcessId, current_event.dwThreadId,
		  continue_status == DBG_CONTINUE ?
		  "DBG_CONTINUE" : "DBG_EXCEPTION_NOT_HANDLED"));
  res = ContinueDebugEvent (current_event.dwProcessId,
			    current_event.dwThreadId,
			    continue_status);
  continue_status = 0;
  if (res)
    for (th = &thread_head; (th = th->next) != NULL;)
      if (((id == -1) || (id == (int) th->id)) && th->suspend_count)
	{

	  for (i = 0; i < th->suspend_count; i++)
	    (void) ResumeThread (th->h);
	  th->suspend_count = 0;
	  if (debug_registers_changed)
	    {
	      /* Only change the value of the debug registers */
	      th->context.ContextFlags = CONTEXT_DEBUG_REGISTERS;
	      th->context.Dr0 = dr[0];
	      th->context.Dr1 = dr[1];
	      th->context.Dr2 = dr[2];
	      th->context.Dr3 = dr[3];
	      /* th->context.Dr6 = dr[6];
		 FIXME: should we set dr6 also ?? */
	      th->context.Dr7 = dr[7];
	      CHECK (SetThreadContext (th->h, &th->context));
	      th->context.ContextFlags = 0;
	    }
	}

  debug_registers_changed = 0;
  return res;
}