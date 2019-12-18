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
struct gdbarch_tdep {int ppc_gp0_regnum; int ppc_gplast_regnum; int ppc_ps_regnum; int ppc_cr_regnum; int ppc_lr_regnum; int ppc_ctr_regnum; int ppc_xer_regnum; int ppc_fpscr_regnum; int ppc_mq_regnum; } ;

/* Variables and functions */
 int CR ; 
 int CTR ; 
 int FP0_REGNUM ; 
 int FPLAST_REGNUM ; 
 int FPR0 ; 
 int FPSCR ; 
 int IAR ; 
 int LR ; 
 int MQ ; 
 int MSR ; 
 int PC_REGNUM ; 
 int XER ; 
 int /*<<< orphan*/  current_gdbarch ; 
 struct gdbarch_tdep* gdbarch_tdep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
regmap (int regno, int *isfloat)
{
  struct gdbarch_tdep *tdep = gdbarch_tdep (current_gdbarch);

  *isfloat = 0;
  if (tdep->ppc_gp0_regnum <= regno && regno <= tdep->ppc_gplast_regnum)
    return regno;
  else if (FP0_REGNUM <= regno && regno <= FPLAST_REGNUM)
    {
      *isfloat = 1;
      return regno - FP0_REGNUM + FPR0;
    }
  else if (regno == PC_REGNUM)
    return IAR;
  else if (regno == tdep->ppc_ps_regnum)
    return MSR;
  else if (regno == tdep->ppc_cr_regnum)
    return CR;
  else if (regno == tdep->ppc_lr_regnum)
    return LR;
  else if (regno == tdep->ppc_ctr_regnum)
    return CTR;
  else if (regno == tdep->ppc_xer_regnum)
    return XER;
  else if (regno == tdep->ppc_fpscr_regnum)
    return FPSCR;
  else if (tdep->ppc_mq_regnum >= 0 && regno == tdep->ppc_mq_regnum)
    return MQ;
  else
    return -1;
}