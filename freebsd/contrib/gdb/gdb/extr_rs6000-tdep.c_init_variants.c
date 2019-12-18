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
struct variant {int nregs; int npregs; int /*<<< orphan*/  num_tot_regs; int /*<<< orphan*/  regs; scalar_t__ name; } ;

/* Variables and functions */
 int num_pseudo_registers (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int num_registers (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct variant* variants ; 

__attribute__((used)) static void
init_variants (void)
{
  struct variant *v;

  for (v = variants; v->name; v++)
    {
      if (v->nregs == -1)
        v->nregs = num_registers (v->regs, v->num_tot_regs);
      if (v->npregs == -1)
        v->npregs = num_pseudo_registers (v->regs, v->num_tot_regs);
    }  
}