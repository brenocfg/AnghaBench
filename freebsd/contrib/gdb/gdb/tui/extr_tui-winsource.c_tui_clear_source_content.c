#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int content_size; scalar_t__* content; void* content_in_use; } ;
struct tui_win_info {TYPE_3__ generic; } ;
struct TYPE_4__ {void* is_exec_point; void* has_break; } ;
struct TYPE_5__ {TYPE_1__ source; } ;
struct tui_win_element {TYPE_2__ which_element; } ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  tui_erase_source_content (struct tui_win_info*,int) ; 

void
tui_clear_source_content (struct tui_win_info * win_info, int display_prompt)
{
  if (win_info != NULL)
    {
      int i;

      win_info->generic.content_in_use = FALSE;
      tui_erase_source_content (win_info, display_prompt);
      for (i = 0; i < win_info->generic.content_size; i++)
	{
	  struct tui_win_element * element =
	  (struct tui_win_element *) win_info->generic.content[i];
	  element->which_element.source.has_break = FALSE;
	  element->which_element.source.is_exec_point = FALSE;
	}
    }
}