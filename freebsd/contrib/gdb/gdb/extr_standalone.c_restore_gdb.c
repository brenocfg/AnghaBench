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
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  POP_FRAME_PTR ; 
 int /*<<< orphan*/  gdb_stack ; 

restore_gdb (void)
{
  CORE_ADDR new_fp = gdb_stack;
  /* Switch to GDB's stack  */
  POP_FRAME_PTR;
  /* Return from the function `resume'.  */
}