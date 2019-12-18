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
struct tui_gen_win_info {scalar_t__ type; int /*<<< orphan*/ * handle; scalar_t__ is_visible; } ;
typedef  int /*<<< orphan*/  WINDOW ;

/* Variables and functions */
 scalar_t__ CMD_WIN ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  tui_delete_win (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tui_make_window (struct tui_gen_win_info*,int) ; 
 int /*<<< orphan*/  tui_win_is_auxillary (scalar_t__) ; 

__attribute__((used)) static void
make_visible (struct tui_gen_win_info *win_info, int visible)
{
  /* Don't tear down/recreate command window */
  if (win_info->type == CMD_WIN)
    return;

  if (visible)
    {
      if (!win_info->is_visible)
	{
	  tui_make_window (win_info,
			   (win_info->type != CMD_WIN
			    && !tui_win_is_auxillary (win_info->type)));
	  win_info->is_visible = TRUE;
	}
    }
  else if (!visible &&
	   win_info->is_visible && win_info->handle != (WINDOW *) NULL)
    {
      win_info->is_visible = FALSE;
      tui_delete_win (win_info->handle);
      win_info->handle = (WINDOW *) NULL;
    }

  return;
}