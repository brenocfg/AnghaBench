#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__** tui_win_content ;
struct tui_gen_win_info {scalar_t__ is_visible; int /*<<< orphan*/ * handle; } ;
typedef  int /*<<< orphan*/  WINDOW ;
struct TYPE_5__ {int content_size; scalar_t__ content; } ;
struct TYPE_8__ {TYPE_1__ generic; } ;
struct TYPE_6__ {struct tui_gen_win_info data_window; } ;
struct TYPE_7__ {TYPE_2__ which_element; } ;

/* Variables and functions */
 TYPE_4__* TUI_DATA_WIN ; 

int
tui_first_data_item_displayed (void)
{
  int element_no = (-1);
  int i;

  for (i = 0; (i < TUI_DATA_WIN->generic.content_size && element_no < 0); i++)
    {
      struct tui_gen_win_info * data_item_win;

      data_item_win = &((tui_win_content)
		      TUI_DATA_WIN->generic.content)[i]->which_element.data_window;
      if (data_item_win->handle != (WINDOW *) NULL && data_item_win->is_visible)
	element_no = i;
    }

  return element_no;
}