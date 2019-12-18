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
struct TYPE_4__ {int regs_content_count; int regs_column_count; } ;
struct TYPE_5__ {TYPE_1__ data_display_info; } ;
struct TYPE_6__ {TYPE_2__ detail; } ;

/* Variables and functions */
 TYPE_3__* TUI_DATA_WIN ; 

int
tui_line_from_reg_element_no (int element_no)
{
  if (element_no < TUI_DATA_WIN->detail.data_display_info.regs_content_count)
    {
      int i, line = (-1);

      i = 1;
      while (line == (-1))
	{
	  if (element_no <
	      (TUI_DATA_WIN->detail.data_display_info.regs_column_count * i))
	    line = i - 1;
	  else
	    i++;
	}

      return line;
    }
  else
    return (-1);
}