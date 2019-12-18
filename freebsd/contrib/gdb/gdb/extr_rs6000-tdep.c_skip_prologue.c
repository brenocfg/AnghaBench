#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rs6000_framedata {int saved_gpr; int saved_fpr; int saved_vr; int saved_ev; int alloca_reg; int frameless; int nosavedpc; long fpr_offset; long gpr_offset; unsigned long offset; long lr_offset; long cr_offset; long vrsave_offset; long vr_offset; long ev_offset; } ;
struct gdbarch_tdep {int ppc_gp0_regnum; } ;
struct bfd_arch_info {scalar_t__ mach; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int GET_SRC_REG (unsigned long) ; 
 long SIGNED_SHORT (unsigned long) ; 
 scalar_t__ bfd_mach_ppc_e500 ; 
 int /*<<< orphan*/  current_gdbarch ; 
 unsigned long extract_signed_integer (char*,int) ; 
 size_t find_pc_misc_function (scalar_t__) ; 
 struct bfd_arch_info* gdbarch_bfd_arch_info (int /*<<< orphan*/ ) ; 
 struct gdbarch_tdep* gdbarch_tdep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  main_name () ; 
 int /*<<< orphan*/  max_skip_non_prologue_insns ; 
 int /*<<< orphan*/  memset (struct rs6000_framedata*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* misc_function_vector ; 
 unsigned long read_memory_integer (scalar_t__,int) ; 
 scalar_t__ refine_prologue_limit (scalar_t__,scalar_t__) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ target_read_memory (scalar_t__,char*,int) ; 
 size_t tmp ; 

__attribute__((used)) static CORE_ADDR
skip_prologue (CORE_ADDR pc, CORE_ADDR lim_pc, struct rs6000_framedata *fdata)
{
  CORE_ADDR orig_pc = pc;
  CORE_ADDR last_prologue_pc = pc;
  CORE_ADDR li_found_pc = 0;
  char buf[4];
  unsigned long op;
  long offset = 0;
  long vr_saved_offset = 0;
  int lr_reg = -1;
  int cr_reg = -1;
  int vr_reg = -1;
  int ev_reg = -1;
  long ev_offset = 0;
  int vrsave_reg = -1;
  int reg;
  int framep = 0;
  int minimal_toc_loaded = 0;
  int prev_insn_was_prologue_insn = 1;
  int num_skip_non_prologue_insns = 0;
  const struct bfd_arch_info *arch_info = gdbarch_bfd_arch_info (current_gdbarch);
  struct gdbarch_tdep *tdep = gdbarch_tdep (current_gdbarch);
  
  /* Attempt to find the end of the prologue when no limit is specified.
     Note that refine_prologue_limit() has been written so that it may
     be used to "refine" the limits of non-zero PC values too, but this
     is only safe if we 1) trust the line information provided by the
     compiler and 2) iterate enough to actually find the end of the
     prologue.  
     
     It may become a good idea at some point (for both performance and
     accuracy) to unconditionally call refine_prologue_limit().  But,
     until we can make a clear determination that this is beneficial,
     we'll play it safe and only use it to obtain a limit when none
     has been specified.  */
  if (lim_pc == 0)
    lim_pc = refine_prologue_limit (pc, lim_pc);

  memset (fdata, 0, sizeof (struct rs6000_framedata));
  fdata->saved_gpr = -1;
  fdata->saved_fpr = -1;
  fdata->saved_vr = -1;
  fdata->saved_ev = -1;
  fdata->alloca_reg = -1;
  fdata->frameless = 1;
  fdata->nosavedpc = 1;

  for (;; pc += 4)
    {
      /* Sometimes it isn't clear if an instruction is a prologue
         instruction or not.  When we encounter one of these ambiguous
	 cases, we'll set prev_insn_was_prologue_insn to 0 (false).
	 Otherwise, we'll assume that it really is a prologue instruction. */
      if (prev_insn_was_prologue_insn)
	last_prologue_pc = pc;

      /* Stop scanning if we've hit the limit.  */
      if (lim_pc != 0 && pc >= lim_pc)
	break;

      prev_insn_was_prologue_insn = 1;

      /* Fetch the instruction and convert it to an integer.  */
      if (target_read_memory (pc, buf, 4))
	break;
      op = extract_signed_integer (buf, 4);

      if ((op & 0xfc1fffff) == 0x7c0802a6)
	{			/* mflr Rx */
	  lr_reg = (op & 0x03e00000);
	  continue;

	}
      else if ((op & 0xfc1fffff) == 0x7c000026)
	{			/* mfcr Rx */
	  cr_reg = (op & 0x03e00000);
	  continue;

	}
      else if ((op & 0xfc1f0000) == 0xd8010000)
	{			/* stfd Rx,NUM(r1) */
	  reg = GET_SRC_REG (op);
	  if (fdata->saved_fpr == -1 || fdata->saved_fpr > reg)
	    {
	      fdata->saved_fpr = reg;
	      fdata->fpr_offset = SIGNED_SHORT (op) + offset;
	    }
	  continue;

	}
      else if (((op & 0xfc1f0000) == 0xbc010000) ||	/* stm Rx, NUM(r1) */
	       (((op & 0xfc1f0000) == 0x90010000 ||	/* st rx,NUM(r1) */
		 (op & 0xfc1f0003) == 0xf8010000) &&	/* std rx,NUM(r1) */
		(op & 0x03e00000) >= 0x01a00000))	/* rx >= r13 */
	{

	  reg = GET_SRC_REG (op);
	  if (fdata->saved_gpr == -1 || fdata->saved_gpr > reg)
	    {
	      fdata->saved_gpr = reg;
	      if ((op & 0xfc1f0003) == 0xf8010000)
		op &= ~3UL;
	      fdata->gpr_offset = SIGNED_SHORT (op) + offset;
	    }
	  continue;

	}
      else if ((op & 0xffff0000) == 0x60000000)
        {
	  /* nop */
	  /* Allow nops in the prologue, but do not consider them to
	     be part of the prologue unless followed by other prologue
	     instructions. */
	  prev_insn_was_prologue_insn = 0;
	  continue;

	}
      else if ((op & 0xffff0000) == 0x3c000000)
	{			/* addis 0,0,NUM, used
				   for >= 32k frames */
	  fdata->offset = (op & 0x0000ffff) << 16;
	  fdata->frameless = 0;
	  continue;

	}
      else if ((op & 0xffff0000) == 0x60000000)
	{			/* ori 0,0,NUM, 2nd ha
				   lf of >= 32k frames */
	  fdata->offset |= (op & 0x0000ffff);
	  fdata->frameless = 0;
	  continue;

	}
      else if (lr_reg != -1 &&
	       /* std Rx, NUM(r1) || stdu Rx, NUM(r1) */
	       (((op & 0xffff0000) == (lr_reg | 0xf8010000)) ||
		/* stw Rx, NUM(r1) */
		((op & 0xffff0000) == (lr_reg | 0x90010000)) ||
		/* stwu Rx, NUM(r1) */
		((op & 0xffff0000) == (lr_reg | 0x94010000))))
	{	/* where Rx == lr */
	  fdata->lr_offset = offset;
	  fdata->nosavedpc = 0;
	  lr_reg = 0;
	  if ((op & 0xfc000003) == 0xf8000000 ||	/* std */
	      (op & 0xfc000000) == 0x90000000)		/* stw */
	    {
	      /* Does not update r1, so add displacement to lr_offset.  */
	      fdata->lr_offset += SIGNED_SHORT (op);
	    }
	  continue;

	}
      else if (cr_reg != -1 &&
	       /* std Rx, NUM(r1) || stdu Rx, NUM(r1) */
	       (((op & 0xffff0000) == (cr_reg | 0xf8010000)) ||
		/* stw Rx, NUM(r1) */
		((op & 0xffff0000) == (cr_reg | 0x90010000)) ||
		/* stwu Rx, NUM(r1) */
		((op & 0xffff0000) == (cr_reg | 0x94010000))))
	{	/* where Rx == cr */
	  fdata->cr_offset = offset;
	  cr_reg = 0;
	  if ((op & 0xfc000003) == 0xf8000000 ||
	      (op & 0xfc000000) == 0x90000000)
	    {
	      /* Does not update r1, so add displacement to cr_offset.  */
	      fdata->cr_offset += SIGNED_SHORT (op);
	    }
	  continue;

	}
      else if (op == 0x48000005)
	{			/* bl .+4 used in 
				   -mrelocatable */
	  continue;

	}
      else if (op == 0x48000004)
	{			/* b .+4 (xlc) */
	  break;

	}
      else if ((op & 0xffff0000) == 0x3fc00000 ||  /* addis 30,0,foo@ha, used
						      in V.4 -mminimal-toc */
	       (op & 0xffff0000) == 0x3bde0000)
	{			/* addi 30,30,foo@l */
	  continue;

	}
      else if ((op & 0xfc000001) == 0x48000001)
	{			/* bl foo, 
				   to save fprs??? */

	  fdata->frameless = 0;
	  /* Don't skip over the subroutine call if it is not within
	     the first three instructions of the prologue.  */
	  if ((pc - orig_pc) > 8)
	    break;

	  op = read_memory_integer (pc + 4, 4);

	  /* At this point, make sure this is not a trampoline
	     function (a function that simply calls another functions,
	     and nothing else).  If the next is not a nop, this branch
	     was part of the function prologue. */

	  if (op == 0x4def7b82 || op == 0)	/* crorc 15, 15, 15 */
	    break;		/* don't skip over 
				   this branch */
	  continue;

	}
      /* update stack pointer */
      else if ((op & 0xfc1f0000) == 0x94010000)
	{		/* stu rX,NUM(r1) ||  stwu rX,NUM(r1) */
	  fdata->frameless = 0;
	  fdata->offset = SIGNED_SHORT (op);
	  offset = fdata->offset;
	  continue;
	}
      else if ((op & 0xfc1f016a) == 0x7c01016e)
	{			/* stwux rX,r1,rY */
	  /* no way to figure out what r1 is going to be */
	  fdata->frameless = 0;
	  offset = fdata->offset;
	  continue;
	}
      else if ((op & 0xfc1f0003) == 0xf8010001)
	{			/* stdu rX,NUM(r1) */
	  fdata->frameless = 0;
	  fdata->offset = SIGNED_SHORT (op & ~3UL);
	  offset = fdata->offset;
	  continue;
	}
      else if ((op & 0xfc1f016a) == 0x7c01016a)
	{			/* stdux rX,r1,rY */
	  /* no way to figure out what r1 is going to be */
	  fdata->frameless = 0;
	  offset = fdata->offset;
	  continue;
	}
      /* Load up minimal toc pointer */
      else if (((op >> 22) == 0x20f	||	/* l r31,... or l r30,... */
	       (op >> 22) == 0x3af)		/* ld r31,... or ld r30,... */
	       && !minimal_toc_loaded)
	{
	  minimal_toc_loaded = 1;
	  continue;

	  /* move parameters from argument registers to local variable
             registers */
 	}
      else if ((op & 0xfc0007fe) == 0x7c000378 &&	/* mr(.)  Rx,Ry */
               (((op >> 21) & 31) >= 3) &&              /* R3 >= Ry >= R10 */
               (((op >> 21) & 31) <= 10) &&
               ((long) ((op >> 16) & 31) >= fdata->saved_gpr)) /* Rx: local var reg */
	{
	  continue;

	  /* store parameters in stack */
	}
      else if ((op & 0xfc1f0003) == 0xf8010000 ||	/* std rx,NUM(r1) */
	       (op & 0xfc1f0000) == 0xd8010000 ||	/* stfd Rx,NUM(r1) */
	       (op & 0xfc1f0000) == 0xfc010000)		/* frsp, fp?,NUM(r1) */
	{
	  continue;

	  /* store parameters in stack via frame pointer */
	}
      else if (framep &&
	       ((op & 0xfc1f0000) == 0x901f0000 ||	/* st rx,NUM(r1) */
		(op & 0xfc1f0000) == 0xd81f0000 ||	/* stfd Rx,NUM(r1) */
		(op & 0xfc1f0000) == 0xfc1f0000))
	{			/* frsp, fp?,NUM(r1) */
	  continue;

	  /* Set up frame pointer */
	}
      else if (op == 0x603f0000	/* oril r31, r1, 0x0 */
	       || op == 0x7c3f0b78)
	{			/* mr r31, r1 */
	  fdata->frameless = 0;
	  framep = 1;
	  fdata->alloca_reg = (tdep->ppc_gp0_regnum + 31);
	  continue;

	  /* Another way to set up the frame pointer.  */
	}
      else if ((op & 0xfc1fffff) == 0x38010000)
	{			/* addi rX, r1, 0x0 */
	  fdata->frameless = 0;
	  framep = 1;
	  fdata->alloca_reg = (tdep->ppc_gp0_regnum
			       + ((op & ~0x38010000) >> 21));
	  continue;
	}
      /* AltiVec related instructions.  */
      /* Store the vrsave register (spr 256) in another register for
	 later manipulation, or load a register into the vrsave
	 register.  2 instructions are used: mfvrsave and
	 mtvrsave.  They are shorthand notation for mfspr Rn, SPR256
	 and mtspr SPR256, Rn.  */
      /* mfspr Rn SPR256 == 011111 nnnnn 0000001000 01010100110
	 mtspr SPR256 Rn == 011111 nnnnn 0000001000 01110100110  */
      else if ((op & 0xfc1fffff) == 0x7c0042a6)    /* mfvrsave Rn */
	{
          vrsave_reg = GET_SRC_REG (op);
	  continue;
	}
      else if ((op & 0xfc1fffff) == 0x7c0043a6)     /* mtvrsave Rn */
        {
          continue;
        }
      /* Store the register where vrsave was saved to onto the stack:
         rS is the register where vrsave was stored in a previous
	 instruction.  */
      /* 100100 sssss 00001 dddddddd dddddddd */
      else if ((op & 0xfc1f0000) == 0x90010000)     /* stw rS, d(r1) */
        {
          if (vrsave_reg == GET_SRC_REG (op))
	    {
	      fdata->vrsave_offset = SIGNED_SHORT (op) + offset;
	      vrsave_reg = -1;
	    }
          continue;
        }
      /* Compute the new value of vrsave, by modifying the register
         where vrsave was saved to.  */
      else if (((op & 0xfc000000) == 0x64000000)    /* oris Ra, Rs, UIMM */
	       || ((op & 0xfc000000) == 0x60000000))/* ori Ra, Rs, UIMM */
	{
	  continue;
	}
      /* li r0, SIMM (short for addi r0, 0, SIMM).  This is the first
	 in a pair of insns to save the vector registers on the
	 stack.  */
      /* 001110 00000 00000 iiii iiii iiii iiii  */
      /* 001110 01110 00000 iiii iiii iiii iiii  */
      else if ((op & 0xffff0000) == 0x38000000         /* li r0, SIMM */
               || (op & 0xffff0000) == 0x39c00000)     /* li r14, SIMM */
	{
	  li_found_pc = pc;
	  vr_saved_offset = SIGNED_SHORT (op);
	}
      /* Store vector register S at (r31+r0) aligned to 16 bytes.  */      
      /* 011111 sssss 11111 00000 00111001110 */
      else if ((op & 0xfc1fffff) == 0x7c1f01ce)   /* stvx Vs, R31, R0 */
        {
	  if (pc == (li_found_pc + 4))
	    {
	      vr_reg = GET_SRC_REG (op);
	      /* If this is the first vector reg to be saved, or if
		 it has a lower number than others previously seen,
		 reupdate the frame info.  */
	      if (fdata->saved_vr == -1 || fdata->saved_vr > vr_reg)
		{
		  fdata->saved_vr = vr_reg;
		  fdata->vr_offset = vr_saved_offset + offset;
		}
	      vr_saved_offset = -1;
	      vr_reg = -1;
	      li_found_pc = 0;
	    }
	}
      /* End AltiVec related instructions.  */

      /* Start BookE related instructions.  */
      /* Store gen register S at (r31+uimm).
         Any register less than r13 is volatile, so we don't care.  */
      /* 000100 sssss 11111 iiiii 01100100001 */
      else if (arch_info->mach == bfd_mach_ppc_e500
	       && (op & 0xfc1f07ff) == 0x101f0321)    /* evstdd Rs,uimm(R31) */
	{
          if ((op & 0x03e00000) >= 0x01a00000)	/* Rs >= r13 */
	    {
              unsigned int imm;
	      ev_reg = GET_SRC_REG (op);
              imm = (op >> 11) & 0x1f;
	      ev_offset = imm * 8;
	      /* If this is the first vector reg to be saved, or if
		 it has a lower number than others previously seen,
		 reupdate the frame info.  */
	      if (fdata->saved_ev == -1 || fdata->saved_ev > ev_reg)
		{
		  fdata->saved_ev = ev_reg;
		  fdata->ev_offset = ev_offset + offset;
		}
	    }
          continue;
        }
      /* Store gen register rS at (r1+rB).  */
      /* 000100 sssss 00001 bbbbb 01100100000 */
      else if (arch_info->mach == bfd_mach_ppc_e500
	       && (op & 0xffe007ff) == 0x13e00320)     /* evstddx RS,R1,Rb */
	{
          if (pc == (li_found_pc + 4))
            {
              ev_reg = GET_SRC_REG (op);
	      /* If this is the first vector reg to be saved, or if
                 it has a lower number than others previously seen,
                 reupdate the frame info.  */
              /* We know the contents of rB from the previous instruction.  */
	      if (fdata->saved_ev == -1 || fdata->saved_ev > ev_reg)
		{
                  fdata->saved_ev = ev_reg;
                  fdata->ev_offset = vr_saved_offset + offset;
		}
	      vr_saved_offset = -1;
	      ev_reg = -1;
	      li_found_pc = 0;
            }
          continue;
        }
      /* Store gen register r31 at (rA+uimm).  */
      /* 000100 11111 aaaaa iiiii 01100100001 */
      else if (arch_info->mach == bfd_mach_ppc_e500
	       && (op & 0xffe007ff) == 0x13e00321)   /* evstdd R31,Ra,UIMM */
        {
          /* Wwe know that the source register is 31 already, but
             it can't hurt to compute it.  */
	  ev_reg = GET_SRC_REG (op);
          ev_offset = ((op >> 11) & 0x1f) * 8;
	  /* If this is the first vector reg to be saved, or if
	     it has a lower number than others previously seen,
	     reupdate the frame info.  */
	  if (fdata->saved_ev == -1 || fdata->saved_ev > ev_reg)
	    {
	      fdata->saved_ev = ev_reg;
	      fdata->ev_offset = ev_offset + offset;
	    }

	  continue;
      	}
      /* Store gen register S at (r31+r0).
         Store param on stack when offset from SP bigger than 4 bytes.  */
      /* 000100 sssss 11111 00000 01100100000 */
      else if (arch_info->mach == bfd_mach_ppc_e500
	       && (op & 0xfc1fffff) == 0x101f0320)     /* evstddx Rs,R31,R0 */
	{
          if (pc == (li_found_pc + 4))
            {
              if ((op & 0x03e00000) >= 0x01a00000)
		{
		  ev_reg = GET_SRC_REG (op);
		  /* If this is the first vector reg to be saved, or if
		     it has a lower number than others previously seen,
		     reupdate the frame info.  */
                  /* We know the contents of r0 from the previous
                     instruction.  */
		  if (fdata->saved_ev == -1 || fdata->saved_ev > ev_reg)
		    {
		      fdata->saved_ev = ev_reg;
		      fdata->ev_offset = vr_saved_offset + offset;
		    }
		  ev_reg = -1;
		}
	      vr_saved_offset = -1;
	      li_found_pc = 0;
	      continue;
            }
	}
      /* End BookE related instructions.  */

      else
	{
	  /* Not a recognized prologue instruction.
	     Handle optimizer code motions into the prologue by continuing
	     the search if we have no valid frame yet or if the return
	     address is not yet saved in the frame.  */
	  if (fdata->frameless == 0
	      && (lr_reg == -1 || fdata->nosavedpc == 0))
	    break;

	  if (op == 0x4e800020		/* blr */
	      || op == 0x4e800420)	/* bctr */
	    /* Do not scan past epilogue in frameless functions or
	       trampolines.  */
	    break;
	  if ((op & 0xf4000000) == 0x40000000) /* bxx */
	    /* Never skip branches.  */
	    break;

	  if (num_skip_non_prologue_insns++ > max_skip_non_prologue_insns)
	    /* Do not scan too many insns, scanning insns is expensive with
	       remote targets.  */
	    break;

	  /* Continue scanning.  */
	  prev_insn_was_prologue_insn = 0;
	  continue;
	}
    }

#if 0
/* I have problems with skipping over __main() that I need to address
 * sometime. Previously, I used to use misc_function_vector which
 * didn't work as well as I wanted to be.  -MGO */

  /* If the first thing after skipping a prolog is a branch to a function,
     this might be a call to an initializer in main(), introduced by gcc2.
     We'd like to skip over it as well.  Fortunately, xlc does some extra
     work before calling a function right after a prologue, thus we can
     single out such gcc2 behaviour.  */


  if ((op & 0xfc000001) == 0x48000001)
    {				/* bl foo, an initializer function? */
      op = read_memory_integer (pc + 4, 4);

      if (op == 0x4def7b82)
	{			/* cror 0xf, 0xf, 0xf (nop) */

	  /* Check and see if we are in main.  If so, skip over this
	     initializer function as well.  */

	  tmp = find_pc_misc_function (pc);
	  if (tmp >= 0
	      && strcmp (misc_function_vector[tmp].name, main_name ()) == 0)
	    return pc + 8;
	}
    }
#endif /* 0 */

  fdata->offset = -fdata->offset;
  return last_prologue_pc;
}