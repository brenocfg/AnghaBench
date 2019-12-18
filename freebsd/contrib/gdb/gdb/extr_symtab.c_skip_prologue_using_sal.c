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
 scalar_t__ FUNCTION_START_OFFSET ; 
 struct symtab_and_line find_pc_line (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_pc_partial_function (scalar_t__,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*) ; 

CORE_ADDR
skip_prologue_using_sal (CORE_ADDR func_addr)
{
  struct symtab_and_line prologue_sal;
  CORE_ADDR start_pc;
  CORE_ADDR end_pc;

  /* Get an initial range for the function.  */
  find_pc_partial_function (func_addr, NULL, &start_pc, &end_pc);
  start_pc += FUNCTION_START_OFFSET;

  prologue_sal = find_pc_line (start_pc, 0);
  if (prologue_sal.line != 0)
    {
      while (prologue_sal.end < end_pc)
	{
	  struct symtab_and_line sal;

	  sal = find_pc_line (prologue_sal.end, 0);
	  if (sal.line == 0)
	    break;
	  /* Assume that a consecutive SAL for the same (or larger)
	     line mark the prologue -> body transition.  */
	  if (sal.line >= prologue_sal.line)
	    break;
	  /* The case in which compiler's optimizer/scheduler has
	     moved instructions into the prologue.  We look ahead in
	     the function looking for address ranges whose
	     corresponding line number is less the first one that we
	     found for the function.  This is more conservative then
	     refine_prologue_limit which scans a large number of SALs
	     looking for any in the prologue */
	  prologue_sal = sal;
	}
    }
  return prologue_sal.end;
}