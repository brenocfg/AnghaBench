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
 int /*<<< orphan*/  sparc32_collect_fpregset (struct regcache const*,int,void*) ; 
 int /*<<< orphan*/  sparc64_collect_fpregset (struct regcache const*,int,void*) ; 

__attribute__((used)) static void
sparc64nbsd_collect_fpregset (const struct regcache *regcache,
			      int regnum, void *fpregs)
{
  int sparc32 = (gdbarch_ptr_bit (current_gdbarch) == 32);

  if (sparc32)
    sparc32_collect_fpregset (regcache, regnum, fpregs);
  else
    sparc64_collect_fpregset (regcache, regnum, fpregs);
}