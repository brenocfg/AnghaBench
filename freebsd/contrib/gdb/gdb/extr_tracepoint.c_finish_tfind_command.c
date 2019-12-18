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
struct symbol {int dummy; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  deprecated_selected_frame ; 
 int /*<<< orphan*/  do_displays () ; 
 int /*<<< orphan*/  error (char*,...) ; 
 struct symbol* find_pc_function (int) ; 
 int /*<<< orphan*/  flush_cached_frames () ; 
 int /*<<< orphan*/  frame_relative_level (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_current_frame () ; 
 scalar_t__ get_frame_base (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  info_verbose ; 
 int /*<<< orphan*/  print_stack_frame (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf_filtered (char*) ; 
 int /*<<< orphan*/  putpkt (char*) ; 
 int read_pc () ; 
 int /*<<< orphan*/  registers_changed () ; 
 char* remote_get_noisy_reply (char*,long) ; 
 int /*<<< orphan*/  select_frame (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_traceframe_context (int) ; 
 int /*<<< orphan*/  set_traceframe_num (int) ; 
 int /*<<< orphan*/  set_tracepoint_num (int) ; 
 scalar_t__ strtol (char*,char**,int) ; 
 int /*<<< orphan*/  trace_find_command (char*,int) ; 

__attribute__((used)) static void
finish_tfind_command (char *msg,
		      long sizeof_msg,
		      int from_tty)
{
  int target_frameno = -1, target_tracept = -1;
  CORE_ADDR old_frame_addr;
  struct symbol *old_func;
  char *reply;

  old_frame_addr = get_frame_base (get_current_frame ());
  old_func = find_pc_function (read_pc ());

  putpkt (msg);
  reply = remote_get_noisy_reply (msg, sizeof_msg);

  while (reply && *reply)
    switch (*reply)
      {
      case 'F':
	if ((target_frameno = (int) strtol (++reply, &reply, 16)) == -1)
	  {
	    /* A request for a non-existant trace frame has failed.
	       Our response will be different, depending on FROM_TTY:

	       If FROM_TTY is true, meaning that this command was 
	       typed interactively by the user, then give an error
	       and DO NOT change the state of traceframe_number etc.

	       However if FROM_TTY is false, meaning that we're either
	       in a script, a loop, or a user-defined command, then 
	       DON'T give an error, but DO change the state of
	       traceframe_number etc. to invalid.

	       The rationalle is that if you typed the command, you
	       might just have committed a typo or something, and you'd
	       like to NOT lose your current debugging state.  However
	       if you're in a user-defined command or especially in a
	       loop, then you need a way to detect that the command
	       failed WITHOUT aborting.  This allows you to write
	       scripts that search thru the trace buffer until the end,
	       and then continue on to do something else.  */

	    if (from_tty)
	      error ("Target failed to find requested trace frame.");
	    else
	      {
		if (info_verbose)
		  printf_filtered ("End of trace buffer.\n");
		/* The following will not recurse, since it's special-cased */
		trace_find_command ("-1", from_tty);
		reply = NULL;	/* break out of loop, 
				   (avoid recursive nonsense) */
	      }
	  }
	break;
      case 'T':
	if ((target_tracept = (int) strtol (++reply, &reply, 16)) == -1)
	  error ("Target failed to find requested trace frame.");
	break;
      case 'O':		/* "OK"? */
	if (reply[1] == 'K' && reply[2] == '\0')
	  reply += 2;
	else
	  error ("Bogus reply from target: %s", reply);
	break;
      default:
	error ("Bogus reply from target: %s", reply);
      }

  flush_cached_frames ();
  registers_changed ();
  select_frame (get_current_frame ());
  set_traceframe_num (target_frameno);
  set_tracepoint_num (target_tracept);
  if (target_frameno == -1)
    set_traceframe_context (-1);
  else
    set_traceframe_context (read_pc ());

  if (from_tty)
    {
      int source_only;

      /* NOTE: in immitation of the step command, try to determine
         whether we have made a transition from one function to another.
         If so, we'll print the "stack frame" (ie. the new function and
         it's arguments) -- otherwise we'll just show the new source line.

         This determination is made by checking (1) whether the current
         function has changed, and (2) whether the current FP has changed.
         Hack: if the FP wasn't collected, either at the current or the
         previous frame, assume that the FP has NOT changed.  */

      if (old_func == find_pc_function (read_pc ()) &&
	  (old_frame_addr == 0 ||
	   get_frame_base (get_current_frame ()) == 0 ||
	   old_frame_addr == get_frame_base (get_current_frame ())))
	source_only = -1;
      else
	source_only = 1;

      print_stack_frame (deprecated_selected_frame,
			 frame_relative_level (deprecated_selected_frame),
			 source_only);
      do_displays ();
    }
}