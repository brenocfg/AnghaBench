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
struct tui_gen_win_info {int width; int /*<<< orphan*/ * handle; } ;
struct tui_data_element {scalar_t__ highlight; int /*<<< orphan*/  content; } ;
typedef  int /*<<< orphan*/  WINDOW ;

/* Variables and functions */
 int /*<<< orphan*/  tui_refresh_win (struct tui_gen_win_info*) ; 
 int /*<<< orphan*/  waddch (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  waddstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wstandend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wstandout (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
tui_display_register (struct tui_data_element *data,
                      struct tui_gen_win_info *win_info)
{
  if (win_info->handle != (WINDOW *) NULL)
    {
      int i;

      if (data->highlight)
	wstandout (win_info->handle);
      
      wmove (win_info->handle, 0, 0);
      for (i = 1; i < win_info->width; i++)
        waddch (win_info->handle, ' ');
      wmove (win_info->handle, 0, 0);
      if (data->content)
        waddstr (win_info->handle, data->content);

      if (data->highlight)
	wstandend (win_info->handle);
      tui_refresh_win (win_info);
    }
}