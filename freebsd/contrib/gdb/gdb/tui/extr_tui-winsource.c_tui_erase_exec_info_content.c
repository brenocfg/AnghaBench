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
struct TYPE_3__ {struct tui_gen_win_info* execution_info; } ;
struct TYPE_4__ {TYPE_1__ source_info; } ;
struct tui_win_info {TYPE_2__ detail; } ;
struct tui_gen_win_info {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  tui_refresh_win (struct tui_gen_win_info*) ; 
 int /*<<< orphan*/  werase (int /*<<< orphan*/ ) ; 

void
tui_erase_exec_info_content (struct tui_win_info * win_info)
{
  struct tui_gen_win_info * exec_info = win_info->detail.source_info.execution_info;

  werase (exec_info->handle);
  tui_refresh_win (exec_info);
}