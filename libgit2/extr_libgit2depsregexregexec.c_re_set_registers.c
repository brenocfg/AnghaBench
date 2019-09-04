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
struct re_registers {unsigned int num_regs; int /*<<< orphan*/ * end; int /*<<< orphan*/ * start; } ;
struct re_pattern_buffer {int /*<<< orphan*/  regs_allocated; } ;
typedef  int /*<<< orphan*/  regoff_t ;

/* Variables and functions */
 int /*<<< orphan*/  REGS_REALLOCATE ; 
 int /*<<< orphan*/  REGS_UNALLOCATED ; 

void
re_set_registers (struct re_pattern_buffer *bufp,
		  struct re_registers *regs,
		  unsigned num_regs,
		  regoff_t *starts,
		  regoff_t *ends)
{
  if (num_regs)
    {
      bufp->regs_allocated = REGS_REALLOCATE;
      regs->num_regs = num_regs;
      regs->start = starts;
      regs->end = ends;
    }
  else
    {
      bufp->regs_allocated = REGS_UNALLOCATED;
      regs->num_regs = 0;
      regs->start = regs->end = (regoff_t *) 0;
    }
}