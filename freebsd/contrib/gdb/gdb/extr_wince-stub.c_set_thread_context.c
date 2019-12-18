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
typedef  int /*<<< orphan*/  res ;
typedef  int /*<<< orphan*/  gdb_wince_result ;
typedef  int /*<<< orphan*/  LPCONTEXT ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  GDB_SETTHREADCONTEXT ; 
 int /*<<< orphan*/  SetThreadContext (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gethandle (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getmemory (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  putresult (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
set_thread_context (int s)
{
  gdb_wince_result res;
  HANDLE h = gethandle (L"SetThreadContext handle", s, GDB_SETTHREADCONTEXT);
  LPCONTEXT pc = (LPCONTEXT) getmemory (L"SetThreadContext context", s,
					GDB_SETTHREADCONTEXT, NULL);

  res = SetThreadContext (h, pc);
  putresult (L"SetThreadContext result", res, s, GDB_SETTHREADCONTEXT,
	     &res, sizeof (res));
}