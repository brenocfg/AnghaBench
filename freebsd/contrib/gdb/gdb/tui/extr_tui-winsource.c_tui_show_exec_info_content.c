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
struct TYPE_5__ {struct tui_gen_win_info* execution_info; } ;
struct TYPE_6__ {TYPE_2__ source_info; } ;
struct tui_win_info {TYPE_3__ detail; } ;
struct TYPE_4__ {int /*<<< orphan*/  simple_string; } ;
struct tui_win_element {TYPE_1__ which_element; } ;
struct tui_gen_win_info {int content_size; int /*<<< orphan*/  content_in_use; scalar_t__* content; int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  mvwaddstr (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tui_refresh_win (struct tui_gen_win_info*) ; 
 int /*<<< orphan*/  werase (int /*<<< orphan*/ ) ; 

void
tui_show_exec_info_content (struct tui_win_info * win_info)
{
  struct tui_gen_win_info * exec_info = win_info->detail.source_info.execution_info;
  int cur_line;

  werase (exec_info->handle);
  tui_refresh_win (exec_info);
  for (cur_line = 1; (cur_line <= exec_info->content_size); cur_line++)
    mvwaddstr (exec_info->handle,
	       cur_line,
	       0,
	       ((struct tui_win_element *)
		exec_info->content[cur_line - 1])->which_element.simple_string);
  tui_refresh_win (exec_info);
  exec_info->content_in_use = TRUE;
}