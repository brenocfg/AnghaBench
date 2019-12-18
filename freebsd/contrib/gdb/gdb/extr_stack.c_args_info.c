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
 int /*<<< orphan*/  deprecated_selected_frame ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  gdb_stdout ; 
 int /*<<< orphan*/  print_frame_arg_vars (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
args_info (char *ignore, int from_tty)
{
  if (!deprecated_selected_frame)
    error ("No frame selected.");
  print_frame_arg_vars (deprecated_selected_frame, gdb_stdout);
}