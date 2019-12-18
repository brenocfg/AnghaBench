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
typedef  int /*<<< orphan*/  id ;
typedef  int gdb_wince_id ;
typedef  int /*<<< orphan*/  WCHAR ;

/* Variables and functions */
#define  GDB_CLOSEHANDLE 141 
#define  GDB_CONTINUEDEBUGEVENT 140 
#define  GDB_CREATEPROCESS 139 
#define  GDB_GETTHREADCONTEXT 138 
#define  GDB_READPROCESSMEMORY 137 
#define  GDB_RESUMETHREAD 136 
#define  GDB_SETTHREADCONTEXT 135 
#define  GDB_SINGLESTEP 134 
#define  GDB_STOPSTUB 133 
#define  GDB_SUSPENDTHREAD 132 
#define  GDB_TERMINATEPROCESS 131 
#define  GDB_THREADALIVE 130 
#define  GDB_WAITFORDEBUGEVENT 129 
#define  GDB_WRITEPROCESSMEMORY 128 
 int /*<<< orphan*/  MB_ICONERROR ; 
 int /*<<< orphan*/  MessageBoxW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close_handle (int) ; 
 int /*<<< orphan*/  continue_debug_event (int) ; 
 int /*<<< orphan*/  create_process (int) ; 
 int /*<<< orphan*/  flag_single_step (int) ; 
 int /*<<< orphan*/  get_thread_context (int) ; 
 int /*<<< orphan*/  read_process_memory (int) ; 
 int /*<<< orphan*/  resume_thread (int) ; 
 int /*<<< orphan*/  set_thread_context (int) ; 
 int skip_next_id ; 
 scalar_t__ sockread (char*,int,int*,int) ; 
 int /*<<< orphan*/  suspend_thread (int) ; 
 int /*<<< orphan*/  terminate_process (int) ; 
 int /*<<< orphan*/  thread_alive (int) ; 
 int /*<<< orphan*/  wait_for_debug_event (int) ; 
 int /*<<< orphan*/  write_process_memory (int) ; 
 int /*<<< orphan*/  wsprintfW (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void
dispatch (int s)
{
  gdb_wince_id id;

  /* Continue reading from socket until receive a GDB_STOPSUB. */
  while (sockread (L"Dispatch", s, &id, sizeof (id)) > 0)
    {
      skip_next_id = 1;
      switch (id)
	{
	case GDB_CREATEPROCESS:
	  create_process (s);
	  break;
	case GDB_TERMINATEPROCESS:
	  terminate_process (s);
	  break;
	case GDB_WAITFORDEBUGEVENT:
	  wait_for_debug_event (s);
	  break;
	case GDB_GETTHREADCONTEXT:
	  get_thread_context (s);
	  break;
	case GDB_SETTHREADCONTEXT:
	  set_thread_context (s);
	  break;
	case GDB_READPROCESSMEMORY:
	  read_process_memory (s);
	  break;
	case GDB_WRITEPROCESSMEMORY:
	  write_process_memory (s);
	  break;
	case GDB_THREADALIVE:
	  thread_alive (s);
	  break;
	case GDB_SUSPENDTHREAD:
	  suspend_thread (s);
	  break;
	case GDB_RESUMETHREAD:
	  resume_thread (s);
	  break;
	case GDB_CONTINUEDEBUGEVENT:
	  continue_debug_event (s);
	  break;
	case GDB_CLOSEHANDLE:
	  close_handle (s);
	  break;
	case GDB_STOPSTUB:
	  terminate_process (s);
	  return;
	case GDB_SINGLESTEP:
	  flag_single_step (s);
	  break;
	default:
	  {
	    WCHAR buf[80];
	    wsprintfW (buf, L"Invalid command id received: %d", id);
	    MessageBoxW (NULL, buf, L"GDB", MB_ICONERROR);
	    skip_next_id = 0;
	  }
	}
    }
}