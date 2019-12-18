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
struct TYPE_2__ {int x; int y; } ;
struct tui_gen_win_info {int type; int width; int height; int viewport_height; TYPE_1__ origin; } ;
typedef  enum tui_win_type { ____Placeholder_tui_win_type } tui_win_type ;

/* Variables and functions */
 scalar_t__ CMD_WIN ; 

__attribute__((used)) static void
init_gen_win_info (struct tui_gen_win_info * win_info, enum tui_win_type type,
                 int height, int width, int origin_x, int origin_y)
{
  int h = height;

  win_info->type = type;
  win_info->width = width;
  win_info->height = h;
  if (h > 1)
    {
      win_info->viewport_height = h - 1;
      if (win_info->type != CMD_WIN)
	win_info->viewport_height--;
    }
  else
    win_info->viewport_height = 1;
  win_info->origin.x = origin_x;
  win_info->origin.y = origin_y;

  return;
}