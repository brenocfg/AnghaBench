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
 struct frame_info* deprecated_selected_frame ; 
 int /*<<< orphan*/  tui_check_data_values (struct frame_info*) ; 
 int tui_refreshing_registers ; 

__attribute__((used)) static void
tui_registers_changed_hook (void)
{
  struct frame_info *fi;

  fi = deprecated_selected_frame;
  if (fi && tui_refreshing_registers == 0)
    {
      tui_refreshing_registers = 1;
#if 0
      tui_check_data_values (fi);
#endif
      tui_refreshing_registers = 0;
    }
}