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
struct frame_info {int dummy; } ;
struct cleanup {int dummy; } ;
typedef  enum mi_cmd_result { ____Placeholder_mi_cmd_result } mi_cmd_result ;

/* Variables and functions */
 int /*<<< orphan*/  LOC_AND_ADDRESS ; 
 int MI_CMD_DONE ; 
 int /*<<< orphan*/  QUIT ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  error (char*) ; 
 struct frame_info* get_current_frame () ; 
 struct frame_info* get_prev_frame (struct frame_info*) ; 
 struct cleanup* make_cleanup_ui_out_list_begin_end (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  print_frame_info (struct frame_info*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target_has_stack ; 
 int /*<<< orphan*/  uiout ; 

enum mi_cmd_result
mi_cmd_stack_list_frames (char *command, char **argv, int argc)
{
  int frame_low;
  int frame_high;
  int i;
  struct cleanup *cleanup_stack;
  struct frame_info *fi;

  if (!target_has_stack)
    error ("mi_cmd_stack_list_frames: No stack.");

  if (argc > 2 || argc == 1)
    error ("mi_cmd_stack_list_frames: Usage: [FRAME_LOW FRAME_HIGH]");

  if (argc == 2)
    {
      frame_low = atoi (argv[0]);
      frame_high = atoi (argv[1]);
    }
  else
    {
      /* Called with no arguments, it means we want the whole
         backtrace. */
      frame_low = -1;
      frame_high = -1;
    }

  /* Let's position fi on the frame at which to start the
     display. Could be the innermost frame if the whole stack needs
     displaying, or if frame_low is 0. */
  for (i = 0, fi = get_current_frame ();
       fi && i < frame_low;
       i++, fi = get_prev_frame (fi));

  if (fi == NULL)
    error ("mi_cmd_stack_list_frames: Not enough frames in stack.");

  cleanup_stack = make_cleanup_ui_out_list_begin_end (uiout, "stack");

  /* Now let;s print the frames up to frame_high, or until there are
     frames in the stack. */
  for (;
       fi && (i <= frame_high || frame_high == -1);
       i++, fi = get_prev_frame (fi))
    {
      QUIT;
      /* level == i: always print the level 'i'
         source == LOC_AND_ADDRESS: print the location and the address 
         always, even for level 0.
         args == 0: don't print the arguments. */
      print_frame_info (fi /* frame info */ ,
			i /* level */ ,
			LOC_AND_ADDRESS /* source */ ,
			0 /* args */ );
    }

  do_cleanups (cleanup_stack);
  if (i < frame_high)
    error ("mi_cmd_stack_list_frames: Not enough frames in stack.");

  return MI_CMD_DONE;
}