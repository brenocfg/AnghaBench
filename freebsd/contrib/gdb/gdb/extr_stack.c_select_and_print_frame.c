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
 int /*<<< orphan*/  frame_relative_level (struct frame_info*) ; 
 int /*<<< orphan*/  print_stack_frame (struct frame_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  select_frame (struct frame_info*) ; 

__attribute__((used)) static void
select_and_print_frame (struct frame_info *fi)
{
  select_frame (fi);
  if (fi)
    {
      print_stack_frame (fi, frame_relative_level (fi), 1);
    }
}