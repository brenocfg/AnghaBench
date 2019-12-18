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

/* Variables and functions */
 int S390_NUM_REGS ; 
 int* regmap_fpregset ; 
 int* regmap_gregset ; 
 int s390_inferior_tid () ; 
 int /*<<< orphan*/  store_fpregs (int,int) ; 
 int /*<<< orphan*/  store_regs (int,int) ; 

void
store_inferior_registers (int regnum)
{
  int tid = s390_inferior_tid ();

  if (regnum == -1 
      || (regnum < S390_NUM_REGS && regmap_gregset[regnum] != -1))
    store_regs (tid, regnum);

  if (regnum == -1 
      || (regnum < S390_NUM_REGS && regmap_fpregset[regnum] != -1))
    store_fpregs (tid, regnum);
}