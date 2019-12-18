#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int width; scalar_t__ type; int height; int /*<<< orphan*/ * handle; } ;
struct tui_win_info {TYPE_1__ generic; } ;
typedef  int /*<<< orphan*/  WINDOW ;

/* Variables and functions */
 int EMPTY_SOURCE_PROMPT ; 
 char* NO_DISASSEM_STRING ; 
 char* NO_SRC_STRING ; 
 scalar_t__ SRC_WIN ; 
 int /*<<< orphan*/  mvwaddstr (int /*<<< orphan*/ *,int,int,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  tui_check_and_display_highlight_if_needed (struct tui_win_info*) ; 
 int /*<<< orphan*/  tui_refresh_win (TYPE_1__*) ; 
 int /*<<< orphan*/  tui_set_source_content_nil (struct tui_win_info*,char*) ; 
 int /*<<< orphan*/  werase (int /*<<< orphan*/ *) ; 

void
tui_erase_source_content (struct tui_win_info * win_info, int display_prompt)
{
  int x_pos;
  int half_width = (win_info->generic.width - 2) / 2;

  if (win_info->generic.handle != (WINDOW *) NULL)
    {
      werase (win_info->generic.handle);
      tui_check_and_display_highlight_if_needed (win_info);
      if (display_prompt == EMPTY_SOURCE_PROMPT)
	{
	  char *no_src_str;

	  if (win_info->generic.type == SRC_WIN)
	    no_src_str = NO_SRC_STRING;
	  else
	    no_src_str = NO_DISASSEM_STRING;
	  if (strlen (no_src_str) >= half_width)
	    x_pos = 1;
	  else
	    x_pos = half_width - strlen (no_src_str);
	  mvwaddstr (win_info->generic.handle,
		     (win_info->generic.height / 2),
		     x_pos,
		     no_src_str);

	  /* elz: added this function call to set the real contents of
	     the window to what is on the  screen, so that later calls
	     to refresh, do display
	     the correct stuff, and not the old image */

	  tui_set_source_content_nil (win_info, no_src_str);
	}
      tui_refresh_win (&win_info->generic);
    }
}