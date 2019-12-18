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
struct symtab_and_line {scalar_t__ pc; scalar_t__ end; } ;
struct symbol {int dummy; } ;
typedef  int /*<<< orphan*/  asection ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ BLOCK_END (int /*<<< orphan*/ ) ; 
 scalar_t__ BLOCK_START (int /*<<< orphan*/ ) ; 
 scalar_t__ FUNCTION_START_OFFSET ; 
 scalar_t__ SKIP_PROLOGUE (scalar_t__) ; 
 int /*<<< orphan*/ * SYMBOL_BFD_SECTION (struct symbol*) ; 
 int /*<<< orphan*/  SYMBOL_BLOCK_VALUE (struct symbol*) ; 
 struct symtab_and_line find_pc_sect_line (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fixup_symbol_section (struct symbol*,int /*<<< orphan*/ *) ; 
 scalar_t__ overlay_mapped_address (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ overlay_unmapped_address (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  section_is_mapped (int /*<<< orphan*/ *) ; 
 scalar_t__ section_is_overlay (int /*<<< orphan*/ *) ; 

struct symtab_and_line
find_function_start_sal (struct symbol *sym, int funfirstline)
{
  CORE_ADDR pc;
  struct symtab_and_line sal;

  pc = BLOCK_START (SYMBOL_BLOCK_VALUE (sym));
  fixup_symbol_section (sym, NULL);
  if (funfirstline)
    {				/* skip "first line" of function (which is actually its prologue) */
      asection *section = SYMBOL_BFD_SECTION (sym);
      /* If function is in an unmapped overlay, use its unmapped LMA
         address, so that SKIP_PROLOGUE has something unique to work on */
      if (section_is_overlay (section) &&
	  !section_is_mapped (section))
	pc = overlay_unmapped_address (pc, section);

      pc += FUNCTION_START_OFFSET;
      pc = SKIP_PROLOGUE (pc);

      /* For overlays, map pc back into its mapped VMA range */
      pc = overlay_mapped_address (pc, section);
    }
  sal = find_pc_sect_line (pc, SYMBOL_BFD_SECTION (sym), 0);

  /* Check if SKIP_PROLOGUE left us in mid-line, and the next
     line is still part of the same function.  */
  if (sal.pc != pc
      && BLOCK_START (SYMBOL_BLOCK_VALUE (sym)) <= sal.end
      && sal.end < BLOCK_END (SYMBOL_BLOCK_VALUE (sym)))
    {
      /* First pc of next line */
      pc = sal.end;
      /* Recalculate the line number (might not be N+1).  */
      sal = find_pc_sect_line (pc, SYMBOL_BFD_SECTION (sym), 0);
    }
  sal.pc = pc;

  return sal;
}