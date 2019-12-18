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
 int /*<<< orphan*/  print_frame_local_vars (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
locals_info (char *args, int from_tty)
{
  if (!deprecated_selected_frame)
    error ("No frame selected.");
  print_frame_local_vars (deprecated_selected_frame, 0, gdb_stdout);
}