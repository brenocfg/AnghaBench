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

/* Variables and functions */
 int /*<<< orphan*/  JERRYX_UNUSED (int) ; 
 int /*<<< orphan*/  jerry_debugger_transport_close () ; 
 int /*<<< orphan*/  jerry_debugger_transport_start () ; 

void
jerryx_debugger_after_connect (bool success) /**< tells whether the connection
                                              *   has been successfully established */
{
#if defined (JERRY_DEBUGGER) && (JERRY_DEBUGGER == 1)
  if (success)
  {
    jerry_debugger_transport_start ();
  }
  else
  {
    jerry_debugger_transport_close ();
  }
#else /* !(defined (JERRY_DEBUGGER) && (JERRY_DEBUGGER == 1)) */
  JERRYX_UNUSED (success);
#endif /* defined (JERRY_DEBUGGER) && (JERRY_DEBUGGER == 1) */
}