#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int height; } ;
struct tui_win_info {TYPE_2__ generic; } ;
typedef  enum tui_win_type { ____Placeholder_tui_win_type } tui_win_type ;
typedef  enum tui_layout_type { ____Placeholder_tui_layout_type } tui_layout_type ;
struct TYPE_4__ {int height; } ;
struct TYPE_6__ {TYPE_1__ generic; } ;

/* Variables and functions */
#define  DISASSEM_COMMAND 132 
#define  DISASSEM_DATA_COMMAND 131 
#define  SRC_COMMAND 130 
#define  SRC_DATA_COMMAND 129 
#define  SRC_DISASSEM_COMMAND 128 
 TYPE_3__* TUI_CMD_WIN ; 
 int tui_term_height () ; 
 struct tui_win_info** tui_win_list ; 

int
tui_default_win_height (enum tui_win_type type, enum tui_layout_type layout)
{
  int h;

  if (tui_win_list[type] != (struct tui_win_info *) NULL)
    h = tui_win_list[type]->generic.height;
  else
    {
      switch (layout)
	{
	case SRC_COMMAND:
	case DISASSEM_COMMAND:
	  if (TUI_CMD_WIN == NULL)
	    h = tui_term_height () / 2;
	  else
	    h = tui_term_height () - TUI_CMD_WIN->generic.height;
	  break;
	case SRC_DISASSEM_COMMAND:
	case SRC_DATA_COMMAND:
	case DISASSEM_DATA_COMMAND:
	  if (TUI_CMD_WIN == NULL)
	    h = tui_term_height () / 3;
	  else
	    h = (tui_term_height () - TUI_CMD_WIN->generic.height) / 2;
	  break;
	default:
	  h = 0;
	  break;
	}
    }

  return h;
}