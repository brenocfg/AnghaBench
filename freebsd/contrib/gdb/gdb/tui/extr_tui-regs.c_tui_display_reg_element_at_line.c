#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tui_win_content ;
struct TYPE_6__ {scalar_t__ regs_content; scalar_t__ regs_content_count; scalar_t__ data_content_count; } ;
struct TYPE_7__ {TYPE_2__ data_display_info; } ;
struct TYPE_5__ {int height; } ;
struct TYPE_8__ {TYPE_3__ detail; TYPE_1__ generic; } ;

/* Variables and functions */
 TYPE_4__* TUI_DATA_WIN ; 
 int /*<<< orphan*/  tui_display_registers_from (int) ; 
 int tui_first_reg_element_no_inline (int) ; 
 int tui_last_regs_line_no () ; 

void
tui_display_reg_element_at_line (int start_element_no, int start_line_no)
{
  if (TUI_DATA_WIN->detail.data_display_info.regs_content != (tui_win_content) NULL &&
      TUI_DATA_WIN->detail.data_display_info.regs_content_count > 0)
    {
      int element_no = start_element_no;

      if (start_element_no != 0 && start_line_no != 0)
	{
	  int last_line_no, first_line_on_last_page;

	  last_line_no = tui_last_regs_line_no ();
	  first_line_on_last_page = last_line_no - (TUI_DATA_WIN->generic.height - 2);
	  if (first_line_on_last_page < 0)
	    first_line_on_last_page = 0;
	  /*
	     ** If there is no other data displayed except registers,
	     ** and the element_no causes us to scroll past the end of the
	     ** registers, adjust what element to really start the display at.
	   */
	  if (TUI_DATA_WIN->detail.data_display_info.data_content_count <= 0 &&
	      start_line_no > first_line_on_last_page)
	    element_no = tui_first_reg_element_no_inline (first_line_on_last_page);
	}
      tui_display_registers_from (element_no);
    }
}