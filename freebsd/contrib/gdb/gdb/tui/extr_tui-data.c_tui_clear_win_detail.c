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
struct TYPE_11__ {int regs_column_count; int /*<<< orphan*/  display_regs; int /*<<< orphan*/  regs_display_type; int /*<<< orphan*/  regs_content_count; void* regs_content; int /*<<< orphan*/  data_content_count; void* data_content; } ;
struct TYPE_10__ {int /*<<< orphan*/  curch; int /*<<< orphan*/  cur_line; } ;
struct TYPE_8__ {int /*<<< orphan*/  addr; } ;
struct TYPE_9__ {int /*<<< orphan*/  horizontal_offset; TYPE_2__ start_line_or_addr; } ;
struct TYPE_12__ {TYPE_5__ data_display_info; TYPE_4__ command_info; TYPE_3__ source_info; } ;
struct TYPE_7__ {int type; } ;
struct tui_win_info {TYPE_6__ detail; TYPE_1__ generic; } ;

/* Variables and functions */
#define  CMD_WIN 131 
#define  DATA_WIN 130 
#define  DISASSEM_WIN 129 
 int /*<<< orphan*/  FALSE ; 
#define  SRC_WIN 128 
 int /*<<< orphan*/  TUI_UNDEFINED_REGS ; 

void
tui_clear_win_detail (struct tui_win_info * win_info)
{
  if (win_info != NULL)
    {
      switch (win_info->generic.type)
	{
	case SRC_WIN:
	case DISASSEM_WIN:
	  win_info->detail.source_info.start_line_or_addr.addr = 0;
	  win_info->detail.source_info.horizontal_offset = 0;
	  break;
	case CMD_WIN:
	  win_info->detail.command_info.cur_line =
	    win_info->detail.command_info.curch = 0;
	  break;
	case DATA_WIN:
	  win_info->detail.data_display_info.data_content =
	    (tui_win_content) NULL;
	  win_info->detail.data_display_info.data_content_count = 0;
	  win_info->detail.data_display_info.regs_content =
	    (tui_win_content) NULL;
	  win_info->detail.data_display_info.regs_content_count = 0;
	  win_info->detail.data_display_info.regs_display_type =
	    TUI_UNDEFINED_REGS;
	  win_info->detail.data_display_info.regs_column_count = 1;
	  win_info->detail.data_display_info.display_regs = FALSE;
	  break;
	default:
	  break;
	}
    }
}