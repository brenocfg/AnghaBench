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
 int /*<<< orphan*/  add_file_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_sigint_signal_handler (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_fd ; 
 int remote_async_terminal_ours_p ; 
 int /*<<< orphan*/  stdin_event_handler ; 
 int /*<<< orphan*/  sync_execution ; 

__attribute__((used)) static void
remote_async_terminal_ours (void)
{
  /* See FIXME in remote_async_terminal_inferior. */
  if (!sync_execution)
    return;
  /* See FIXME in remote_async_terminal_inferior. */
  if (remote_async_terminal_ours_p)
    return;
  cleanup_sigint_signal_handler (NULL);
  add_file_handler (input_fd, stdin_event_handler, 0);
  remote_async_terminal_ours_p = 1;
}