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
typedef  int /*<<< orphan*/  gdb_wince_result ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GDB_CONTINUEDEBUGEVENT ; 
 int getresult (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  putdword (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ s ; 

__attribute__((used)) static int
continue_debug_event (DWORD pid, DWORD tid, DWORD status)
{
  gdb_wince_result res;
  if (s < 0)
    return 0;
  putdword ("ContinueDebugEvent pid", GDB_CONTINUEDEBUGEVENT, pid);
  putdword ("ContinueDebugEvent tid", GDB_CONTINUEDEBUGEVENT, tid);
  putdword ("ContinueDebugEvent status", GDB_CONTINUEDEBUGEVENT, status);
  return getresult ("ContinueDebugEvent result", GDB_CONTINUEDEBUGEVENT, &res, NULL);
}