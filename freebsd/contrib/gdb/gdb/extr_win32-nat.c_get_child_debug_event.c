#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  thread_info ;
struct TYPE_14__ {int related_pid; int /*<<< orphan*/  integer; } ;
struct target_waitstatus {TYPE_6__ value; int /*<<< orphan*/  kind; } ;
struct TYPE_12__ {int /*<<< orphan*/  hFile; } ;
struct TYPE_11__ {int /*<<< orphan*/  dwExitCode; } ;
struct TYPE_10__ {int /*<<< orphan*/  hThread; int /*<<< orphan*/  hProcess; int /*<<< orphan*/  hFile; } ;
struct TYPE_9__ {int /*<<< orphan*/  hThread; } ;
struct TYPE_13__ {TYPE_4__ LoadDll; TYPE_3__ ExitProcess; TYPE_2__ CreateProcessInfo; TYPE_1__ CreateThread; } ;
struct TYPE_15__ {int dwDebugEventCode; int dwThreadId; int /*<<< orphan*/  dwProcessId; TYPE_5__ u; } ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int /*<<< orphan*/ ) ; 
#define  CREATE_PROCESS_DEBUG_EVENT 135 
#define  CREATE_THREAD_DEBUG_EVENT 134 
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int DBG_CONTINUE ; 
 int /*<<< orphan*/  DEBUG_EVENTS (char*) ; 
#define  EXCEPTION_DEBUG_EVENT 133 
#define  EXIT_PROCESS_DEBUG_EVENT 132 
#define  EXIT_THREAD_DEBUG_EVENT 131 
#define  LOAD_DLL_DEBUG_EVENT 130 
#define  OUTPUT_DEBUG_STRING_EVENT 129 
 int /*<<< orphan*/  RETURN_MASK_ALL ; 
 int /*<<< orphan*/  TARGET_SIGNAL_0 ; 
 int /*<<< orphan*/  TARGET_WAITKIND_EXITED ; 
 int /*<<< orphan*/  TARGET_WAITKIND_LOADED ; 
 int /*<<< orphan*/  TARGET_WAITKIND_SPURIOUS ; 
 int /*<<< orphan*/  TRUE ; 
