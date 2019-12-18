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
struct TYPE_5__ {TYPE_1__* execution_info; } ;
struct TYPE_6__ {TYPE_2__ source_info; } ;
struct tui_win_info {TYPE_3__ detail; } ;
struct TYPE_4__ {int /*<<< orphan*/  content_in_use; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  tui_erase_exec_info_content (struct tui_win_info*) ; 

void
tui_clear_exec_info_content (struct tui_win_info * win_info)
{
  win_info->detail.source_info.execution_info->content_in_use = FALSE;
  tui_erase_exec_info_content (win_info);

  return;
}