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
struct TYPE_6__ {scalar_t__ ContextFlags; } ;
struct TYPE_5__ {TYPE_3__ context; int /*<<< orphan*/  h; } ;
typedef  TYPE_1__ thread_info ;
typedef  int /*<<< orphan*/  ptid_t ;
typedef  enum target_signal { ____Placeholder_target_signal } target_signal ;
struct TYPE_7__ {int /*<<< orphan*/  dwThreadId; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBG_CONTINUE ; 
 int /*<<< orphan*/  DBG_EXCEPTION_NOT_HANDLED ; 
 int /*<<< orphan*/  DEBUG_EXEC (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ NSIG ; 
 int PIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  child_continue (int /*<<< orphan*/ ,int) ; 
 TYPE_4__ current_event ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gdb_stderr ; 
 scalar_t__ last_sig ; 
 int /*<<< orphan*/  set_thread_context (int /*<<< orphan*/ ,TYPE_3__*) ; 
 TYPE_1__* thread_rec (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
child_resume (ptid_t ptid, int step, enum target_signal sig)
{
  thread_info *th;
  DWORD continue_status = last_sig > 0 && last_sig < NSIG ?
  DBG_EXCEPTION_NOT_HANDLED : DBG_CONTINUE;
  int pid = PIDGET (ptid);

  DEBUG_EXEC (("gdb: child_resume (pid=%d, step=%d, sig=%d);\n",
	       pid, step, sig));

  /* Get context for currently selected thread */
  th = thread_rec (current_event.dwThreadId, FALSE);

  if (th->context.ContextFlags)
    {
      CHECK (set_thread_context (th->h, &th->context));
      th->context.ContextFlags = 0;
    }

  /* Allow continuing with the same signal that interrupted us.
     Otherwise complain. */
  if (sig && sig != last_sig)
    fprintf_unfiltered (gdb_stderr, "Can't send signals to the child.  signal %d\n", sig);

  last_sig = 0;
  child_continue (continue_status, pid);
}