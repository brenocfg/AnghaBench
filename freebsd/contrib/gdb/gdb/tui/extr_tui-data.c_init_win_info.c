#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  void* tui_win_content ;
struct TYPE_10__ {int /*<<< orphan*/  curch; int /*<<< orphan*/  cur_line; } ;
struct TYPE_9__ {int regs_column_count; int /*<<< orphan*/  current_group; void* display_regs; int /*<<< orphan*/  regs_display_type; int /*<<< orphan*/  regs_content_count; void* regs_content; int /*<<< orphan*/  data_content_count; void* data_content; } ;
struct TYPE_7__ {int /*<<< orphan*/  addr; } ;
struct TYPE_8__ {int /*<<< orphan*/  filename; TYPE_1__ start_line_or_addr; int /*<<< orphan*/  horizontal_offset; void* has_locator; struct tui_gen_win_info* execution_info; } ;
struct TYPE_11__ {int /*<<< orphan*/ * opaque; TYPE_4__ command_info; TYPE_3__ data_display_info; TYPE_2__ source_info; } ;
struct TYPE_12__ {int type; } ;
struct tui_win_info {TYPE_5__ detail; TYPE_6__ generic; void* is_highlighted; void* can_highlight; } ;
struct tui_gen_win_info {int dummy; } ;

/* Variables and functions */
#define  CMD_WIN 131 
#define  DATA_WIN 130 
#define  DISASSEM_WIN 129 
 void* FALSE ; 
#define  SRC_WIN 128 
 int /*<<< orphan*/  TUI_UNDEFINED_REGS ; 
 int /*<<< orphan*/  tui_init_generic_part (TYPE_6__*) ; 

void
init_win_info (struct tui_win_info * win_info)
{
  tui_init_generic_part (&win_info->generic);
  win_info->can_highlight =
    win_info->is_highlighted = FALSE;
  switch (win_info->generic.type)
    {
    case SRC_WIN:
    case DISASSEM_WIN:
      win_info->detail.source_info.execution_info = (struct tui_gen_win_info *) NULL;
      win_info->detail.source_info.has_locator = FALSE;
      win_info->detail.source_info.horizontal_offset = 0;
      win_info->detail.source_info.start_line_or_addr.addr = 0;
      win_info->detail.source_info.filename = 0;
      break;
    case DATA_WIN:
      win_info->detail.data_display_info.data_content = (tui_win_content) NULL;
      win_info->detail.data_display_info.data_content_count = 0;
      win_info->detail.data_display_info.regs_content = (tui_win_content) NULL;
      win_info->detail.data_display_info.regs_content_count = 0;
      win_info->detail.data_display_info.regs_display_type =
	TUI_UNDEFINED_REGS;
      win_info->detail.data_display_info.regs_column_count = 1;
      win_info->detail.data_display_info.display_regs = FALSE;
      win_info->detail.data_display_info.current_group = 0;
      break;
    case CMD_WIN:
      win_info->detail.command_info.cur_line = 0;
      win_info->detail.command_info.curch = 0;
      break;
    default:
      win_info->detail.opaque = NULL;
      break;
    }
}