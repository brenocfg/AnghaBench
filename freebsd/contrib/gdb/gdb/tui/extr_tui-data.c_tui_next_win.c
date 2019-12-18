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
struct TYPE_2__ {int type; scalar_t__ is_visible; } ;
struct tui_win_info {TYPE_1__ generic; } ;
typedef  enum tui_win_type { ____Placeholder_tui_win_type } tui_win_type ;

/* Variables and functions */
 int CMD_WIN ; 
 int SRC_WIN ; 
 struct tui_win_info** tui_win_list ; 

struct tui_win_info *
tui_next_win (struct tui_win_info * cur_win)
{
  enum tui_win_type type = cur_win->generic.type;
  struct tui_win_info * next_win = (struct tui_win_info *) NULL;

  if (cur_win->generic.type == CMD_WIN)
    type = SRC_WIN;
  else
    type = cur_win->generic.type + 1;
  while (type != cur_win->generic.type && (next_win == NULL))
    {
      if (tui_win_list[type] && tui_win_list[type]->generic.is_visible)
	next_win = tui_win_list[type];
      else
	{
	  if (type == CMD_WIN)
	    type = SRC_WIN;
	  else
	    type++;
	}
    }

  return next_win;
}