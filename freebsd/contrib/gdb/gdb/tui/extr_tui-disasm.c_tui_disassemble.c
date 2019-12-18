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
struct ui_file {int dummy; } ;
struct tui_asm_line {void* insn; void* addr_string; scalar_t__ addr; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ gdb_print_insn (scalar_t__,struct ui_file*) ; 
 int /*<<< orphan*/  print_address (scalar_t__,struct ui_file*) ; 
 int /*<<< orphan*/  tui_file_get_strbuf (struct ui_file*) ; 
 struct ui_file* tui_sfileopen (int) ; 
 int /*<<< orphan*/  ui_file_delete (struct ui_file*) ; 
 int /*<<< orphan*/  ui_file_rewind (struct ui_file*) ; 
 int /*<<< orphan*/  xfree (void*) ; 
 void* xstrdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static CORE_ADDR
tui_disassemble (struct tui_asm_line* asm_lines, CORE_ADDR pc, int count)
{
  struct ui_file *gdb_dis_out;

  /* now init the ui_file structure */
  gdb_dis_out = tui_sfileopen (256);

  /* Now construct each line */
  for (; count > 0; count--, asm_lines++)
    {
      if (asm_lines->addr_string)
        xfree (asm_lines->addr_string);
      if (asm_lines->insn)
        xfree (asm_lines->insn);
      
      print_address (pc, gdb_dis_out);
      asm_lines->addr = pc;
      asm_lines->addr_string = xstrdup (tui_file_get_strbuf (gdb_dis_out));

      ui_file_rewind (gdb_dis_out);

      pc = pc + gdb_print_insn (pc, gdb_dis_out);

      asm_lines->insn = xstrdup (tui_file_get_strbuf (gdb_dis_out));

      /* reset the buffer to empty */
      ui_file_rewind (gdb_dis_out);
    }
  ui_file_delete (gdb_dis_out);
  return pc;
}