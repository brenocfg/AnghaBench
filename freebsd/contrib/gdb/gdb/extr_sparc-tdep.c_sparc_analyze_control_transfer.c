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
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ X_A (unsigned long) ; 
 int X_COND (unsigned long) ; 
 int X_DISP19 (unsigned long) ; 
 int X_DISP22 (unsigned long) ; 
 scalar_t__ X_OP (unsigned long) ; 
 int X_OP2 (unsigned long) ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 unsigned long sparc_fetch_instruction (scalar_t__) ; 

__attribute__((used)) static CORE_ADDR
sparc_analyze_control_transfer (CORE_ADDR pc, CORE_ADDR *npc)
{
  unsigned long insn = sparc_fetch_instruction (pc);
  int conditional_p = X_COND (insn) & 0x7;
  int branch_p = 0;
  long offset = 0;			/* Must be signed for sign-extend.  */

  if (X_OP (insn) == 0 && X_OP2 (insn) == 3 && (insn & 0x1000000) == 0)
    {
      /* Branch on Integer Register with Prediction (BPr).  */
      branch_p = 1;
      conditional_p = 1;
    }
  else if (X_OP (insn) == 0 && X_OP2 (insn) == 6)
    {
      /* Branch on Floating-Point Condition Codes (FBfcc).  */
      branch_p = 1;
      offset = 4 * X_DISP22 (insn);
    }
  else if (X_OP (insn) == 0 && X_OP2 (insn) == 5)
    {
      /* Branch on Floating-Point Condition Codes with Prediction
         (FBPfcc).  */
      branch_p = 1;
      offset = 4 * X_DISP19 (insn);
    }
  else if (X_OP (insn) == 0 && X_OP2 (insn) == 2)
    {
      /* Branch on Integer Condition Codes (Bicc).  */
      branch_p = 1;
      offset = 4 * X_DISP22 (insn);
    }
  else if (X_OP (insn) == 0 && X_OP2 (insn) == 1)
    {
      /* Branch on Integer Condition Codes with Prediction (BPcc).  */
      branch_p = 1;
      offset = 4 * X_DISP19 (insn);
    }

  /* FIXME: Handle DONE and RETRY instructions.  */

  /* FIXME: Handle the Trap instruction.  */

  if (branch_p)
    {
      if (conditional_p)
	{
	  /* For conditional branches, return nPC + 4 iff the annul
	     bit is 1.  */
	  return (X_A (insn) ? *npc + 4 : 0);
	}
      else
	{
	  /* For unconditional branches, return the target if its
	     specified condition is "always" and return nPC + 4 if the
	     condition is "never".  If the annul bit is 1, set *NPC to
	     zero.  */
	  if (X_COND (insn) == 0x0)
	    pc = *npc, offset = 4;
	  if (X_A (insn))
	    *npc = 0;

	  gdb_assert (offset != 0);
	  return pc + offset;
	}
    }

  return 0;
}