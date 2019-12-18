#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__* content; } ;
struct TYPE_6__ {int horizontal_offset; } ;
struct TYPE_7__ {TYPE_1__ source_info; } ;
struct tui_win_info {TYPE_5__ generic; TYPE_2__ detail; } ;
struct TYPE_8__ {int /*<<< orphan*/  line_or_addr; } ;
struct TYPE_9__ {TYPE_3__ source; } ;
struct tui_win_element {TYPE_4__ which_element; } ;
struct symtab_and_line {struct symtab* symtab; } ;
struct symtab {int dummy; } ;
typedef  enum tui_scroll_direction { ____Placeholder_tui_scroll_direction } tui_scroll_direction ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int LEFT_SCROLL ; 
 int /*<<< orphan*/  deprecated_selected_frame ; 
 struct symtab* find_pc_symtab (int /*<<< orphan*/ ) ; 
 struct symtab_and_line get_current_source_symtab_and_line () ; 
 int /*<<< orphan*/  get_frame_pc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tui_update_source_window_as_is (struct tui_win_info*,struct symtab*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
tui_horizontal_source_scroll (struct tui_win_info * win_info,
			      enum tui_scroll_direction direction,
			      int num_to_scroll)
{
  if (win_info->generic.content != NULL)
    {
      int offset;
      struct symtab *s;
      struct symtab_and_line cursal = get_current_source_symtab_and_line ();

      if (cursal.symtab == (struct symtab *) NULL)
	s = find_pc_symtab (get_frame_pc (deprecated_selected_frame));
      else
	s = cursal.symtab;

      if (direction == LEFT_SCROLL)
	offset = win_info->detail.source_info.horizontal_offset + num_to_scroll;
      else
	{
	  if ((offset =
	     win_info->detail.source_info.horizontal_offset - num_to_scroll) < 0)
	    offset = 0;
	}
      win_info->detail.source_info.horizontal_offset = offset;
      tui_update_source_window_as_is (win_info, s,
				      ((struct tui_win_element *)
				       win_info->generic.content[0])->which_element.source.line_or_addr,
				      FALSE);
    }

  return;
}