#define  UNLOAD_DLL_DEBUG_EVENT 128 
 int /*<<< orphan*/  WaitForDebugEvent (TYPE_7__*,int) ; 
 int /*<<< orphan*/  attach_flag ; 
 int /*<<< orphan*/  catch_errors (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * child_add_thread (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  child_continue (int,int) ; 
 int /*<<< orphan*/  child_delete_thread (int) ; 
 TYPE_7__ current_event ; 
 int /*<<< orphan*/  current_process_handle ; 
 int /*<<< orphan*/  current_thread ; 
 int /*<<< orphan*/  event_count ; 
 int fake_create_process () ; 
 int /*<<< orphan*/  handle_exception (struct target_waitstatus*) ; 
 int /*<<< orphan*/  handle_load_dll ; 
 int /*<<< orphan*/  handle_output_debug_string (struct target_waitstatus*) ; 
 int /*<<< orphan*/  handle_unload_dll ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  info_verbose ; 
 int /*<<< orphan*/  last_sig ; 
 int main_thread_id ; 
 int /*<<< orphan*/  pid_to_ptid (int) ; 
 int /*<<< orphan*/  printf_unfiltered (char*,int,...) ; 
 int /*<<< orphan*/  re_enable_breakpoints_in_shlibs () ; 
 int /*<<< orphan*/  registers_changed () ; 
 int saw_create ; 
 int target_pid_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_rec (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
get_child_debug_event (int pid, struct target_waitstatus *ourstatus)
{
  BOOL debug_event;
  DWORD continue_status, event_code;
  thread_info *th;
  static thread_info dummy_thread_info;
  int retval = 0;

  last_sig = TARGET_SIGNAL_0;

  if (!(debug_event = WaitForDebugEvent (&current_event, 1000)))
    goto out;

  event_count++;
  continue_status = DBG_CONTINUE;

  event_code = current_event.dwDebugEventCode;
  ourstatus->kind = TARGET_WAITKIND_SPURIOUS;
  th = NULL;

  switch (event_code)
    {
    case CREATE_THREAD_DEBUG_EVENT:
      DEBUG_EVENTS (("gdb: kernel event for pid=%d tid=%x code=%s)\n",
		     (unsigned) current_event.dwProcessId,
		     (unsigned) current_event.dwThreadId,
		     "CREATE_THREAD_DEBUG_EVENT"));
      if (saw_create != 1)
	{
	  if (!saw_create && attach_flag)
	    {
	      /* Kludge around a Windows bug where first event is a create
		 thread event.  Caused when attached process does not have
		 a main thread. */
	      retval = ourstatus->value.related_pid = fake_create_process ();
	      saw_create++;
	    }
	  break;
	}
      /* Record the existence of this thread */
      th = child_add_thread (current_event.dwThreadId,
			     current_event.u.CreateThread.hThread);
      if (info_verbose)
	printf_unfiltered ("[New %s]\n",
			   target_pid_to_str (
			     pid_to_ptid (current_event.dwThreadId)));
      retval = current_event.dwThreadId;
      break;

    case EXIT_THREAD_DEBUG_EVENT:
      DEBUG_EVENTS (("gdb: kernel event for pid=%d tid=%d code=%s)\n",
		     (unsigned) current_event.dwProcessId,
		     (unsigned) current_event.dwThreadId,
		     "EXIT_THREAD_DEBUG_EVENT"));
      if (current_event.dwThreadId != main_thread_id)
	{
	  child_delete_thread (current_event.dwThreadId);
	  th = &dummy_thread_info;
	}
      break;

    case CREATE_PROCESS_DEBUG_EVENT:
      DEBUG_EVENTS (("gdb: kernel event for pid=%d tid=%d code=%s)\n",
		     (unsigned) current_event.dwProcessId,
		     (unsigned) current_event.dwThreadId,
		     "CREATE_PROCESS_DEBUG_EVENT"));
      CloseHandle (current_event.u.CreateProcessInfo.hFile);
      if (++saw_create != 1)
	{
	  CloseHandle (current_event.u.CreateProcessInfo.hProcess);
	  break;
	}

      current_process_handle = current_event.u.CreateProcessInfo.hProcess;
      if (main_thread_id)
	child_delete_thread (main_thread_id);
      main_thread_id = current_event.dwThreadId;
      /* Add the main thread */
      th = child_add_thread (main_thread_id,
			     current_event.u.CreateProcessInfo.hThread);
      retval = ourstatus->value.related_pid = current_event.dwThreadId;
      break;

    case EXIT_PROCESS_DEBUG_EVENT:
      DEBUG_EVENTS (("gdb: kernel event for pid=%d tid=%d code=%s)\n",
		     (unsigned) current_event.dwProcessId,
		     (unsigned) current_event.dwThreadId,
		     "EXIT_PROCESS_DEBUG_EVENT"));
      if (saw_create != 1)
	break;
      ourstatus->kind = TARGET_WAITKIND_EXITED;
      ourstatus->value.integer = current_event.u.ExitProcess.dwExitCode;
      CloseHandle (current_process_handle);
      retval = main_thread_id;
      break;

    case LOAD_DLL_DEBUG_EVENT:
      DEBUG_EVENTS (("gdb: kernel event for pid=%d tid=%d code=%s)\n",
		     (unsigned) current_event.dwProcessId,
		     (unsigned) current_event.dwThreadId,
		     "LOAD_DLL_DEBUG_EVENT"));
      CloseHandle (current_event.u.LoadDll.hFile);
      if (saw_create != 1)
	break;
      catch_errors (handle_load_dll, NULL, (char *) "", RETURN_MASK_ALL);
      registers_changed ();	/* mark all regs invalid */
      ourstatus->kind = TARGET_WAITKIND_LOADED;
      ourstatus->value.integer = 0;
      retval = main_thread_id;
      re_enable_breakpoints_in_shlibs ();
      break;

    case UNLOAD_DLL_DEBUG_EVENT:
      DEBUG_EVENTS (("gdb: kernel event for pid=%d tid=%d code=%s)\n",
		     (unsigned) current_event.dwProcessId,
		     (unsigned) current_event.dwThreadId,
		     "UNLOAD_DLL_DEBUG_EVENT"));
      if (saw_create != 1)
	break;
      catch_errors (handle_unload_dll, NULL, (char *) "", RETURN_MASK_ALL);
      registers_changed ();	/* mark all regs invalid */
      /* ourstatus->kind = TARGET_WAITKIND_UNLOADED;
	 does not exist yet. */
      break;

    case EXCEPTION_DEBUG_EVENT:
      DEBUG_EVENTS (("gdb: kernel event for pid=%d tid=%d code=%s)\n",
		     (unsigned) current_event.dwProcessId,
		     (unsigned) current_event.dwThreadId,
		     "EXCEPTION_DEBUG_EVENT"));
      if (saw_create != 1)
	break;
      if (handle_exception (ourstatus))
	retval = current_event.dwThreadId;
      break;

    case OUTPUT_DEBUG_STRING_EVENT:	/* message from the kernel */
      DEBUG_EVENTS (("gdb: kernel event for pid=%d tid=%d code=%s)\n",
		     (unsigned) current_event.dwProcessId,
		     (unsigned) current_event.dwThreadId,
		     "OUTPUT_DEBUG_STRING_EVENT"));
      if (saw_create != 1)
	break;
      if (handle_output_debug_string (ourstatus))
	retval = main_thread_id;
      break;

    default:
      if (saw_create != 1)
	break;
      printf_unfiltered ("gdb: kernel event for pid=%ld tid=%ld\n",
			 (DWORD) current_event.dwProcessId,
			 (DWORD) current_event.dwThreadId);
      printf_unfiltered ("                 unknown event code %ld\n",
			 current_event.dwDebugEventCode);
      break;
    }

  if (!retval || saw_create != 1)
    CHECK (child_continue (continue_status, -1));
  else
    {
      inferior_ptid = pid_to_ptid (retval);
      current_thread = th ?: thread_rec (current_event.dwThreadId, TRUE);
    }

out:
  return retval;
}