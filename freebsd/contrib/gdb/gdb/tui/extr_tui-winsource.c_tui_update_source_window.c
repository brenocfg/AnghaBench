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
typedef  union tui_line_or_address {int dummy; } tui_line_or_address ;
struct TYPE_3__ {scalar_t__ horizontal_offset; } ;
struct TYPE_4__ {TYPE_1__ source_info; } ;
struct tui_win_info {TYPE_2__ detail; } ;
struct symtab {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tui_update_source_window_as_is (struct tui_win_info*,struct symtab*,union tui_line_or_address,int) ; 

void
tui_update_source_window (struct tui_win_info * win_info, struct symtab *s,
			  union tui_line_or_address line_or_addr, int noerror)
{
  win_info->detail.source_info.horizontal_offset = 0;
  tui_update_source_window_as_is (win_info, s, line_or_addr, noerror);

  return;
}