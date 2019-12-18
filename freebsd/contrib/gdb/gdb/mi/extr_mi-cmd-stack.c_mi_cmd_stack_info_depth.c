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
typedef  enum mi_cmd_result { ____Placeholder_mi_cmd_result } mi_cmd_result ;

/* Variables and functions */
 int MI_CMD_DONE ; 
 int /*<<< orphan*/  QUIT ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  error (char*) ; 
 struct frame_info* get_current_frame () ; 
 struct frame_info* get_prev_frame (struct frame_info*) ; 
 int /*<<< orphan*/  target_has_stack ; 
 int /*<<< orphan*/  ui_out_field_int (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  uiout ; 

enum mi_cmd_result
mi_cmd_stack_info_depth (char *command, char **argv, int argc)
{
  int frame_high;
  int i;
  struct frame_info *fi;

  if (!target_has_stack)
    error ("mi_cmd_stack_info_depth: No stack.");

  if (argc > 1)
    error ("mi_cmd_stack_info_depth: Usage: [MAX_DEPTH]");

  if (argc == 1)
    frame_high = atoi (argv[0]);
  else
    /* Called with no arguments, it means we want the real depth of
       the stack. */
    frame_high = -1;

  for (i = 0, fi = get_current_frame ();
       fi && (i < frame_high || frame_high == -1);
       i++, fi = get_prev_frame (fi))
    QUIT;

  ui_out_field_int (uiout, "depth", i);

  return MI_CMD_DONE;
}