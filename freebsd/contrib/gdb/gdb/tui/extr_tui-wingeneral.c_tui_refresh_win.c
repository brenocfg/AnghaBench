#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__** tui_win_content ;
struct tui_gen_win_info {scalar_t__ type; scalar_t__ content_size; int /*<<< orphan*/ * handle; scalar_t__ content; } ;
typedef  int /*<<< orphan*/  WINDOW ;
struct TYPE_3__ {struct tui_gen_win_info data_window; } ;
struct TYPE_4__ {TYPE_1__ which_element; } ;

/* Variables and functions */
 scalar_t__ CMD_WIN ; 
 scalar_t__ DATA_WIN ; 
 int /*<<< orphan*/  wrefresh (int /*<<< orphan*/ *) ; 

void
tui_refresh_win (struct tui_gen_win_info * win_info)
{
  if (win_info->type == DATA_WIN && win_info->content_size > 0)
    {
      int i;

      for (i = 0; (i < win_info->content_size); i++)
	{
	  struct tui_gen_win_info * data_item_win_ptr;

	  data_item_win_ptr = &((tui_win_content)
			     win_info->content)[i]->which_element.data_window;
	  if (data_item_win_ptr != NULL
	      && data_item_win_ptr->handle != (WINDOW *) NULL)
	    wrefresh (data_item_win_ptr->handle);
	}
    }
  else if (win_info->type == CMD_WIN)
    {
      /* Do nothing */
    }
  else
    {
      if (win_info->handle != (WINDOW *) NULL)
	wrefresh (win_info->handle);
    }

  return;
}