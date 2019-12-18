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
 scalar_t__ deprecated_selected_frame ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  frame_relative_level (scalar_t__) ; 
 int /*<<< orphan*/  print_stack_frame (scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ target_has_stack ; 

__attribute__((used)) static void
current_frame_command (char *level_exp, int from_tty)
{
  if (target_has_stack == 0 || deprecated_selected_frame == 0)
    error ("No stack.");
  print_stack_frame (deprecated_selected_frame,
			  frame_relative_level (deprecated_selected_frame), 1);
}