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
struct reggroup {int dummy; } ;
struct gdbarch_tdep {int dummy; } ;
struct gdbarch {int dummy; } ;

/* Variables and functions */
 int S390_CC_REGNUM ; 
 int S390_F0_REGNUM ; 
 int S390_F15_REGNUM ; 
 int S390_FPC_REGNUM ; 
 int S390_PC_REGNUM ; 
 int S390_PSWA_REGNUM ; 
 int S390_PSWM_REGNUM ; 
 int S390_R0_REGNUM ; 
 int S390_R15_REGNUM ; 
 int default_register_reggroup_p (struct gdbarch*,int,struct reggroup*) ; 
 struct reggroup* float_reggroup ; 
 struct gdbarch_tdep* gdbarch_tdep (struct gdbarch*) ; 
 struct reggroup* general_reggroup ; 
 struct reggroup* restore_reggroup ; 
 struct reggroup* save_reggroup ; 

__attribute__((used)) static int
s390_register_reggroup_p (struct gdbarch *gdbarch, int regnum,
			  struct reggroup *group)
{
  struct gdbarch_tdep *tdep = gdbarch_tdep (gdbarch);

  /* Registers displayed via 'info regs'.  */
  if (group == general_reggroup)
    return (regnum >= S390_R0_REGNUM && regnum <= S390_R15_REGNUM)
	   || regnum == S390_PC_REGNUM
	   || regnum == S390_CC_REGNUM;

  /* Registers displayed via 'info float'.  */
  if (group == float_reggroup)
    return (regnum >= S390_F0_REGNUM && regnum <= S390_F15_REGNUM)
	   || regnum == S390_FPC_REGNUM;

  /* Registers that need to be saved/restored in order to
     push or pop frames.  */
  if (group == save_reggroup || group == restore_reggroup)
    return regnum != S390_PSWM_REGNUM && regnum != S390_PSWA_REGNUM;

  return default_register_reggroup_p (gdbarch, regnum, group);
}