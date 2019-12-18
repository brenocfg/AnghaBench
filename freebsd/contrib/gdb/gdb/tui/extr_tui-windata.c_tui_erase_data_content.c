#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int width; int height; int /*<<< orphan*/  handle; } ;
struct TYPE_5__ {TYPE_1__ generic; } ;

/* Variables and functions */
 TYPE_2__* TUI_DATA_WIN ; 
 int /*<<< orphan*/  mvwaddstr (int /*<<< orphan*/ ,int,int,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  tui_check_and_display_highlight_if_needed (TYPE_2__*) ; 
 int /*<<< orphan*/  werase (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrefresh (int /*<<< orphan*/ ) ; 

void
tui_erase_data_content (char *prompt)
{
  werase (TUI_DATA_WIN->generic.handle);
  tui_check_and_display_highlight_if_needed (TUI_DATA_WIN);
  if (prompt != (char *) NULL)
    {
      int half_width = (TUI_DATA_WIN->generic.width - 2) / 2;
      int x_pos;

      if (strlen (prompt) >= half_width)
	x_pos = 1;
      else
	x_pos = half_width - strlen (prompt);
      mvwaddstr (TUI_DATA_WIN->generic.handle,
		 (TUI_DATA_WIN->generic.height / 2),
		 x_pos,
		 prompt);
    }
  wrefresh (TUI_DATA_WIN->generic.handle);
}