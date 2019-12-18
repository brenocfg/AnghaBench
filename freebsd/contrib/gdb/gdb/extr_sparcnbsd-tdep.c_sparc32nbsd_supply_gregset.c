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
struct regset {int /*<<< orphan*/  descr; } ;
struct regcache {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sparc32_supply_fpregset (struct regcache*,int,char const*) ; 
 int /*<<< orphan*/  sparc32_supply_gregset (int /*<<< orphan*/ ,struct regcache*,int,void const*) ; 

__attribute__((used)) static void
sparc32nbsd_supply_gregset (const struct regset *regset,
			    struct regcache *regcache,
			    int regnum, const void *gregs, size_t len)
{
  sparc32_supply_gregset (regset->descr, regcache, regnum, gregs);

  /* Traditional NetBSD core files don't use multiple register sets.
     Instead, the general-purpose and floating-point registers are
     lumped together in a single section.  */
  if (len >= 212)
    sparc32_supply_fpregset (regcache, regnum, (const char *) gregs + 80);
}