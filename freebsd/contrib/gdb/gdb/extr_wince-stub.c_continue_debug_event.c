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
typedef  scalar_t__ gdb_wince_result ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 scalar_t__ ContinueDebugEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GDB_CONTINUEDEBUGEVENT ; 
 int /*<<< orphan*/  getdword (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putresult (char*,scalar_t__,int,int /*<<< orphan*/ ,scalar_t__*,int) ; 

__attribute__((used)) static void
continue_debug_event (int s)
{
  gdb_wince_result res;
  DWORD pid = getdword (L"ContinueDebugEvent pid", s, GDB_CONTINUEDEBUGEVENT);
  DWORD tid = getdword (L"ContinueDebugEvent tid", s, GDB_CONTINUEDEBUGEVENT);
  DWORD status = getdword (L"ContinueDebugEvent status", s, GDB_CONTINUEDEBUGEVENT);
  res = (gdb_wince_result) ContinueDebugEvent (pid, tid, status);
  putresult (L"ContinueDebugEvent result", res, s, GDB_CONTINUEDEBUGEVENT, &res, sizeof (res));
}