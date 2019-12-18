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
struct rs6000_framedata {scalar_t__ saved_fpr; scalar_t__ saved_gpr; scalar_t__ saved_vr; scalar_t__ saved_ev; scalar_t__ lr_offset; scalar_t__ cr_offset; scalar_t__ vr_offset; scalar_t__ ev_offset; int fpr_offset; int gpr_offset; scalar_t__ vrsave_offset; } ;
struct gdbarch_tdep {int wordsize; int ppc_gp0_regnum; int ppc_vr0_regnum; int ppc_vrsave_regnum; int ppc_ev0_regnum; int ppc_ev31_regnum; size_t ppc_cr_regnum; size_t ppc_lr_regnum; } ;
struct frame_info {int dummy; } ;
typedef  int CORE_ADDR ;

/* Variables and functions */
 int DEPRECATED_FRAME_CHAIN (struct frame_info*) ; 
 int DEPRECATED_REGISTER_RAW_SIZE (int) ; 
 int FP0_REGNUM ; 
 int /*<<< orphan*/  current_gdbarch ; 
 int* deprecated_get_frame_saved_regs (struct frame_info*) ; 
 int /*<<< orphan*/  frame_saved_regs_zalloc (struct frame_info*) ; 
 struct gdbarch_tdep* gdbarch_tdep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_frame_func (struct frame_info*) ; 
 int /*<<< orphan*/  get_frame_pc (struct frame_info*) ; 
 int /*<<< orphan*/  skip_prologue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rs6000_framedata*) ; 

__attribute__((used)) static void
frame_get_saved_regs (struct frame_info *fi, struct rs6000_framedata *fdatap)
{
  CORE_ADDR frame_addr;
  struct rs6000_framedata work_fdata;
  struct gdbarch_tdep * tdep = gdbarch_tdep (current_gdbarch);
  int wordsize = tdep->wordsize;

  if (deprecated_get_frame_saved_regs (fi))
    return;

  if (fdatap == NULL)
    {
      fdatap = &work_fdata;
      (void) skip_prologue (get_frame_func (fi), get_frame_pc (fi), fdatap);
    }

  frame_saved_regs_zalloc (fi);

  /* If there were any saved registers, figure out parent's stack
     pointer.  */
  /* The following is true only if the frame doesn't have a call to
     alloca(), FIXME.  */

  if (fdatap->saved_fpr == 0
      && fdatap->saved_gpr == 0
      && fdatap->saved_vr == 0
      && fdatap->saved_ev == 0
      && fdatap->lr_offset == 0
      && fdatap->cr_offset == 0
      && fdatap->vr_offset == 0
      && fdatap->ev_offset == 0)
    frame_addr = 0;
  else
    /* NOTE: cagney/2002-04-14: The ->frame points to the inner-most
       address of the current frame.  Things might be easier if the
       ->frame pointed to the outer-most address of the frame.  In the
       mean time, the address of the prev frame is used as the base
       address of this frame.  */
    frame_addr = DEPRECATED_FRAME_CHAIN (fi);

  /* if != -1, fdatap->saved_fpr is the smallest number of saved_fpr.
     All fpr's from saved_fpr to fp31 are saved.  */

  if (fdatap->saved_fpr >= 0)
    {
      int i;
      CORE_ADDR fpr_addr = frame_addr + fdatap->fpr_offset;
      for (i = fdatap->saved_fpr; i < 32; i++)
	{
	  deprecated_get_frame_saved_regs (fi)[FP0_REGNUM + i] = fpr_addr;
	  fpr_addr += 8;
	}
    }

  /* if != -1, fdatap->saved_gpr is the smallest number of saved_gpr.
     All gpr's from saved_gpr to gpr31 are saved.  */

  if (fdatap->saved_gpr >= 0)
    {
      int i;
      CORE_ADDR gpr_addr = frame_addr + fdatap->gpr_offset;
      for (i = fdatap->saved_gpr; i < 32; i++)
	{
	  deprecated_get_frame_saved_regs (fi)[tdep->ppc_gp0_regnum + i] = gpr_addr;
	  gpr_addr += wordsize;
	}
    }

  /* if != -1, fdatap->saved_vr is the smallest number of saved_vr.
     All vr's from saved_vr to vr31 are saved.  */
  if (tdep->ppc_vr0_regnum != -1 && tdep->ppc_vrsave_regnum != -1)
    {
      if (fdatap->saved_vr >= 0)
	{
	  int i;
	  CORE_ADDR vr_addr = frame_addr + fdatap->vr_offset;
	  for (i = fdatap->saved_vr; i < 32; i++)
	    {
	      deprecated_get_frame_saved_regs (fi)[tdep->ppc_vr0_regnum + i] = vr_addr;
	      vr_addr += DEPRECATED_REGISTER_RAW_SIZE (tdep->ppc_vr0_regnum);
	    }
	}
    }

  /* if != -1, fdatap->saved_ev is the smallest number of saved_ev.
	All vr's from saved_ev to ev31 are saved. ?????	*/
  if (tdep->ppc_ev0_regnum != -1 && tdep->ppc_ev31_regnum != -1)
    {
      if (fdatap->saved_ev >= 0)
	{
	  int i;
	  CORE_ADDR ev_addr = frame_addr + fdatap->ev_offset;
	  for (i = fdatap->saved_ev; i < 32; i++)
	    {
	      deprecated_get_frame_saved_regs (fi)[tdep->ppc_ev0_regnum + i] = ev_addr;
              deprecated_get_frame_saved_regs (fi)[tdep->ppc_gp0_regnum + i] = ev_addr + 4;
	      ev_addr += DEPRECATED_REGISTER_RAW_SIZE (tdep->ppc_ev0_regnum);
            }
	}
    }

  /* If != 0, fdatap->cr_offset is the offset from the frame that holds
     the CR.  */
  if (fdatap->cr_offset != 0)
    deprecated_get_frame_saved_regs (fi)[tdep->ppc_cr_regnum] = frame_addr + fdatap->cr_offset;

  /* If != 0, fdatap->lr_offset is the offset from the frame that holds
     the LR.  */
  if (fdatap->lr_offset != 0)
    deprecated_get_frame_saved_regs (fi)[tdep->ppc_lr_regnum] = frame_addr + fdatap->lr_offset;

  /* If != 0, fdatap->vrsave_offset is the offset from the frame that holds
     the VRSAVE.  */
  if (fdatap->vrsave_offset != 0)
    deprecated_get_frame_saved_regs (fi)[tdep->ppc_vrsave_regnum] = frame_addr + fdatap->vrsave_offset;
}