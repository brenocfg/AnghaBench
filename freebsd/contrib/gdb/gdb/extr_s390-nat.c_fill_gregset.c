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
typedef  int /*<<< orphan*/  gregset_t ;

/* Variables and functions */
 int S390_NUM_REGS ; 
 int SUBOFF (int) ; 
 int /*<<< orphan*/  current_regcache ; 
 int /*<<< orphan*/  regcache_raw_collect (int /*<<< orphan*/ ,int,char*) ; 
 int* regmap_gregset ; 

void
fill_gregset (gregset_t *regp, int regno)
{
  int i;
  for (i = 0; i < S390_NUM_REGS; i++)
    if (regmap_gregset[i] != -1)
      if (regno == -1 || regno == i)
	regcache_raw_collect (current_regcache, i, 
			      (char *)regp + regmap_gregset[i] + SUBOFF (i));
}