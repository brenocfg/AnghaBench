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
union tui_line_or_address {scalar_t__ addr; } ;
typedef  TYPE_4__** tui_win_content ;
struct TYPE_10__ {int content_size; int /*<<< orphan*/  content; } ;
struct tui_win_info {TYPE_5__ generic; } ;
struct TYPE_6__ {scalar_t__ addr; } ;
struct TYPE_7__ {int is_exec_point; TYPE_1__ line_or_addr; } ;
struct TYPE_8__ {TYPE_2__ source; } ;
struct TYPE_9__ {TYPE_3__ which_element; } ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  tui_refresh_win (TYPE_5__*) ; 
 int /*<<< orphan*/  tui_show_source_line (struct tui_win_info*,int) ; 

void
tui_set_is_exec_point_at (union tui_line_or_address l, struct tui_win_info * win_info)
{
  int changed = 0;
  int i;
  tui_win_content content = (tui_win_content) win_info->generic.content;

  i = 0;
  while (i < win_info->generic.content_size)
    {
      int new_state;

      if (content[i]->which_element.source.line_or_addr.addr == l.addr)
        new_state = TRUE;
      else
	new_state = FALSE;
      if (new_state != content[i]->which_element.source.is_exec_point)
        {
          changed++;
          content[i]->which_element.source.is_exec_point = new_state;
          tui_show_source_line (win_info, i + 1);
        }
      i++;
    }
  if (changed)
    tui_refresh_win (&win_info->generic);
}