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
 int /*<<< orphan*/  delete_file_handler (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initialize_sigint_signal_handler () ; 
 int /*<<< orphan*/  input_fd ; 
 scalar_t__ remote_async_terminal_ours_p ; 
 int /*<<< orphan*/  sync_execution ; 

__attribute__((used)) static void
remote_async_terminal_inferior (void)
{
  /* FIXME: cagney/1999-09-27: Shouldn't need to test for
     sync_execution here.  This function should only be called when
     GDB is resuming the inferior in the forground.  A background
     resume (``run&'') should leave GDB in control of the terminal and
     consequently should not call this code. */
  if (!sync_execution)
    return;
  /* FIXME: cagney/1999-09-27: Closely related to the above.  Make
     calls target_terminal_*() idenpotent. The event-loop GDB talking
     to an asynchronous target with a synchronous command calls this
     function from both event-top.c and infrun.c/infcmd.c.  Once GDB
     stops trying to transfer the terminal to the target when it
     shouldn't this guard can go away.  */
  if (!remote_async_terminal_ours_p)
    return;
  delete_file_handler (input_fd);
  remote_async_terminal_ours_p = 0;
  initialize_sigint_signal_handler ();
  /* NOTE: At this point we could also register our selves as the
     recipient of all input.  Any characters typed could then be
     passed on down to the target. */
}