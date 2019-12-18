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
struct trad_frame_saved_reg {int realreg; void* addr; } ;
struct frame_info {int dummy; } ;
typedef  scalar_t__ ULONGEST ;
typedef  void* CORE_ADDR ;

/* Variables and functions */
 scalar_t__ PSR_EF ; 
 size_t SPARC32_FSR_REGNUM ; 
 size_t SPARC32_NPC_REGNUM ; 
 size_t SPARC32_PC_REGNUM ; 
 size_t SPARC32_PSR_REGNUM ; 
 size_t SPARC32_Y_REGNUM ; 
 int SPARC_F0_REGNUM ; 
 int SPARC_F31_REGNUM ; 
 size_t SPARC_FP_REGNUM ; 
 int SPARC_G0_REGNUM ; 
 size_t SPARC_G1_REGNUM ; 
 int SPARC_G2_REGNUM ; 
 int SPARC_G7_REGNUM ; 
 size_t SPARC_I0_REGNUM ; 
 int SPARC_I7_REGNUM ; 
 int SPARC_L0_REGNUM ; 
 int SPARC_L1_REGNUM ; 
 size_t SPARC_O0_REGNUM ; 
 int SPARC_O1_REGNUM ; 
 int SPARC_O5_REGNUM ; 
 size_t SPARC_O7_REGNUM ; 
 size_t SPARC_SP_REGNUM ; 
 void* frame_unwind_register_unsigned (struct frame_info*,size_t) ; 
 scalar_t__ get_frame_memory_unsigned (struct frame_info*,void*,int) ; 
 scalar_t__ sparc_fetch_wcookie () ; 
 struct trad_frame_saved_reg* trad_frame_alloc_saved_regs (struct frame_info*) ; 
 int /*<<< orphan*/  trad_frame_set_value (struct trad_frame_saved_reg*,int,scalar_t__) ; 

struct trad_frame_saved_reg *
sparc32nbsd_sigcontext_saved_regs (struct frame_info *next_frame)
{
  struct trad_frame_saved_reg *saved_regs;
  CORE_ADDR addr, sigcontext_addr;
  int regnum, delta;
  ULONGEST psr;

  saved_regs = trad_frame_alloc_saved_regs (next_frame);

  /* We find the appropriate instance of `struct sigcontext' at a
     fixed offset in the signal frame.  */
  addr = frame_unwind_register_unsigned (next_frame, SPARC_FP_REGNUM);
  sigcontext_addr = addr + 64 + 16;

  /* The registers are saved in bits and pieces scattered all over the
     place.  The code below records their location on the assumption
     that the part of the signal trampoline that saves the state has
     been executed.  */

  saved_regs[SPARC_SP_REGNUM].addr = sigcontext_addr + 8;
  saved_regs[SPARC32_PC_REGNUM].addr = sigcontext_addr + 12;
  saved_regs[SPARC32_NPC_REGNUM].addr = sigcontext_addr + 16;
  saved_regs[SPARC32_PSR_REGNUM].addr = sigcontext_addr + 20;
  saved_regs[SPARC_G1_REGNUM].addr = sigcontext_addr + 24;
  saved_regs[SPARC_O0_REGNUM].addr = sigcontext_addr + 28;

  /* The remaining `global' registers and %y are saved in the `local'
     registers.  */
  delta = SPARC_L0_REGNUM - SPARC_G0_REGNUM;
  for (regnum = SPARC_G2_REGNUM; regnum <= SPARC_G7_REGNUM; regnum++)
    saved_regs[regnum].realreg = regnum + delta;
  saved_regs[SPARC32_Y_REGNUM].realreg = SPARC_L1_REGNUM;

  /* The remaining `out' registers can be found in the current frame's
     `in' registers.  */
  delta = SPARC_I0_REGNUM - SPARC_O0_REGNUM;
  for (regnum = SPARC_O1_REGNUM; regnum <= SPARC_O5_REGNUM; regnum++)
    saved_regs[regnum].realreg = regnum + delta;
  saved_regs[SPARC_O7_REGNUM].realreg = SPARC_I7_REGNUM;

  /* The `local' and `in' registers have been saved in the register
     save area.  */
  addr = saved_regs[SPARC_SP_REGNUM].addr;
  addr = get_frame_memory_unsigned (next_frame, addr, 4);
  for (regnum = SPARC_L0_REGNUM;
       regnum <= SPARC_I7_REGNUM; regnum++, addr += 4)
    saved_regs[regnum].addr = addr;

  /* Handle StackGhost.  */
  {
    ULONGEST wcookie = sparc_fetch_wcookie ();

    if (wcookie != 0)
      {
	ULONGEST i7;

	addr = saved_regs[SPARC_I7_REGNUM].addr;
	i7 = get_frame_memory_unsigned (next_frame, addr, 4);
	trad_frame_set_value (saved_regs, SPARC_I7_REGNUM, i7 ^ wcookie);
      }
  }

  /* The floating-point registers are only saved if the EF bit in %prs
     has been set.  */

#define PSR_EF	0x00001000

  addr = saved_regs[SPARC32_PSR_REGNUM].addr;
  psr = get_frame_memory_unsigned (next_frame, addr, 4);
  if (psr & PSR_EF)
    {
      CORE_ADDR sp;

      sp = frame_unwind_register_unsigned (next_frame, SPARC_SP_REGNUM);
      saved_regs[SPARC32_FSR_REGNUM].addr = sp + 96;
      for (regnum = SPARC_F0_REGNUM, addr = sp + 96 + 8;
	   regnum <= SPARC_F31_REGNUM; regnum++, addr += 4)
	saved_regs[regnum].addr = addr;
    }

  return saved_regs;
}