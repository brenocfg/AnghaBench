#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_4__** tui_win_content ;
typedef  int /*<<< orphan*/  title ;
struct tui_data_element {int item_no; char const* name; void* value; void* highlight; } ;
struct TYPE_11__ {struct tui_data_element data; } ;
struct tui_win_element {TYPE_3__ which_element; } ;
struct tui_gen_win_info {scalar_t__* content; } ;
struct tui_data_info {int regs_content_count; scalar_t__ data_content_count; TYPE_4__** regs_content; } ;
struct reggroup {int dummy; } ;
struct gdbarch {int dummy; } ;
struct frame_info {int dummy; } ;
typedef  enum tui_status { ____Placeholder_tui_status } tui_status ;
struct TYPE_13__ {scalar_t__ content_size; void* content; int /*<<< orphan*/  title; } ;
struct TYPE_9__ {struct tui_data_info data_display_info; } ;
struct TYPE_14__ {TYPE_7__ generic; TYPE_1__ detail; } ;
struct TYPE_10__ {struct tui_gen_win_info data_window; } ;
struct TYPE_12__ {TYPE_2__ which_element; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_WIN ; 
 void* FALSE ; 
 int /*<<< orphan*/  MAX_REGISTER_SIZE ; 
 int NUM_PSEUDO_REGS ; 
 int NUM_REGS ; 
 int TRUE ; 
 TYPE_8__* TUI_DATA_WIN ; 
 int TUI_FAILURE ; 
 int TUI_SUCCESS ; 
 char* gdbarch_register_name (struct gdbarch*,int) ; 
 scalar_t__ gdbarch_register_reggroup_p (struct gdbarch*,int,struct reggroup*) ; 
 char* reggroup_name (struct reggroup*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  tui_add_content_elements (TYPE_7__*,int) ; 
 TYPE_4__** tui_alloc_content (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tui_free_data_content (TYPE_4__**,int) ; 
 int /*<<< orphan*/  tui_get_register (struct gdbarch*,struct frame_info*,struct tui_data_element*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfree (int /*<<< orphan*/ ) ; 
 scalar_t__ xmalloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xstrdup (char*) ; 

__attribute__((used)) static enum tui_status
tui_show_register_group (struct gdbarch *gdbarch, struct reggroup *group,
                         struct frame_info *frame, int refresh_values_only)
{
  enum tui_status ret = TUI_FAILURE;
  int nr_regs;
  int allocated_here = FALSE;
  int regnum, pos;
  char title[80];
  struct tui_data_info *display_info = &TUI_DATA_WIN->detail.data_display_info;

  /* Make a new title showing which group we display.  */
  snprintf (title, sizeof (title) - 1, "Register group: %s",
            reggroup_name (group));
  xfree (TUI_DATA_WIN->generic.title);
  TUI_DATA_WIN->generic.title = xstrdup (title);

  /* See how many registers must be displayed.  */
  nr_regs = 0;
  for (regnum = 0; regnum < NUM_REGS + NUM_PSEUDO_REGS; regnum++)
    {
      /* Must be in the group and have a name.  */
      if (gdbarch_register_reggroup_p (gdbarch, regnum, group)
          && gdbarch_register_name (gdbarch, regnum) != 0)
        nr_regs++;
    }

  if (display_info->regs_content_count > 0 && !refresh_values_only)
    {
      tui_free_data_content (display_info->regs_content,
                             display_info->regs_content_count);
      display_info->regs_content_count = 0;
    }

  if (display_info->regs_content_count <= 0)
    {
      display_info->regs_content = tui_alloc_content (nr_regs, DATA_WIN);
      allocated_here = TRUE;
      refresh_values_only = FALSE;
    }

  if (display_info->regs_content != (tui_win_content) NULL)
    {
      if (!refresh_values_only || allocated_here)
	{
	  TUI_DATA_WIN->generic.content = (void*) NULL;
	  TUI_DATA_WIN->generic.content_size = 0;
	  tui_add_content_elements (&TUI_DATA_WIN->generic, nr_regs);
	  display_info->regs_content
            = (tui_win_content) TUI_DATA_WIN->generic.content;
	  display_info->regs_content_count = nr_regs;
	}

      /* Now set the register names and values */
      pos = 0;
      for (regnum = 0; regnum < NUM_REGS + NUM_PSEUDO_REGS; regnum++)
        {
	  struct tui_gen_win_info *data_item_win;
          struct tui_data_element *data;
          const char *name;

          if (!gdbarch_register_reggroup_p (gdbarch, regnum, group))
            continue;

          name = gdbarch_register_name (gdbarch, regnum);
          if (name == 0)
            continue;

	  data_item_win =
            &display_info->regs_content[pos]->which_element.data_window;
          data =
            &((struct tui_win_element *) data_item_win->content[0])->which_element.data;
          if (data)
            {
              if (!refresh_values_only)
                {
                  data->item_no = regnum;
                  data->name = name;
                  data->highlight = FALSE;
                }
              if (data->value == (void*) NULL)
                data->value = (void*) xmalloc (MAX_REGISTER_SIZE);

              tui_get_register (gdbarch, frame, data, regnum, 0);
            }
          pos++;
	}

      TUI_DATA_WIN->generic.content_size =
	display_info->regs_content_count + display_info->data_content_count;
      ret = TUI_SUCCESS;
    }

  return ret;
}