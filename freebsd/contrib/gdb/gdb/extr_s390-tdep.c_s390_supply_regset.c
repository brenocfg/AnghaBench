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
struct regset {int* descr; } ;
struct regcache {int dummy; } ;

/* Variables and functions */
 int S390_NUM_REGS ; 
 int /*<<< orphan*/  regcache_raw_supply (struct regcache*,int,char const*) ; 

__attribute__((used)) static void
s390_supply_regset (const struct regset *regset, struct regcache *regcache,
		    int regnum, const void *regs, size_t len)
{
  const int *offset = regset->descr;
  int i;

  for (i = 0; i < S390_NUM_REGS; i++)
    {
      if ((regnum == i || regnum == -1) && offset[i] != -1)
	regcache_raw_supply (regcache, i, (const char *)regs + offset[i]);
    }
}