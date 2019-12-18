#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  dwProcessId; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CTRL_C_EVENT ; 
 int /*<<< orphan*/  DEBUG_EVENTS (char*) ; 
 int /*<<< orphan*/  GenerateConsoleCtrlEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ current_event ; 
 int /*<<< orphan*/  registers_changed () ; 

__attribute__((used)) static void
child_stop (void)
{
  DEBUG_EVENTS (("gdb: GenerateConsoleCtrlEvent (CTRLC_EVENT, 0)\n"));
  CHECK (GenerateConsoleCtrlEvent (CTRL_C_EVENT, current_event.dwProcessId));
  registers_changed ();		/* refresh register state */
}