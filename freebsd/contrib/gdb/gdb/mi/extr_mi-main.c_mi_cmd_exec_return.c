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
typedef  enum mi_cmd_result { ____Placeholder_mi_cmd_result } mi_cmd_result ;

/* Variables and functions */
 int /*<<< orphan*/  LOC_AND_ADDRESS ; 
 int MI_CMD_DONE ; 
 int /*<<< orphan*/  deprecated_selected_frame ; 
 int /*<<< orphan*/  frame_relative_level (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_stack_frame (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  return_command (char*,int /*<<< orphan*/ ) ; 

enum mi_cmd_result
mi_cmd_exec_return (char *args, int from_tty)
{
  /* This command doesn't really execute the target, it just pops the
     specified number of frames. */
  if (*args)
    /* Call return_command with from_tty argument equal to 0 so as to
       avoid being queried. */
    return_command (args, 0);
  else
    /* Call return_command with from_tty argument equal to 0 so as to
       avoid being queried. */
    return_command (NULL, 0);

  /* Because we have called return_command with from_tty = 0, we need
     to print the frame here. */
  print_stack_frame (deprecated_selected_frame,
		     frame_relative_level (deprecated_selected_frame),
		     LOC_AND_ADDRESS);

  return MI_CMD_DONE;
}