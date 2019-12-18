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
 int SPARC64_F32_REGNUM ; 
 int SPARC64_F62_REGNUM ; 
 int SPARC64_FSR_REGNUM ; 
 int SPARC_F0_REGNUM ; 
 int SPARC_F31_REGNUM ; 
 int /*<<< orphan*/  current_gdbarch ; 
 int gdbarch_ptr_bit (int /*<<< orphan*/ ) ; 
 int sparc32_fpregset_supplies_p (int) ; 

__attribute__((used)) static int
sparc64_fpregset_supplies_p (int regnum)
{
  if (gdbarch_ptr_bit (current_gdbarch) == 32)
    return sparc32_fpregset_supplies_p (regnum);

  /* Floating-point registers.  */
  if ((regnum >= SPARC_F0_REGNUM && regnum <= SPARC_F31_REGNUM)
      || (regnum >= SPARC64_F32_REGNUM && regnum <= SPARC64_F62_REGNUM))
    return 1;

  /* Control registers.  */
  if (regnum == SPARC64_FSR_REGNUM)
    return 1;

  return 0;
}