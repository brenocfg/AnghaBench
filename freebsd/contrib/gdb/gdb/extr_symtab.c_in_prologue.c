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
struct symtab_and_line {scalar_t__ line; scalar_t__ end; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ SKIP_PROLOGUE (scalar_t__) ; 
 struct symtab_and_line find_pc_line (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_pc_partial_function (scalar_t__,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*) ; 

int
in_prologue (CORE_ADDR pc, CORE_ADDR func_start)
{
  struct symtab_and_line sal;
  CORE_ADDR func_addr, func_end;

  /* We have several sources of information we can consult to figure
     this out.
     - Compilers usually emit line number info that marks the prologue
       as its own "source line".  So the ending address of that "line"
       is the end of the prologue.  If available, this is the most
       reliable method.
     - The minimal symbols and partial symbols, which can usually tell
       us the starting and ending addresses of a function.
     - If we know the function's start address, we can call the
       architecture-defined SKIP_PROLOGUE function to analyze the
       instruction stream and guess where the prologue ends.
     - Our `func_start' argument; if non-zero, this is the caller's
       best guess as to the function's entry point.  At the time of
       this writing, handle_inferior_event doesn't get this right, so
       it should be our last resort.  */

  /* Consult the partial symbol table, to find which function
     the PC is in.  */
  if (! find_pc_partial_function (pc, NULL, &func_addr, &func_end))
    {
      CORE_ADDR prologue_end;

      /* We don't even have minsym information, so fall back to using
         func_start, if given.  */
      if (! func_start)
	return 1;		/* We *might* be in a prologue.  */

      prologue_end = SKIP_PROLOGUE (func_start);

      return func_start <= pc && pc < prologue_end;
    }

  /* If we have line number information for the function, that's
     usually pretty reliable.  */
  sal = find_pc_line (func_addr, 0);

  /* Now sal describes the source line at the function's entry point,
     which (by convention) is the prologue.  The end of that "line",
     sal.end, is the end of the prologue.

     Note that, for functions whose source code is all on a single
     line, the line number information doesn't always end up this way.
     So we must verify that our purported end-of-prologue address is
     *within* the function, not at its start or end.  */
  if (sal.line == 0
      || sal.end <= func_addr
      || func_end <= sal.end)
    {
      /* We don't have any good line number info, so use the minsym
	 information, together with the architecture-specific prologue
	 scanning code.  */
      CORE_ADDR prologue_end = SKIP_PROLOGUE (func_addr);

      return func_addr <= pc && pc < prologue_end;
    }

  /* We have line number info, and it looks good.  */
  return func_addr <= pc && pc < sal.end;
}