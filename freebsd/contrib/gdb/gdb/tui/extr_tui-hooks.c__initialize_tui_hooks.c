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
 int /*<<< orphan*/  target_new_objfile_hook ; 
 int /*<<< orphan*/  tui_new_objfile_hook ; 
 int /*<<< orphan*/  tui_target_new_objfile_chain ; 

void
_initialize_tui_hooks (void)
{
  /* Install the permanent hooks.  */
  tui_target_new_objfile_chain = target_new_objfile_hook;
  target_new_objfile_hook = tui_new_objfile_hook;
}