#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  enum tui_win_type { ____Placeholder_tui_win_type } tui_win_type ;
struct TYPE_8__ {scalar_t__ is_visible; } ;
struct TYPE_9__ {TYPE_1__ generic; } ;

/* Variables and functions */
#define  DATA_WIN 130 
#define  DISASSEM_WIN 129 
 int MAX_MAJOR_WINDOWS ; 
#define  SRC_WIN 128 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  clearok (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curscr ; 
 int /*<<< orphan*/  tui_check_and_display_highlight_if_needed (TYPE_2__*) ; 
 int /*<<< orphan*/  tui_erase_exec_info_content (TYPE_2__*) ; 
 int /*<<< orphan*/  tui_refresh_all (TYPE_2__**) ; 
 int /*<<< orphan*/  tui_refresh_data_win () ; 
 int /*<<< orphan*/  tui_show_locator_content () ; 
 int /*<<< orphan*/  tui_show_source_content (TYPE_2__*) ; 
 int /*<<< orphan*/  tui_update_exec_info (TYPE_2__*) ; 
 TYPE_2__** tui_win_list ; 

void
tui_refresh_all_win (void)
{
  enum tui_win_type type;

  clearok (curscr, TRUE);
  tui_refresh_all (tui_win_list);
  for (type = SRC_WIN; type < MAX_MAJOR_WINDOWS; type++)
    {
      if (tui_win_list[type] && tui_win_list[type]->generic.is_visible)
	{
	  switch (type)
	    {
	    case SRC_WIN:
	    case DISASSEM_WIN:
	      tui_show_source_content (tui_win_list[type]);
	      tui_check_and_display_highlight_if_needed (tui_win_list[type]);
	      tui_erase_exec_info_content (tui_win_list[type]);
	      tui_update_exec_info (tui_win_list[type]);
	      break;
	    case DATA_WIN:
	      tui_refresh_data_win ();
	      break;
	    default:
	      break;
	    }
	}
    }
  tui_show_locator_content ();
}