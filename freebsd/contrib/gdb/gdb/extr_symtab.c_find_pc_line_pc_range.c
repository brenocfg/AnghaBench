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
struct symtab_and_line {scalar_t__ symtab; int /*<<< orphan*/  end; int /*<<< orphan*/  pc; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 struct symtab_and_line find_pc_line (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
find_pc_line_pc_range (CORE_ADDR pc, CORE_ADDR *startptr, CORE_ADDR *endptr)
{
  struct symtab_and_line sal;
  sal = find_pc_line (pc, 0);
  *startptr = sal.pc;
  *endptr = sal.end;
  return sal.symtab != 0;
}