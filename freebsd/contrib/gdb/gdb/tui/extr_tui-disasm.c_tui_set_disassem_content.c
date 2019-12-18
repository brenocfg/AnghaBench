#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ addr; } ;
struct tui_source_element {char* line; int is_exec_point; int has_break; TYPE_6__ line_or_addr; } ;
struct TYPE_13__ {scalar_t__ addr; } ;
struct TYPE_14__ {struct tui_source_element source; TYPE_4__ locator; } ;
struct tui_win_element {TYPE_5__ which_element; } ;
struct tui_gen_win_info {scalar_t__* content; } ;
struct tui_asm_line {char* addr_string; char* insn; scalar_t__ addr; } ;
typedef  enum tui_status { ____Placeholder_tui_status } tui_status ;
struct TYPE_16__ {int height; int width; int content_size; scalar_t__* content; } ;
struct TYPE_10__ {scalar_t__ addr; } ;
struct TYPE_11__ {int horizontal_offset; TYPE_1__ start_line_or_addr; } ;
struct TYPE_12__ {TYPE_2__ source_info; } ;
struct TYPE_17__ {TYPE_7__ generic; TYPE_3__ detail; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 TYPE_8__* TUI_DISASM_WIN ; 
 int TUI_FAILURE ; 
 int TUI_SUCCESS ; 
 scalar_t__ alloca (int) ; 
 scalar_t__ breakpoint_here_p (scalar_t__) ; 
 int /*<<< orphan*/  memset (struct tui_asm_line*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ no_breakpoint_here ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 int tui_alloc_source_buffer (TYPE_8__*) ; 
 int tui_default_tab_len () ; 
 int /*<<< orphan*/  tui_disassemble (struct tui_asm_line*,scalar_t__,int) ; 
 struct tui_gen_win_info* tui_locator_win_info_ptr () ; 
 int /*<<< orphan*/  xfree (char*) ; 

enum tui_status
tui_set_disassem_content (CORE_ADDR pc)
{
  enum tui_status ret = TUI_FAILURE;
  int i;
  int offset = TUI_DISASM_WIN->detail.source_info.horizontal_offset;
  int line_width, max_lines;
  CORE_ADDR cur_pc;
  struct tui_gen_win_info * locator = tui_locator_win_info_ptr ();
  int tab_len = tui_default_tab_len ();
  struct tui_asm_line* asm_lines;
  int insn_pos;
  int addr_size, max_size;
  char* line;
  
  if (pc == 0)
    return TUI_FAILURE;

  ret = tui_alloc_source_buffer (TUI_DISASM_WIN);
  if (ret != TUI_SUCCESS)
    return ret;

  TUI_DISASM_WIN->detail.source_info.start_line_or_addr.addr = pc;
  cur_pc = (CORE_ADDR)
    (((struct tui_win_element *) locator->content[0])->which_element.locator.addr);

  max_lines = TUI_DISASM_WIN->generic.height - 2;	/* account for hilite */

  /* Get temporary table that will hold all strings (addr & insn).  */
  asm_lines = (struct tui_asm_line*) alloca (sizeof (struct tui_asm_line)
                                         * max_lines);
  memset (asm_lines, 0, sizeof (struct tui_asm_line) * max_lines);

  line_width = TUI_DISASM_WIN->generic.width - 1;

  tui_disassemble (asm_lines, pc, max_lines);

  /* See what is the maximum length of an address and of a line.  */
  addr_size = 0;
  max_size = 0;
  for (i = 0; i < max_lines; i++)
    {
      size_t len = strlen (asm_lines[i].addr_string);
      if (len > addr_size)
        addr_size = len;

      len = strlen (asm_lines[i].insn) + tab_len;
      if (len > max_size)
        max_size = len;
    }
  max_size += addr_size + tab_len;

  /* Allocate memory to create each line.  */
  line = (char*) alloca (max_size);
  insn_pos = (1 + (addr_size / tab_len)) * tab_len;

  /* Now construct each line */
  for (i = 0; i < max_lines; i++)
    {
      struct tui_win_element * element;
      struct tui_source_element* src;
      int cur_len;

      element = (struct tui_win_element *) TUI_DISASM_WIN->generic.content[i];
      src = &element->which_element.source;
      strcpy (line, asm_lines[i].addr_string);
      cur_len = strlen (line);

      /* Add spaces to make the instructions start on the same column */
      while (cur_len < insn_pos)
        {
          strcat (line, " ");
          cur_len++;
        }

      strcat (line, asm_lines[i].insn);

      /* Now copy the line taking the offset into account */
      if (strlen (line) > offset)
        strcpy (src->line, &line[offset]);
      else
        src->line[0] = '\0';

      src->line_or_addr.addr = asm_lines[i].addr;
      src->is_exec_point = asm_lines[i].addr == cur_pc;

      /* See whether there is a breakpoint installed.  */
      src->has_break = (!src->is_exec_point
                       && breakpoint_here_p (pc) != no_breakpoint_here);

      xfree (asm_lines[i].addr_string);
      xfree (asm_lines[i].insn);
    }
  TUI_DISASM_WIN->generic.content_size = i;
  return TUI_SUCCESS;
}