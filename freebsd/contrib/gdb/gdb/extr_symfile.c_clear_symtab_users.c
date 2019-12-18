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
 int /*<<< orphan*/  breakpoint_re_set () ; 
 int /*<<< orphan*/  clear_current_source_symtab_and_line () ; 
 int /*<<< orphan*/  clear_displays () ; 
 int /*<<< orphan*/  clear_internalvars () ; 
 int /*<<< orphan*/  clear_pc_function_cache () ; 
 int /*<<< orphan*/  clear_value_history () ; 
 int /*<<< orphan*/  set_default_breakpoint (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target_new_objfile_hook (int /*<<< orphan*/ *) ; 

void
clear_symtab_users (void)
{
  /* Someday, we should do better than this, by only blowing away
     the things that really need to be blown.  */
  clear_value_history ();
  clear_displays ();
  clear_internalvars ();
  breakpoint_re_set ();
  set_default_breakpoint (0, 0, 0, 0);
  clear_current_source_symtab_and_line ();
  clear_pc_function_cache ();
  if (target_new_objfile_hook)
    target_new_objfile_hook (NULL);
}