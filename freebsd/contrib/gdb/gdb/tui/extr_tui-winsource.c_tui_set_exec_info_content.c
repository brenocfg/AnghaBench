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
struct TYPE_10__ {int content_size; scalar_t__* content; int /*<<< orphan*/  height; } ;
struct TYPE_6__ {struct tui_gen_win_info* execution_info; } ;
struct TYPE_7__ {TYPE_1__ source_info; } ;
struct tui_win_info {TYPE_5__ generic; TYPE_2__ detail; } ;
struct TYPE_8__ {int has_break; scalar_t__ is_exec_point; } ;
struct TYPE_9__ {char* simple_string; TYPE_3__ source; } ;
struct tui_win_element {TYPE_4__ which_element; } ;
struct tui_gen_win_info {void** content; int content_size; int /*<<< orphan*/  type; } ;
typedef  enum tui_status { ____Placeholder_tui_status } tui_status ;

/* Variables and functions */
 size_t TUI_BP_BREAK_POS ; 
 int TUI_BP_DISABLED ; 
 int TUI_BP_ENABLED ; 
 int TUI_BP_HARDWARE ; 
 int TUI_BP_HIT ; 
 size_t TUI_BP_HIT_POS ; 
 int TUI_EXECINFO_SIZE ; 
 size_t TUI_EXEC_POS ; 
 int TUI_FAILURE ; 
 int TUI_SUCCESS ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 scalar_t__ tui_alloc_content (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tui_update_breakpoint_info (struct tui_win_info*,int) ; 

enum tui_status
tui_set_exec_info_content (struct tui_win_info * win_info)
{
  enum tui_status ret = TUI_SUCCESS;

  if (win_info->detail.source_info.execution_info != (struct tui_gen_win_info *) NULL)
    {
      struct tui_gen_win_info * exec_info_ptr = win_info->detail.source_info.execution_info;

      if (exec_info_ptr->content == NULL)
	exec_info_ptr->content =
	  (void **) tui_alloc_content (win_info->generic.height,
					 exec_info_ptr->type);
      if (exec_info_ptr->content != NULL)
	{
	  int i;

          tui_update_breakpoint_info (win_info, 1);
	  for (i = 0; i < win_info->generic.content_size; i++)
	    {
	      struct tui_win_element * element;
	      struct tui_win_element * src_element;
              int mode;

	      element = (struct tui_win_element *) exec_info_ptr->content[i];
	      src_element = (struct tui_win_element *) win_info->generic.content[i];

              memset(element->which_element.simple_string, ' ',
                     sizeof(element->which_element.simple_string));
              element->which_element.simple_string[TUI_EXECINFO_SIZE - 1] = 0;

	      /* Now update the exec info content based upon the state
                 of each line as indicated by the source content.  */
              mode = src_element->which_element.source.has_break;
              if (mode & TUI_BP_HIT)
                element->which_element.simple_string[TUI_BP_HIT_POS] =
                  (mode & TUI_BP_HARDWARE) ? 'H' : 'B';
              else if (mode & (TUI_BP_ENABLED | TUI_BP_DISABLED))
                element->which_element.simple_string[TUI_BP_HIT_POS] =
                  (mode & TUI_BP_HARDWARE) ? 'h' : 'b';

              if (mode & TUI_BP_ENABLED)
                element->which_element.simple_string[TUI_BP_BREAK_POS] = '+';
              else if (mode & TUI_BP_DISABLED)
                element->which_element.simple_string[TUI_BP_BREAK_POS] = '-';

              if (src_element->which_element.source.is_exec_point)
                element->which_element.simple_string[TUI_EXEC_POS] = '>';
	    }
	  exec_info_ptr->content_size = win_info->generic.content_size;
	}
      else
	ret = TUI_FAILURE;
    }

  return ret;
}