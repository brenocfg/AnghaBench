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
typedef  enum tui_register_display_type { ____Placeholder_tui_register_display_type } tui_register_display_type ;
typedef  enum tui_layout_type { ____Placeholder_tui_layout_type } tui_layout_type ;

/* Variables and functions */
#define  DISASSEM_COMMAND 132 
#define  DISASSEM_DATA_COMMAND 131 
#define  SRC_COMMAND 130 
#define  SRC_DATA_COMMAND 129 
#define  SRC_DISASSEM_COMMAND 128 
 int TUI_UNDEFINED_REGS ; 
 scalar_t__ tui_active ; 
 int tui_current_layout () ; 
 int /*<<< orphan*/  tui_rl_switch_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tui_set_layout (int,int) ; 

__attribute__((used)) static int
tui_rl_delete_other_windows (int notused1, int notused2)
{
  if (!tui_active)
    tui_rl_switch_mode (0/*notused*/, 0/*notused*/);

  if (tui_active)
    {
      enum tui_layout_type new_layout;
      enum tui_register_display_type regs_type = TUI_UNDEFINED_REGS;

      new_layout = tui_current_layout ();

      /* Kill one window.  */
      switch (new_layout)
	{
	case SRC_COMMAND:
	case SRC_DATA_COMMAND:
	case SRC_DISASSEM_COMMAND:
	default:
	  new_layout = SRC_COMMAND;
	  break;

	case DISASSEM_COMMAND:
	case DISASSEM_DATA_COMMAND:
	  new_layout = DISASSEM_COMMAND;
	  break;
	}
      tui_set_layout (new_layout, regs_type);
    }
  return 0;
}