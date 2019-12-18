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
 int SPARC32_FSR_REGNUM ; 
 int SPARC_F0_REGNUM ; 
 int /*<<< orphan*/  regcache_raw_supply (struct regcache*,int,char const*) ; 

void
sparc32_supply_fpregset (struct regcache *regcache,
			 int regnum, const void *fpregs)
{
  const char *regs = fpregs;
  int i;

  for (i = 0; i < 32; i++)
    {
      if (regnum == (SPARC_F0_REGNUM + i) || regnum == -1)
	regcache_raw_supply (regcache, SPARC_F0_REGNUM + i, regs + (i * 4));
    }

  if (regnum == SPARC32_FSR_REGNUM || regnum == -1)
    regcache_raw_supply (regcache, SPARC32_FSR_REGNUM, regs + (32 * 4) + 4);
}