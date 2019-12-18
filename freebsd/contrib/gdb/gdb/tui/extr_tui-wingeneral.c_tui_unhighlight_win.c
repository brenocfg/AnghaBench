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
struct TYPE_2__ {int /*<<< orphan*/ * handle; } ;
struct tui_win_info {TYPE_1__ generic; } ;
struct tui_gen_win_info {int dummy; } ;
typedef  int /*<<< orphan*/  WINDOW ;

/* Variables and functions */
 int /*<<< orphan*/  NO_HILITE ; 
 int /*<<< orphan*/  box_win (struct tui_gen_win_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tui_set_win_highlight (struct tui_win_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrefresh (int /*<<< orphan*/ *) ; 

void
tui_unhighlight_win (struct tui_win_info * win_info)
{
  if (win_info != NULL && win_info->generic.handle != (WINDOW *) NULL)
    {
      box_win ((struct tui_gen_win_info *) win_info, NO_HILITE);
      wrefresh (win_info->generic.handle);
      tui_set_win_highlight (win_info, 0);
    }
}