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
struct symtab_and_line {scalar_t__ pc; scalar_t__ line; scalar_t__ end; int /*<<< orphan*/  section; int /*<<< orphan*/  symtab; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  find_line_pc (int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ; 
 struct symtab_and_line find_pc_sect_line (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
find_line_pc_range (struct symtab_and_line sal, CORE_ADDR *startptr,
		    CORE_ADDR *endptr)
{
  CORE_ADDR startaddr;
  struct symtab_and_line found_sal;

  startaddr = sal.pc;
  if (startaddr == 0 && !find_line_pc (sal.symtab, sal.line, &startaddr))
    return 0;

  /* This whole function is based on address.  For example, if line 10 has
     two parts, one from 0x100 to 0x200 and one from 0x300 to 0x400, then
     "info line *0x123" should say the line goes from 0x100 to 0x200
     and "info line *0x355" should say the line goes from 0x300 to 0x400.
     This also insures that we never give a range like "starts at 0x134
     and ends at 0x12c".  */

  found_sal = find_pc_sect_line (startaddr, sal.section, 0);
  if (found_sal.line != sal.line)
    {
      /* The specified line (sal) has zero bytes.  */
      *startptr = found_sal.pc;
      *endptr = found_sal.pc;
    }
  else
    {
      *startptr = found_sal.pc;
      *endptr = found_sal.end;
    }
  return 1;
}