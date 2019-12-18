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
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  DEBUG_EVENT ;

/* Variables and functions */
 int /*<<< orphan*/  GDB_WAITFORDEBUGEVENT ; 
 int getresult (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  putdword (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ s ; 

__attribute__((used)) static int
wait_for_debug_event (DEBUG_EVENT * ev, DWORD ms)
{
  if (s < 0)
    return 1;
  putdword ("WaitForDebugEvent ms", GDB_WAITFORDEBUGEVENT, ms);
  return getresult ("WaitForDebugEvent event", GDB_WAITFORDEBUGEVENT, ev, NULL);
}