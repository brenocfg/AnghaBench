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
struct TYPE_2__ {scalar_t__ type; } ;
struct tui_win_info {TYPE_1__ generic; } ;

/* Variables and functions */
 scalar_t__ CMD_WIN ; 
 int /*<<< orphan*/  tui_highlight_win (struct tui_win_info*) ; 
 int /*<<< orphan*/  tui_set_win_with_focus (struct tui_win_info*) ; 
 int /*<<< orphan*/  tui_unhighlight_win (struct tui_win_info*) ; 
 struct tui_win_info* tui_win_with_focus () ; 

void
tui_set_win_focus_to (struct tui_win_info * win_info)
{
  if (win_info != NULL)
    {
      struct tui_win_info * win_with_focus = tui_win_with_focus ();

      if (win_with_focus != NULL
	  && win_with_focus->generic.type != CMD_WIN)
	tui_unhighlight_win (win_with_focus);
      tui_set_win_with_focus (win_info);
      if (win_info->generic.type != CMD_WIN)
	tui_highlight_win (win_info);
    }
}