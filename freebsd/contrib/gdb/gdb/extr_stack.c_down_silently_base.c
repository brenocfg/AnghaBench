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
 scalar_t__ deprecated_selected_frame ; 
 int /*<<< orphan*/  error (char*) ; 
 struct frame_info* find_relative_frame (scalar_t__,int*) ; 
 int /*<<< orphan*/  frame_relative_level (scalar_t__) ; 
 int parse_and_eval_long (char*) ; 
 int /*<<< orphan*/  select_frame (struct frame_info*) ; 
 int /*<<< orphan*/  selected_frame_level_changed_event (int /*<<< orphan*/ ) ; 
 scalar_t__ target_has_stack ; 

__attribute__((used)) static void
down_silently_base (char *count_exp)
{
  struct frame_info *frame;
  int count = -1, count1;
  if (count_exp)
    count = -parse_and_eval_long (count_exp);
  count1 = count;

  if (target_has_stack == 0 || deprecated_selected_frame == 0)
    error ("No stack.");

  frame = find_relative_frame (deprecated_selected_frame, &count1);
  if (count1 != 0 && count_exp == 0)
    {

      /* We only do this if count_exp is not specified.  That way "down"
         means to really go down (and let me know if that is
         impossible), but "down 9999" can be used to mean go all the way
         down without getting an error.  */

      error ("Bottom (i.e., innermost) frame selected; you cannot go down.");
    }

  select_frame (frame);
  selected_frame_level_changed_event (frame_relative_level (deprecated_selected_frame));
}