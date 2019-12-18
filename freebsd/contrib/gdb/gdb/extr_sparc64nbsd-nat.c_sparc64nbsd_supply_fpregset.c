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
struct regcache {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  current_gdbarch ; 
 int gdbarch_ptr_bit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sparc32_supply_fpregset (struct regcache*,int,void const*) ; 
 int /*<<< orphan*/  sparc64_supply_fpregset (struct regcache*,int,void const*) ; 

__attribute__((used)) static void
sparc64nbsd_supply_fpregset (struct regcache *regcache,
			     int regnum, const void *fpregs)
{
  int sparc32 = (gdbarch_ptr_bit (current_gdbarch) == 32);

  if (sparc32)
    sparc32_supply_fpregset (regcache, regnum, fpregs);
  else
    sparc64_supply_fpregset (regcache, regnum, fpregs);
}