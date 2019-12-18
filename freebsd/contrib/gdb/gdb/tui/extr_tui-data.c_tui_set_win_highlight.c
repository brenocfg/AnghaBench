#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tui_win_info {int is_highlighted; } ;

/* Variables and functions */

void
tui_set_win_highlight (struct tui_win_info *win_info, int highlight)
{
  if (win_info != NULL)
    win_info->is_highlighted = highlight;
}