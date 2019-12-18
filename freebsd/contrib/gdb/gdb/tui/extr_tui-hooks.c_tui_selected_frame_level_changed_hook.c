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
struct symtab {int dummy; } ;
struct frame_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_WIN ; 
 struct frame_info* deprecated_selected_frame ; 
 struct symtab* find_pc_symtab (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_frame_pc (struct frame_info*) ; 
 int /*<<< orphan*/  select_source_symtab (struct symtab*) ; 
 int /*<<< orphan*/  tui_check_data_values (struct frame_info*) ; 
 scalar_t__ tui_is_window_visible (int /*<<< orphan*/ ) ; 
 int tui_refreshing_registers ; 
 int /*<<< orphan*/  tui_show_frame_info (struct frame_info*) ; 

__attribute__((used)) static void
tui_selected_frame_level_changed_hook (int level)
{
  struct frame_info *fi;

  fi = deprecated_selected_frame;
  /* Ensure that symbols for this frame are read in.  Also, determine the
     source language of this frame, and switch to it if desired.  */
  if (fi)
    {
      struct symtab *s;
      
      s = find_pc_symtab (get_frame_pc (fi));
      /* elz: this if here fixes the problem with the pc not being displayed
         in the tui asm layout, with no debug symbols. The value of s 
         would be 0 here, and select_source_symtab would abort the
         command by calling the 'error' function */
      if (s)
        select_source_symtab (s);

      /* Display the frame position (even if there is no symbols).  */
      tui_show_frame_info (fi);

      /* Refresh the register window if it's visible.  */
      if (tui_is_window_visible (DATA_WIN))
        {
          tui_refreshing_registers = 1;
          tui_check_data_values (fi);
          tui_refreshing_registers = 0;
        }
    }
}