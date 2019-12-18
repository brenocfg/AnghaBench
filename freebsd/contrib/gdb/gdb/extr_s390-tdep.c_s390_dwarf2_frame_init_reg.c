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
struct gdbarch_tdep {int abi; } ;
struct gdbarch {int dummy; } ;
struct dwarf2_frame_state_reg {void* how; } ;

/* Variables and functions */
#define  ABI_LINUX_S390 129 
#define  ABI_LINUX_ZSERIES 128 
 void* DWARF2_FRAME_REG_RA ; 
 void* DWARF2_FRAME_REG_SAME_VALUE ; 
 void* DWARF2_FRAME_REG_UNDEFINED ; 
 int S390_F0_REGNUM ; 
 int S390_F15_REGNUM ; 
 int S390_F4_REGNUM ; 
 int S390_F6_REGNUM ; 
 int S390_F7_REGNUM ; 
 int S390_F8_REGNUM ; 
 int S390_PC_REGNUM ; 
 int S390_R0_REGNUM ; 
 int S390_R15_REGNUM ; 
 int S390_R5_REGNUM ; 
 int S390_R6_REGNUM ; 
 struct gdbarch_tdep* gdbarch_tdep (struct gdbarch*) ; 

__attribute__((used)) static void
s390_dwarf2_frame_init_reg (struct gdbarch *gdbarch, int regnum,
                            struct dwarf2_frame_state_reg *reg)
{
  struct gdbarch_tdep *tdep = gdbarch_tdep (gdbarch);

  switch (tdep->abi)
    {
    case ABI_LINUX_S390:
      /* Call-saved registers.  */
      if ((regnum >= S390_R6_REGNUM && regnum <= S390_R15_REGNUM)
	  || regnum == S390_F4_REGNUM
	  || regnum == S390_F6_REGNUM)
	reg->how = DWARF2_FRAME_REG_SAME_VALUE;

      /* Call-clobbered registers.  */
      else if ((regnum >= S390_R0_REGNUM && regnum <= S390_R5_REGNUM)
	       || (regnum >= S390_F0_REGNUM && regnum <= S390_F15_REGNUM
		   && regnum != S390_F4_REGNUM && regnum != S390_F6_REGNUM))
	reg->how = DWARF2_FRAME_REG_UNDEFINED;

      /* The return address column.  */
      else if (regnum == S390_PC_REGNUM)
	reg->how = DWARF2_FRAME_REG_RA;
      break;

    case ABI_LINUX_ZSERIES:
      /* Call-saved registers.  */
      if ((regnum >= S390_R6_REGNUM && regnum <= S390_R15_REGNUM)
	  || (regnum >= S390_F8_REGNUM && regnum <= S390_F15_REGNUM))
	reg->how = DWARF2_FRAME_REG_SAME_VALUE;

      /* Call-clobbered registers.  */
      else if ((regnum >= S390_R0_REGNUM && regnum <= S390_R5_REGNUM)
	       || (regnum >= S390_F0_REGNUM && regnum <= S390_F7_REGNUM))
	reg->how = DWARF2_FRAME_REG_UNDEFINED;

      /* The return address column.  */
      else if (regnum == S390_PC_REGNUM)
	reg->how = DWARF2_FRAME_REG_RA;
      break;
    }
}