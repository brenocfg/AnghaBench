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
struct TYPE_4__ {int regs_content_count; } ;
struct TYPE_5__ {TYPE_1__ data_display_info; } ;
struct TYPE_6__ {TYPE_2__ detail; } ;

/* Variables and functions */
 TYPE_3__* TUI_DATA_WIN ; 
 int /*<<< orphan*/  tui_display_reg_element_at_line (int,int) ; 
 int tui_first_reg_element_no_inline (int) ; 
 int tui_last_regs_line_no () ; 
 int tui_line_from_reg_element_no (int) ; 

int
tui_display_registers_from_line (int line_no, int force_display)
{
  if (TUI_DATA_WIN->detail.data_display_info.regs_content_count > 0)
    {
      int line, element_no;

      if (line_no < 0)
	line = 0;
      else if (force_display)
	{			/*
				   ** If we must display regs (force_display is true), then make
				   ** sure that we don't display off the end of the registers.
				 */
	  if (line_no >= tui_last_regs_line_no ())
	    {
	      if ((line = tui_line_from_reg_element_no (
		 TUI_DATA_WIN->detail.data_display_info.regs_content_count - 1)) < 0)
		line = 0;
	    }
	  else
	    line = line_no;
	}
      else
	line = line_no;

      element_no = tui_first_reg_element_no_inline (line);
      if (element_no < TUI_DATA_WIN->detail.data_display_info.regs_content_count)
	tui_display_reg_element_at_line (element_no, line);
      else
	line = (-1);

      return line;
    }

  return (-1);			/* nothing was displayed */
}