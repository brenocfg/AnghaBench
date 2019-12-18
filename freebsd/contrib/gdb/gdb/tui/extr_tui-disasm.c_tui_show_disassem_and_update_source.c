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
struct symtab_and_line {TYPE_1__* symtab; int /*<<< orphan*/  line; } ;
struct TYPE_2__ {char* filename; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 scalar_t__ SRC_DISASSEM_COMMAND ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TUI_SRC_WIN ; 
 struct symtab_and_line find_pc_line (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_current_source_symtab_and_line (struct symtab_and_line*) ; 
 scalar_t__ tui_current_layout () ; 
 int /*<<< orphan*/  tui_show_disassem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tui_update_locator_filename (char*) ; 
 int /*<<< orphan*/  tui_update_source_window (int /*<<< orphan*/ ,TYPE_1__*,union tui_line_or_address,int /*<<< orphan*/ ) ; 

void
tui_show_disassem_and_update_source (CORE_ADDR start_addr)
{
  struct symtab_and_line sal;

  tui_show_disassem (start_addr);
  if (tui_current_layout () == SRC_DISASSEM_COMMAND)
    {
      union tui_line_or_address val;

      /*
         ** Update what is in the source window if it is displayed too,
         ** note that it follows what is in the disassembly window and visa-versa
       */
      sal = find_pc_line (start_addr, 0);
      val.line_no = sal.line;
      tui_update_source_window (TUI_SRC_WIN, sal.symtab, val, TRUE);
      if (sal.symtab)
	{
	  set_current_source_symtab_and_line (&sal);
	  tui_update_locator_filename (sal.symtab->filename);
	}
      else
	tui_update_locator_filename ("?");
    }

  return;
}