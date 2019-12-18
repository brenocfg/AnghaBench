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
struct reg {scalar_t__ pseudo; } ;

/* Variables and functions */

__attribute__((used)) static int
num_pseudo_registers (const struct reg *reg_list, int num_tot_regs)
{
  int i;
  int npregs = 0;

  for (i = 0; i < num_tot_regs; i++)
    if (reg_list[i].pseudo)
      npregs ++; 

  return npregs;
}