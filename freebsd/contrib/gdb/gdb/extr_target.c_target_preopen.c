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
 int /*<<< orphan*/  dont_repeat () ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  pop_target () ; 
 scalar_t__ query (char*) ; 
 scalar_t__ target_has_execution ; 
 int /*<<< orphan*/  target_kill () ; 

void
target_preopen (int from_tty)
{
  dont_repeat ();

  if (target_has_execution)
    {
      if (!from_tty
          || query ("A program is being debugged already.  Kill it? "))
	target_kill ();
      else
	error ("Program not killed.");
    }

  /* Calling target_kill may remove the target from the stack.  But if
     it doesn't (which seems like a win for UDI), remove it now.  */

  if (target_has_execution)
    pop_target ();
}