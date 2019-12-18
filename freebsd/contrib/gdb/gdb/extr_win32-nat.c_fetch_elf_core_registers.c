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
typedef  int /*<<< orphan*/  CORE_ADDR ;
typedef  int /*<<< orphan*/  CONTEXT ;

/* Variables and functions */
 int NUM_REGS ; 
 int /*<<< orphan*/  error (char*,unsigned int) ; 
 int* mappings ; 
 int /*<<< orphan*/  supply_register (int,char*) ; 

__attribute__((used)) static void
fetch_elf_core_registers (char *core_reg_sect,
			  unsigned core_reg_size,
			  int which,
			  CORE_ADDR reg_addr)
{
  int r;
  if (core_reg_size < sizeof (CONTEXT))
    {
      error ("Core file register section too small (%u bytes).", core_reg_size);
      return;
    }
  for (r = 0; r < NUM_REGS; r++)
    supply_register (r, core_reg_sect + mappings[r]);
}