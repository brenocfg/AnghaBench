#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
union tui_line_or_address {int /*<<< orphan*/  line_no; } ;
struct tui_win_info {int dummy; } ;
struct symtab_and_line {int /*<<< orphan*/  symtab; int /*<<< orphan*/  line; } ;
struct TYPE_2__ {int count; scalar_t__* list; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
#define  DISASSEM_COMMAND 130 
#define  DISASSEM_DATA_COMMAND 129 
 int /*<<< orphan*/  EMPTY_SOURCE_PROMPT ; 
 int /*<<< orphan*/  FALSE ; 
#define  SRC_DISASSEM_COMMAND 128 
 struct symtab_and_line find_pc_line (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tui_clear_exec_info_content (struct tui_win_info*) ; 
 int /*<<< orphan*/  tui_clear_source_content (struct tui_win_info*,int /*<<< orphan*/ ) ; 
 int tui_current_layout () ; 
 int /*<<< orphan*/  tui_show_disassem (scalar_t__) ; 
 int /*<<< orphan*/  tui_show_disassem_and_update_source (scalar_t__) ; 
 int /*<<< orphan*/  tui_show_symtab_source (int /*<<< orphan*/ ,union tui_line_or_address,int /*<<< orphan*/ ) ; 
 TYPE_1__* tui_source_windows () ; 

void
tui_update_source_windows_with_addr (CORE_ADDR addr)
{
  if (addr != 0)
    {
      struct symtab_and_line sal;
      union tui_line_or_address l;
      
      switch (tui_current_layout ())
	{
	case DISASSEM_COMMAND:
	case DISASSEM_DATA_COMMAND:
	  tui_show_disassem (addr);
	  break;
	case SRC_DISASSEM_COMMAND:
	  tui_show_disassem_and_update_source (addr);
	  break;
	default:
	  sal = find_pc_line (addr, 0);
	  l.line_no = sal.line;
	  tui_show_symtab_source (sal.symtab, l, FALSE);
	  break;
	}
    }
  else
    {
      int i;

      for (i = 0; i < (tui_source_windows ())->count; i++)
	{
	  struct tui_win_info * win_info = (struct tui_win_info *) (tui_source_windows ())->list[i];

	  tui_clear_source_content (win_info, EMPTY_SOURCE_PROMPT);
	  tui_clear_exec_info_content (win_info);
	}
    }
}