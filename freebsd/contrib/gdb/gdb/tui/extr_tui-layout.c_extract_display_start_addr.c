#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct symtab_and_line {int /*<<< orphan*/  symtab; } ;
typedef  enum tui_layout_type { ____Placeholder_tui_layout_type } tui_layout_type ;
struct TYPE_12__ {int /*<<< orphan*/  addr; } ;
struct TYPE_13__ {TYPE_4__ start_line_or_addr; } ;
struct TYPE_14__ {TYPE_5__ source_info; } ;
struct TYPE_16__ {TYPE_6__ detail; } ;
struct TYPE_9__ {int /*<<< orphan*/  line_no; } ;
struct TYPE_10__ {TYPE_1__ start_line_or_addr; } ;
struct TYPE_11__ {TYPE_2__ source_info; } ;
struct TYPE_15__ {TYPE_3__ detail; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
#define  DISASSEM_COMMAND 132 
#define  DISASSEM_DATA_COMMAND 131 
#define  SRC_COMMAND 130 
#define  SRC_DATA_COMMAND 129 
#define  SRC_DISASSEM_COMMAND 128 
 TYPE_8__* TUI_DISASM_WIN ; 
 TYPE_7__* TUI_SRC_WIN ; 
 int /*<<< orphan*/  find_line_pc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct symtab_and_line get_current_source_symtab_and_line () ; 
 int tui_current_layout () ; 

__attribute__((used)) static CORE_ADDR
extract_display_start_addr (void)
{
  enum tui_layout_type cur_layout = tui_current_layout ();
  CORE_ADDR addr;
  CORE_ADDR pc;
  struct symtab_and_line cursal = get_current_source_symtab_and_line ();

  switch (cur_layout)
    {
    case SRC_COMMAND:
    case SRC_DATA_COMMAND:
      find_line_pc (cursal.symtab,
		    TUI_SRC_WIN->detail.source_info.start_line_or_addr.line_no,
		    &pc);
      addr = pc;
      break;
    case DISASSEM_COMMAND:
    case SRC_DISASSEM_COMMAND:
    case DISASSEM_DATA_COMMAND:
      addr = TUI_DISASM_WIN->detail.source_info.start_line_or_addr.addr;
      break;
    default:
      addr = 0;
      break;
    }

  return addr;
}