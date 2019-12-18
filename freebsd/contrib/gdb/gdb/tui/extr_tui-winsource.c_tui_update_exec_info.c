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
struct tui_win_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tui_set_exec_info_content (struct tui_win_info*) ; 
 int /*<<< orphan*/  tui_show_exec_info_content (struct tui_win_info*) ; 

void
tui_update_exec_info (struct tui_win_info * win_info)
{
  tui_set_exec_info_content (win_info);
  tui_show_exec_info_content (win_info);
}