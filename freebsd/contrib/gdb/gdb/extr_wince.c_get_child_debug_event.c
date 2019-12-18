#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  thread_info ;
struct TYPE_10__ {int /*<<< orphan*/  integer; } ;
struct target_waitstatus {TYPE_3__ value; int /*<<< orphan*/  kind; } ;
struct TYPE_11__ {int /*<<< orphan*/  dwExitCode; } ;
struct TYPE_9__ {int /*<<< orphan*/  hThread; int /*<<< orphan*/  hProcess; } ;
struct TYPE_8__ {int /*<<< orphan*/  hThread; } ;
struct TYPE_12__ {TYPE_4__ ExitProcess; TYPE_2__ CreateProcessInfo; TYPE_1__ CreateThread; } ;
struct TYPE_13__ {int dwDebugEventCode; int dwProcessId; int dwThreadId; TYPE_5__ u; } ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int /*<<< orphan*/ ) ; 
#define  CREATE_PROCESS_DEBUG_EVENT 135 
#define  CREATE_THREAD_DEBUG_EVENT 134 
 int DBG_CONTINUE ; 
 int DBG_EXCEPTION_NOT_HANDLED ; 
 int /*<<< orphan*/  DEBUG_EVENTS (char*) ; 
#define  EXCEPTION_DEBUG_EVENT 133 
#define  EXIT_PROCESS_DEBUG_EVENT 132 
#define  EXIT_THREAD_DEBUG_EVENT 131 
#define  LOAD_DLL_DEBUG_EVENT 130 
#define  OUTPUT_DEBUG_STRING_EVENT 129 
 int PIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RETURN_MASK_ALL ; 
 int /*<<< orphan*/  TARGET_WAITKIND_EXITED ; 
 int /*<<< orphan*/  TRUE ; 
