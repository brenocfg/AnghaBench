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
struct reg {int offset; scalar_t__ size; } ;

/* Variables and functions */
 int num_registers ; 
 struct reg* reg_defs ; 
 int register_bytes ; 

void
set_register_cache (struct reg *regs, int n)
{
  int offset, i;
  
  reg_defs = regs;
  num_registers = n;

  offset = 0;
  for (i = 0; i < n; i++)
    {
      regs[i].offset = offset;
      offset += regs[i].size;
    }

  register_bytes = offset / 8;
}