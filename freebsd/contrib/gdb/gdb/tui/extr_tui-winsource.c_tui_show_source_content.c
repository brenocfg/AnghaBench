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
struct TYPE_2__ {scalar_t__ content_size; int /*<<< orphan*/  content_in_use; } ;
struct tui_win_info {TYPE_1__ generic; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  tui_check_and_display_highlight_if_needed (struct tui_win_info*) ; 
 int /*<<< orphan*/  tui_erase_source_content (struct tui_win_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tui_refresh_win (TYPE_1__*) ; 
 int /*<<< orphan*/  tui_show_source_line (struct tui_win_info*,int) ; 

void
tui_show_source_content (struct tui_win_info * win_info)
{
  if (win_info->generic.content_size > 0)
    {
      int lineno;

      for (lineno = 1; lineno <= win_info->generic.content_size; lineno++)
        tui_show_source_line (win_info, lineno);
    }
  else
    tui_erase_source_content (win_info, TRUE);

  tui_check_and_display_highlight_if_needed (win_info);
  tui_refresh_win (&win_info->generic);
  win_info->generic.content_in_use = TRUE;
}