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

/* Variables and functions */
 int /*<<< orphan*/  deprecated_selected_frame ; 
 int /*<<< orphan*/  error (char*) ; 
 int frame_relative_level (int /*<<< orphan*/ ) ; 
 struct frame_info* parse_frame_specification (char*) ; 
 int /*<<< orphan*/  select_frame (struct frame_info*) ; 
 int /*<<< orphan*/  selected_frame_level_changed_event (int) ; 
 int /*<<< orphan*/  target_has_stack ; 

void
select_frame_command (char *level_exp, int from_tty)
{
  struct frame_info *frame;
  int level = frame_relative_level (deprecated_selected_frame);

  if (!target_has_stack)
    error ("No stack.");

  frame = parse_frame_specification (level_exp);

  select_frame (frame);
  if (level != frame_relative_level (deprecated_selected_frame))
    selected_frame_level_changed_event (frame_relative_level (deprecated_selected_frame));
}