#define  UNLOAD_DLL_DEBUG_EVENT 128 
 int /*<<< orphan*/  catch_errors (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * child_add_thread (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  child_continue (int,int) ; 
 int /*<<< orphan*/  child_delete_thread (int) ; 
 int /*<<< orphan*/  close_handle (int /*<<< orphan*/ ) ; 
 TYPE_6__ current_event ; 
 int /*<<< orphan*/  current_process_handle ; 
 int /*<<< orphan*/  current_thread ; 
 int /*<<< orphan*/  event_count ; 
 int /*<<< orphan*/  handle_exception (struct target_waitstatus*) ; 
 int /*<<< orphan*/  handle_load_dll ; 
 int /*<<< orphan*/  handle_output_debug_string (struct target_waitstatus*) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  info_verbose ; 
 int main_thread_id ; 
 int /*<<< orphan*/  pid_to_ptid (int) ; 
 int /*<<< orphan*/  printf_unfiltered (char*,int,...) ; 
 int /*<<< orphan*/  registers_changed () ; 
 int target_pid_to_str (int) ; 
 int /*<<< orphan*/  this_thread ; 
 int /*<<< orphan*/  thread_rec (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_debug_event (TYPE_6__*,int) ; 

__attribute__((used)) static int
get_child_debug_event (int pid, struct target_waitstatus *ourstatus,
		       DWORD target_event_code, int *retval)
{
  int breakout = 0;
  BOOL debug_event;
  DWORD continue_status, event_code;
  thread_info *th = NULL;
  static thread_info dummy_thread_info;

  if (!(debug_event = wait_for_debug_event (&current_event, 1000)))
    {
      *retval = 0;
      goto out;
    }

  event_count++;
  continue_status = DBG_CONTINUE;
  *retval = 0;

  event_code = current_event.dwDebugEventCode;
  breakout = event_code == target_event_code;

  switch (event_code)
    {
    case CREATE_THREAD_DEBUG_EVENT:
      DEBUG_EVENTS (("gdb: kernel event for pid=%d tid=%x code=%s)\n",
		     (unsigned) current_event.dwProcessId,
		     (unsigned) current_event.dwThreadId,
		     "CREATE_THREAD_DEBUG_EVENT"));
      /* Record the existence of this thread */
      th = child_add_thread (current_event.dwThreadId,
			     current_event.u.CreateThread.hThread);
      if (info_verbose)
	printf_unfiltered ("[New %s]\n",
			   target_pid_to_str (current_event.dwThreadId));
      break;

    case EXIT_THREAD_DEBUG_EVENT:
      DEBUG_EVENTS (("gdb: kernel event for pid=%d tid=%d code=%s)\n",
		     (unsigned) current_event.dwProcessId,
		     (unsigned) current_event.dwThreadId,
		     "EXIT_THREAD_DEBUG_EVENT"));
      child_delete_thread (current_event.dwThreadId);
      th = &dummy_thread_info;
      break;

    case CREATE_PROCESS_DEBUG_EVENT:
      DEBUG_EVENTS (("gdb: kernel event for pid=%d tid=%d code=%s)\n",
		     (unsigned) current_event.dwProcessId,
		     (unsigned) current_event.dwThreadId,
		     "CREATE_PROCESS_DEBUG_EVENT"));
      current_process_handle = current_event.u.CreateProcessInfo.hProcess;

      main_thread_id = current_event.dwThreadId;
      inferior_ptid = pid_to_ptid (main_thread_id);
      /* Add the main thread */
      th = child_add_thread (PIDGET (inferior_ptid),
			     current_event.u.CreateProcessInfo.hThread);
      break;

    case EXIT_PROCESS_DEBUG_EVENT:
      DEBUG_EVENTS (("gdb: kernel event for pid=%d tid=%d code=%s)\n",
		     (unsigned) current_event.dwProcessId,
		     (unsigned) current_event.dwThreadId,
		     "EXIT_PROCESS_DEBUG_EVENT"));
      ourstatus->kind = TARGET_WAITKIND_EXITED;
      ourstatus->value.integer = current_event.u.ExitProcess.dwExitCode;
      close_handle (current_process_handle);
      *retval = current_event.dwProcessId;
      breakout = 1;
      break;

    case LOAD_DLL_DEBUG_EVENT:
      DEBUG_EVENTS (("gdb: kernel event for pid=%d tid=%d code=%s)\n",
		     (unsigned) current_event.dwProcessId,
		     (unsigned) current_event.dwThreadId,
		     "LOAD_DLL_DEBUG_EVENT"));
      catch_errors (handle_load_dll, NULL, (char *) "", RETURN_MASK_ALL);
      registers_changed ();	/* mark all regs invalid */
      break;

    case UNLOAD_DLL_DEBUG_EVENT:
      DEBUG_EVENTS (("gdb: kernel event for pid=%d tid=%d code=%s)\n",
		     (unsigned) current_event.dwProcessId,
		     (unsigned) current_event.dwThreadId,
		     "UNLOAD_DLL_DEBUG_EVENT"));
      break;			/* FIXME: don't know what to do here */

    case EXCEPTION_DEBUG_EVENT:
      DEBUG_EVENTS (("gdb: kernel event for pid=%d tid=%d code=%s)\n",
		     (unsigned) current_event.dwProcessId,
		     (unsigned) current_event.dwThreadId,
		     "EXCEPTION_DEBUG_EVENT"));
      if (handle_exception (ourstatus))
	*retval = current_event.dwThreadId;
      else
	{
	  continue_status = DBG_EXCEPTION_NOT_HANDLED;
	  breakout = 0;
	}
      break;

    case OUTPUT_DEBUG_STRING_EVENT:	/* message from the kernel */
      DEBUG_EVENTS (("gdb: kernel event for pid=%d tid=%d code=%s)\n",
		     (unsigned) current_event.dwProcessId,
		     (unsigned) current_event.dwThreadId,
		     "OUTPUT_DEBUG_STRING_EVENT"));
      handle_output_debug_string ( ourstatus);
      break;
    default:
      printf_unfiltered ("gdb: kernel event for pid=%d tid=%d\n",
			 current_event.dwProcessId,
			 current_event.dwThreadId);
      printf_unfiltered ("                 unknown event code %d\n",
			 current_event.dwDebugEventCode);
      break;
    }

  if (breakout)
    this_thread = current_thread = th ?: thread_rec (current_event.dwThreadId, TRUE);
  else
    CHECK (child_continue (continue_status, -1));

out:
  return breakout;
}