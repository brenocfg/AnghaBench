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
struct gdbarch {int dummy; } ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 unsigned int S390_R0_REGNUM ; 
 unsigned int S390_SP_REGNUM ; 
 int gdbarch_ptr_bit (struct gdbarch*) ; 
 scalar_t__ is_rs (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int*,unsigned int*,int*,unsigned int*) ; 
 scalar_t__ is_rsy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*,unsigned int*,int*,unsigned int*) ; 
 int /*<<< orphan*/  op1_lmg ; 
 int /*<<< orphan*/  op1_lmy ; 
 int /*<<< orphan*/  op2_lmg ; 
 int /*<<< orphan*/  op2_lmy ; 
 int /*<<< orphan*/  op_lm ; 
 int /*<<< orphan*/  read_memory_nobpt (scalar_t__,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
s390_in_function_epilogue_p (struct gdbarch *gdbarch, CORE_ADDR pc)
{
  int word_size = gdbarch_ptr_bit (gdbarch) / 8;

  /* In frameless functions, there's not frame to destroy and thus
     we don't care about the epilogue.

     In functions with frame, the epilogue sequence is a pair of
     a LM-type instruction that restores (amongst others) the
     return register %r14 and the stack pointer %r15, followed
     by a branch 'br %r14' --or equivalent-- that effects the
     actual return.

     In that situation, this function needs to return 'true' in
     exactly one case: when pc points to that branch instruction.

     Thus we try to disassemble the one instructions immediately
     preceeding pc and check whether it is an LM-type instruction
     modifying the stack pointer.

     Note that disassembling backwards is not reliable, so there
     is a slight chance of false positives here ...  */

  bfd_byte insn[6];
  unsigned int r1, r3, b2;
  int d2;

  if (word_size == 4
      && !read_memory_nobpt (pc - 4, insn, 4)
      && is_rs (insn, op_lm, &r1, &r3, &d2, &b2)
      && r3 == S390_SP_REGNUM - S390_R0_REGNUM)
    return 1;

  if (word_size == 4
      && !read_memory_nobpt (pc - 6, insn, 6)
      && is_rsy (insn, op1_lmy, op2_lmy, &r1, &r3, &d2, &b2)
      && r3 == S390_SP_REGNUM - S390_R0_REGNUM)
    return 1;

  if (word_size == 8
      && !read_memory_nobpt (pc - 6, insn, 6)
      && is_rsy (insn, op1_lmg, op2_lmg, &r1, &r3, &d2, &b2)
      && r3 == S390_SP_REGNUM - S390_R0_REGNUM)
    return 1;

  return 0;
}