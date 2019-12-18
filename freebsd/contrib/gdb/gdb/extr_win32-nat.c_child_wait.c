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
struct target_waitstatus {int dummy; } ;
typedef  int /*<<< orphan*/  ptid_t ;

/* Variables and functions */
 int PIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  child_kill_inferior () ; 
 int get_child_debug_event (int,struct target_waitstatus*) ; 
 int /*<<< orphan*/  pid_to_ptid (int) ; 
 int ui_loop_hook (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ptid_t
child_wait (ptid_t ptid, struct target_waitstatus *ourstatus)
{
  int pid = PIDGET (ptid);

  /* We loop when we get a non-standard exception rather than return
     with a SPURIOUS because resume can try and step or modify things,
     which needs a current_thread->h.  But some of these exceptions mark
     the birth or death of threads, which mean that the current thread
     isn't necessarily what you think it is. */

  while (1)
    {
      int retval = get_child_debug_event (pid, ourstatus);
      if (retval)
	return pid_to_ptid (retval);
      else
	{
	  int detach = 0;

	  if (ui_loop_hook != NULL)
	    detach = ui_loop_hook (0);

	  if (detach)
	    child_kill_inferior ();
	}
    }
}