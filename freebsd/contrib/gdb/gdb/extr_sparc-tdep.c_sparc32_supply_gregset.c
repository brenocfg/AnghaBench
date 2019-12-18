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
struct sparc_gregset {int r_psr_offset; int r_pc_offset; int r_npc_offset; int r_y_offset; int r_g1_offset; int r_l0_offset; } ;
struct regcache {int dummy; } ;
typedef  int /*<<< orphan*/  ULONGEST ;

/* Variables and functions */
 int SPARC32_NPC_REGNUM ; 
 int SPARC32_PC_REGNUM ; 
 int SPARC32_PSR_REGNUM ; 
 int SPARC32_Y_REGNUM ; 
 int SPARC_G0_REGNUM ; 
 int SPARC_G1_REGNUM ; 
 int SPARC_I7_REGNUM ; 
 int SPARC_L0_REGNUM ; 
 int SPARC_O7_REGNUM ; 
 int /*<<< orphan*/  SPARC_SP_REGNUM ; 
 int /*<<< orphan*/  regcache_cooked_read_unsigned (struct regcache*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regcache_raw_supply (struct regcache*,int,char const*) ; 
 int /*<<< orphan*/  sparc_supply_rwindow (struct regcache*,int /*<<< orphan*/ ,int) ; 

void
sparc32_supply_gregset (const struct sparc_gregset *gregset,
			struct regcache *regcache,
			int regnum, const void *gregs)
{
  const char *regs = gregs;
  int i;

  if (regnum == SPARC32_PSR_REGNUM || regnum == -1)
    regcache_raw_supply (regcache, SPARC32_PSR_REGNUM,
			 regs + gregset->r_psr_offset);

  if (regnum == SPARC32_PC_REGNUM || regnum == -1)
    regcache_raw_supply (regcache, SPARC32_PC_REGNUM,
			 regs + gregset->r_pc_offset);

  if (regnum == SPARC32_NPC_REGNUM || regnum == -1)
    regcache_raw_supply (regcache, SPARC32_NPC_REGNUM,
			 regs + gregset->r_npc_offset);

  if (regnum == SPARC32_Y_REGNUM || regnum == -1)
    regcache_raw_supply (regcache, SPARC32_Y_REGNUM,
			 regs + gregset->r_y_offset);

  if (regnum == SPARC_G0_REGNUM || regnum == -1)
    regcache_raw_supply (regcache, SPARC_G0_REGNUM, NULL);

  if ((regnum >= SPARC_G1_REGNUM && regnum <= SPARC_O7_REGNUM) || regnum == -1)
    {
      int offset = gregset->r_g1_offset;

      for (i = SPARC_G1_REGNUM; i <= SPARC_O7_REGNUM; i++)
	{
	  if (regnum == i || regnum == -1)
	    regcache_raw_supply (regcache, i, regs + offset);
	  offset += 4;
	}
    }

  if ((regnum >= SPARC_L0_REGNUM && regnum <= SPARC_I7_REGNUM) || regnum == -1)
    {
      /* Not all of the register set variants include Locals and
         Inputs.  For those that don't, we read them off the stack.  */
      if (gregset->r_l0_offset == -1)
	{
	  ULONGEST sp;

	  regcache_cooked_read_unsigned (regcache, SPARC_SP_REGNUM, &sp);
	  sparc_supply_rwindow (regcache, sp, regnum);
	}
      else
	{
	  int offset = gregset->r_l0_offset;

	  for (i = SPARC_L0_REGNUM; i <= SPARC_I7_REGNUM; i++)
	    {
	      if (regnum == i || regnum == -1)
		regcache_raw_supply (regcache, i, regs + offset);
	      offset += 4;
	    }
	}
    }
}