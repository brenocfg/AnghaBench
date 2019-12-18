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
union tui_line_or_address {int line_no; } ;
struct symtab {int dummy; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
#define  DISASSEM_COMMAND 129 
#define  DISASSEM_DATA_COMMAND 128 
 int /*<<< orphan*/  FALSE ; 
 int SRC_DISASSEM_COMMAND ; 
 int /*<<< orphan*/  find_line_pc (struct symtab*,int,int /*<<< orphan*/ *) ; 
 int tui_current_layout () ; 
 int /*<<< orphan*/  tui_show_disassem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tui_show_symtab_source (struct symtab*,union tui_line_or_address,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tui_update_source_windows_with_addr (int /*<<< orphan*/ ) ; 

void
tui_update_source_windows_with_line (struct symtab *s, int line)
{
  CORE_ADDR pc;
  union tui_line_or_address l;
  
  switch (tui_current_layout ())
    {
    case DISASSEM_COMMAND:
    case DISASSEM_DATA_COMMAND:
      find_line_pc (s, line, &pc);
      tui_update_source_windows_with_addr (pc);
      break;
    default:
      l.line_no = line;
      tui_show_symtab_source (s, l, FALSE);
      if (tui_current_layout () == SRC_DISASSEM_COMMAND)
	{
	  find_line_pc (s, line, &pc);
	  tui_show_disassem (pc);
	}
      break;
    }

  return;
}