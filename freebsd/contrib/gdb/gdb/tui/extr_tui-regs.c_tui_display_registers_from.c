#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_6__** tui_win_content ;
struct tui_data_element {char* content; } ;
struct TYPE_11__ {struct tui_data_element data; } ;
struct tui_win_element {TYPE_4__ which_element; } ;
struct TYPE_12__ {int x; int y; } ;
struct tui_gen_win_info {int height; int width; int /*<<< orphan*/ * handle; TYPE_5__ origin; scalar_t__* content; } ;
struct tui_data_info {scalar_t__ regs_content_count; int regs_column_count; TYPE_6__** regs_content; } ;
typedef  int /*<<< orphan*/  WINDOW ;
struct TYPE_9__ {int width; int viewport_height; } ;
struct TYPE_8__ {struct tui_data_info data_display_info; } ;
struct TYPE_14__ {TYPE_2__ generic; TYPE_1__ detail; } ;
struct TYPE_10__ {struct tui_gen_win_info data_window; } ;
struct TYPE_13__ {TYPE_3__ which_element; } ;

/* Variables and functions */
 int /*<<< orphan*/  DONT_BOX_WINDOW ; 
 int /*<<< orphan*/  FALSE ; 
 TYPE_7__* TUI_DATA_WIN ; 
 int /*<<< orphan*/  scrollok (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  touchwin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tui_delete_win (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tui_display_register (struct tui_data_element*,struct tui_gen_win_info*) ; 
 int /*<<< orphan*/  tui_make_window (struct tui_gen_win_info*,int /*<<< orphan*/ ) ; 

void
tui_display_registers_from (int start_element_no)
{
  struct tui_data_info *display_info = &TUI_DATA_WIN->detail.data_display_info;

  if (display_info->regs_content != (tui_win_content) NULL &&
      display_info->regs_content_count > 0)
    {
      int i = start_element_no;
      int j, value_chars_wide, item_win_width, cur_y;

      int max_len = 0;
      for (i = 0; i < display_info->regs_content_count; i++)
        {
          struct tui_data_element *data;
          struct tui_gen_win_info *data_item_win;
          char *p;
          int len;

          data_item_win = &display_info->regs_content[i]->which_element.data_window;
          data = &((struct tui_win_element *)
                   data_item_win->content[0])->which_element.data;
          len = 0;
          p = data->content;
          if (p != 0)
            while (*p)
              {
                if (*p++ == '\t')
                  len = 8 * ((len / 8) + 1);
                else
                  len++;
              }

          if (len > max_len)
            max_len = len;
        }
      item_win_width = max_len + 1;
      i = start_element_no;

      display_info->regs_column_count =
        (TUI_DATA_WIN->generic.width - 2) / item_win_width;
      if (display_info->regs_column_count == 0)
        display_info->regs_column_count = 1;
      item_win_width =
        (TUI_DATA_WIN->generic.width - 2) / display_info->regs_column_count;

      /*
         ** Now create each data "sub" window, and write the display into it.
       */
      cur_y = 1;
      while (i < display_info->regs_content_count &&
	     cur_y <= TUI_DATA_WIN->generic.viewport_height)
	{
	  for (j = 0;
	       (j < display_info->regs_column_count &&
		i < display_info->regs_content_count); j++)
	    {
	      struct tui_gen_win_info * data_item_win;
	      struct tui_data_element * data_element_ptr;

	      /* create the window if necessary */
	      data_item_win = &display_info->regs_content[i]
                ->which_element.data_window;
	      data_element_ptr = &((struct tui_win_element *)
				 data_item_win->content[0])->which_element.data;
              if (data_item_win->handle != (WINDOW*) NULL
                  && (data_item_win->height != 1
                      || data_item_win->width != item_win_width
                      || data_item_win->origin.x != (item_win_width * j) + 1
                      || data_item_win->origin.y != cur_y))
                {
                  tui_delete_win (data_item_win->handle);
                  data_item_win->handle = 0;
                }
                  
	      if (data_item_win->handle == (WINDOW *) NULL)
		{
		  data_item_win->height = 1;
		  data_item_win->width = item_win_width;
		  data_item_win->origin.x = (item_win_width * j) + 1;
		  data_item_win->origin.y = cur_y;
		  tui_make_window (data_item_win, DONT_BOX_WINDOW);
                  scrollok (data_item_win->handle, FALSE);
		}
              touchwin (data_item_win->handle);

	      /* Get the printable representation of the register
                 and display it.  */
              tui_display_register (data_element_ptr, data_item_win);
	      i++;		/* next register */
	    }
	  cur_y++;		/* next row; */
	}
    }
}