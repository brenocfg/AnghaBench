#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ ContextFlags; void* Dr7; void* Dr3; void* Dr2; void* Dr1; void* Dr0; int /*<<< orphan*/  EFlags; } ;
struct TYPE_12__ {TYPE_8__ context; int /*<<< orphan*/  h; } ;
typedef  TYPE_4__ thread_info ;
typedef  int /*<<< orphan*/  ptid_t ;
typedef  enum target_signal { ____Placeholder_target_signal } target_signal ;
struct TYPE_9__ {int ExceptionCode; } ;
struct TYPE_10__ {TYPE_1__ ExceptionRecord; } ;
struct TYPE_11__ {TYPE_2__ Exception; } ;
struct TYPE_14__ {scalar_t__ dwDebugEventCode; int /*<<< orphan*/  dwThreadId; TYPE_3__ u; } ;
struct TYPE_13__ {int them; int us; } ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int /*<<< orphan*/ ) ; 
 scalar_t__ DBG_CONTINUE ; 
 scalar_t__ DBG_EXCEPTION_NOT_HANDLED ; 
 int /*<<< orphan*/  DEBUG_EXCEPT (char*) ; 
 int /*<<< orphan*/  DEBUG_EXEC (char*) ; 
 scalar_t__ EXCEPTION_DEBUG_EVENT ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FLAG_TRACE_BIT ; 
 int PIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PS_REGNUM ; 
 int /*<<< orphan*/  SetThreadContext (int /*<<< orphan*/ ,TYPE_8__*) ; 
 int TARGET_SIGNAL_0 ; 
 int /*<<< orphan*/  child_continue (scalar_t__,int) ; 
 int /*<<< orphan*/  child_fetch_inferior_registers (int /*<<< orphan*/ ) ; 
 TYPE_7__ current_event ; 
 scalar_t__ debug_registers_changed ; 
 void** dr ; 
 int last_sig ; 
 TYPE_4__* thread_rec (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* xlate ; 

void
child_resume (ptid_t ptid, int step, enum target_signal sig)
{
  thread_info *th;
  DWORD continue_status = DBG_CONTINUE;

  int pid = PIDGET (ptid);

  if (sig != TARGET_SIGNAL_0)
    {
      if (current_event.dwDebugEventCode != EXCEPTION_DEBUG_EVENT)
	{
	  DEBUG_EXCEPT(("Cannot continue with signal %d here.\n",sig));
	}
      else if (sig == last_sig)
	continue_status = DBG_EXCEPTION_NOT_HANDLED;
      else
#if 0
/* This code does not seem to work, because
  the kernel does probably not consider changes in the ExceptionRecord
  structure when passing the exception to the inferior.
  Note that this seems possible in the exception handler itself.  */
	{
	  int i;
	  for (i = 0; xlate[i].them != -1; i++)
	    if (xlate[i].us == sig)
	      {
		current_event.u.Exception.ExceptionRecord.ExceptionCode =
		  xlate[i].them;
		continue_status = DBG_EXCEPTION_NOT_HANDLED;
		break;
	      }
	  if (continue_status == DBG_CONTINUE)
	    {
	      DEBUG_EXCEPT(("Cannot continue with signal %d.\n",sig));
	    }
	}
#endif
	DEBUG_EXCEPT(("Can only continue with recieved signal %d.\n",
	  last_sig));
    }

  last_sig = TARGET_SIGNAL_0;

  DEBUG_EXEC (("gdb: child_resume (pid=%d, step=%d, sig=%d);\n",
	       pid, step, sig));

  /* Get context for currently selected thread */
  th = thread_rec (current_event.dwThreadId, FALSE);
  if (th)
    {
      if (step)
	{
	  /* Single step by setting t bit */
	  child_fetch_inferior_registers (PS_REGNUM);
	  th->context.EFlags |= FLAG_TRACE_BIT;
	}

      if (th->context.ContextFlags)
	{
	  if (debug_registers_changed)
	    {
	      th->context.Dr0 = dr[0];
	      th->context.Dr1 = dr[1];
	      th->context.Dr2 = dr[2];
	      th->context.Dr3 = dr[3];
	      /* th->context.Dr6 = dr[6];
	       FIXME: should we set dr6 also ?? */
	      th->context.Dr7 = dr[7];
	    }
	  CHECK (SetThreadContext (th->h, &th->context));
	  th->context.ContextFlags = 0;
	}
    }

  /* Allow continuing with the same signal that interrupted us.
     Otherwise complain. */

  child_continue (continue_status, pid);
}