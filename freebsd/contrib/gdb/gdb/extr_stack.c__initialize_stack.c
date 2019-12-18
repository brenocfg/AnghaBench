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
 int /*<<< orphan*/  add_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_com (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  add_com_alias (char*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  add_info (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  add_info_alias (char*,char*,int) ; 
 int /*<<< orphan*/  args_info ; 
 int /*<<< orphan*/  args_plus_locals_info ; 
 int /*<<< orphan*/  backtrace_command ; 
 int /*<<< orphan*/  backtrace_full_command ; 
 int backtrace_limit ; 
 int /*<<< orphan*/  backtrace_limit_info ; 
 int /*<<< orphan*/  catch_info ; 
 int /*<<< orphan*/  class_alias ; 
 int /*<<< orphan*/  class_info ; 
 int /*<<< orphan*/  class_stack ; 
 int /*<<< orphan*/  class_support ; 
 int /*<<< orphan*/  current_frame_command ; 
 scalar_t__ dbx_commands ; 
 int /*<<< orphan*/  down_command ; 
 int /*<<< orphan*/  down_silently_command ; 
 int /*<<< orphan*/  frame_command ; 
 int /*<<< orphan*/  frame_info ; 
 int /*<<< orphan*/  func_command ; 
 int /*<<< orphan*/  locals_info ; 
 int /*<<< orphan*/  return_command ; 
 int /*<<< orphan*/  select_frame_command ; 
 int /*<<< orphan*/  set_backtrace_limit_command ; 
 int /*<<< orphan*/  setlist ; 
 int /*<<< orphan*/  up_command ; 
 int /*<<< orphan*/  up_silently_command ; 
 scalar_t__ xdb_commands ; 

void
_initialize_stack (void)
{
#if 0
  backtrace_limit = 30;
#endif

  add_com ("return", class_stack, return_command,
	   "Make selected stack frame return to its caller.\n\
Control remains in the debugger, but when you continue\n\
execution will resume in the frame above the one now selected.\n\
If an argument is given, it is an expression for the value to return.");

  add_com ("up", class_stack, up_command,
	   "Select and print stack frame that called this one.\n\
An argument says how many frames up to go.");
  add_com ("up-silently", class_support, up_silently_command,
	   "Same as the `up' command, but does not print anything.\n\
This is useful in command scripts.");

  add_com ("down", class_stack, down_command,
	   "Select and print stack frame called by this one.\n\
An argument says how many frames down to go.");
  add_com_alias ("do", "down", class_stack, 1);
  add_com_alias ("dow", "down", class_stack, 1);
  add_com ("down-silently", class_support, down_silently_command,
	   "Same as the `down' command, but does not print anything.\n\
This is useful in command scripts.");

  add_com ("frame", class_stack, frame_command,
	   "Select and print a stack frame.\n\
With no argument, print the selected stack frame.  (See also \"info frame\").\n\
An argument specifies the frame to select.\n\
It can be a stack frame number or the address of the frame.\n\
With argument, nothing is printed if input is coming from\n\
a command file or a user-defined command.");

  add_com_alias ("f", "frame", class_stack, 1);

  if (xdb_commands)
    {
      add_com ("L", class_stack, current_frame_command,
	       "Print the current stack frame.\n");
      add_com_alias ("V", "frame", class_stack, 1);
    }
  add_com ("select-frame", class_stack, select_frame_command,
	   "Select a stack frame without printing anything.\n\
An argument specifies the frame to select.\n\
It can be a stack frame number or the address of the frame.\n");

  add_com ("backtrace", class_stack, backtrace_command,
	   "Print backtrace of all stack frames, or innermost COUNT frames.\n\
With a negative argument, print outermost -COUNT frames.\n\
Use of the 'full' qualifier also prints the values of the local variables.\n");
  add_com_alias ("bt", "backtrace", class_stack, 0);
  if (xdb_commands)
    {
      add_com_alias ("t", "backtrace", class_stack, 0);
      add_com ("T", class_stack, backtrace_full_command,
	       "Print backtrace of all stack frames, or innermost COUNT frames \n\
and the values of the local variables.\n\
With a negative argument, print outermost -COUNT frames.\n\
Usage: T <count>\n");
    }

  add_com_alias ("where", "backtrace", class_alias, 0);
  add_info ("stack", backtrace_command,
	    "Backtrace of the stack, or innermost COUNT frames.");
  add_info_alias ("s", "stack", 1);
  add_info ("frame", frame_info,
	    "All about selected stack frame, or frame at ADDR.");
  add_info_alias ("f", "frame", 1);
  add_info ("locals", locals_info,
	    "Local variables of current stack frame.");
  add_info ("args", args_info,
	    "Argument variables of current stack frame.");
  if (xdb_commands)
    add_com ("l", class_info, args_plus_locals_info,
	     "Argument and local variables of current stack frame.");

  if (dbx_commands)
    add_com ("func", class_stack, func_command,
      "Select the stack frame that contains <func>.\nUsage: func <name>\n");

  add_info ("catch", catch_info,
	    "Exceptions that can be caught in the current stack frame.");

#if 0
  add_cmd ("backtrace-limit", class_stack, set_backtrace_limit_command,
  "Specify maximum number of frames for \"backtrace\" to print by default.",
	   &setlist);
  add_info ("backtrace-limit", backtrace_limit_info,
     "The maximum number of frames for \"backtrace\" to print by default.");
#endif
}