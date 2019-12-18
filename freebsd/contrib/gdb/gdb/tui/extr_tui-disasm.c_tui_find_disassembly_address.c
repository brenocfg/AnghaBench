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
struct tui_asm_line {scalar_t__ addr; int /*<<< orphan*/  insn; int /*<<< orphan*/  addr_string; } ;
struct minimal_symbol {int dummy; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ SYMBOL_VALUE_ADDRESS (struct minimal_symbol*) ; 
 scalar_t__ alloca (int) ; 
 struct minimal_symbol* lookup_minimal_symbol_by_pc_section (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct tui_asm_line*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ tui_disassemble (struct tui_asm_line*,scalar_t__,int) ; 
 int /*<<< orphan*/  xfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static CORE_ADDR
tui_find_disassembly_address (CORE_ADDR pc, int from)
{
  CORE_ADDR new_low;
  int max_lines;
  int i;
  struct tui_asm_line* asm_lines;

  max_lines = (from > 0) ? from : - from;
  if (max_lines <= 1)
     return pc;

  asm_lines = (struct tui_asm_line*) alloca (sizeof (struct tui_asm_line)
                                         * max_lines);
  memset (asm_lines, 0, sizeof (struct tui_asm_line) * max_lines);

  new_low = pc;
  if (from > 0)
    {
      tui_disassemble (asm_lines, pc, max_lines);
      new_low = asm_lines[max_lines - 1].addr;
    }
  else
    {
      CORE_ADDR last_addr;
      int pos;
      struct minimal_symbol* msymbol;
              
      /* Find backward an address which is a symbol
         and for which disassembling from that address will fill
         completely the window.  */
      pos = max_lines - 1;
      do {
         new_low -= 1 * max_lines;
         msymbol = lookup_minimal_symbol_by_pc_section (new_low, 0);

         if (msymbol)
            new_low = SYMBOL_VALUE_ADDRESS (msymbol);
         else
            new_low += 1 * max_lines;

         tui_disassemble (asm_lines, new_low, max_lines);
         last_addr = asm_lines[pos].addr;
      } while (last_addr > pc && msymbol);

      /* Scan forward disassembling one instruction at a time
         until the last visible instruction of the window
         matches the pc.  We keep the disassembled instructions
         in the 'lines' window and shift it downward (increasing
         its addresses).  */
      if (last_addr < pc)
        do
          {
            CORE_ADDR next_addr;
                 
            pos++;
            if (pos >= max_lines)
              pos = 0;

            next_addr = tui_disassemble (&asm_lines[pos], last_addr, 1);

            /* If there are some problems while disassembling exit.  */
            if (next_addr <= last_addr)
              break;
            last_addr = next_addr;
          } while (last_addr <= pc);
      pos++;
      if (pos >= max_lines)
         pos = 0;
      new_low = asm_lines[pos].addr;
    }
  for (i = 0; i < max_lines; i++)
    {
      xfree (asm_lines[i].addr_string);
      xfree (asm_lines[i].insn);
    }
  return new_low;
}