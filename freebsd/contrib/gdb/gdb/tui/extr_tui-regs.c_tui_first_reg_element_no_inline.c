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
struct TYPE_4__ {int regs_column_count; int regs_content_count; } ;
struct TYPE_5__ {TYPE_1__ data_display_info; } ;
struct TYPE_6__ {TYPE_2__ detail; } ;

/* Variables and functions */
 TYPE_3__* TUI_DATA_WIN ; 

int
tui_first_reg_element_no_inline (int line_no)
{
  if ((line_no * TUI_DATA_WIN->detail.data_display_info.regs_column_count)
      <= TUI_DATA_WIN->detail.data_display_info.regs_content_count)
    return ((line_no + 1) *
	    TUI_DATA_WIN->detail.data_display_info.regs_column_count) -
      TUI_DATA_WIN->detail.data_display_info.regs_column_count;
  else
    return (-1);
}