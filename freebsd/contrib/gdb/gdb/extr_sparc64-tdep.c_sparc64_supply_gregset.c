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
struct sparc_gregset {int r_tstate_offset; int r_pc_offset; int r_npc_offset; int r_y_offset; int r_y_size; int r_fprs_offset; int r_g1_offset; int r_l0_offset; } ;
struct regcache {int dummy; } ;
typedef  int ULONGEST ;

/* Variables and functions */
 int PSR_S ; 
 int PSR_V8PLUS ; 
 int SPARC32_NPC_REGNUM ; 
 int SPARC32_PC_REGNUM ; 
 int SPARC32_PSR_REGNUM ; 
 int SPARC32_Y_REGNUM ; 
 int SPARC64_FPRS_REGNUM ; 
 int SPARC64_NPC_REGNUM ; 
 int SPARC64_PC_REGNUM ; 
 int SPARC64_STATE_REGNUM ; 
 int SPARC64_Y_REGNUM ; 
 int SPARC_G0_REGNUM ; 
 int SPARC_G1_REGNUM ; 
 int SPARC_I7_REGNUM ; 
 int SPARC_L0_REGNUM ; 
 int SPARC_O7_REGNUM ; 
 int /*<<< orphan*/  SPARC_SP_REGNUM ; 
 int TSTATE_CWP ; 
 int TSTATE_ICC ; 
 int TSTATE_XCC ; 
 int /*<<< orphan*/  current_gdbarch ; 
 int extract_unsigned_integer (char const*,int) ; 
 int gdbarch_ptr_bit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regcache_cooked_read_unsigned (struct regcache*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regcache_raw_supply (struct regcache*,int,char const*) ; 
 int /*<<< orphan*/  sparc_supply_rwindow (struct regcache*,int,int) ; 
 int /*<<< orphan*/  store_unsigned_integer (char*,int,int) ; 

void
sparc64_supply_gregset (const struct sparc_gregset *gregset,
			struct regcache *regcache,
			int regnum, const void *gregs)
{
  int sparc32 = (gdbarch_ptr_bit (current_gdbarch) == 32);
  const char *regs = gregs;
  int i;

  if (sparc32)
    {
      if (regnum == SPARC32_PSR_REGNUM || regnum == -1)
	{
	  int offset = gregset->r_tstate_offset;
	  ULONGEST tstate, psr;
	  char buf[4];

	  tstate = extract_unsigned_integer (regs + offset, 8);
	  psr = ((tstate & TSTATE_CWP) | PSR_S | ((tstate & TSTATE_ICC) >> 12)
		 | ((tstate & TSTATE_XCC) >> 20) | PSR_V8PLUS);
	  store_unsigned_integer (buf, 4, psr);
	  regcache_raw_supply (regcache, SPARC32_PSR_REGNUM, buf);
	}

      if (regnum == SPARC32_PC_REGNUM || regnum == -1)
	regcache_raw_supply (regcache, SPARC32_PC_REGNUM,
			     regs + gregset->r_pc_offset + 4);

      if (regnum == SPARC32_NPC_REGNUM || regnum == -1)
	regcache_raw_supply (regcache, SPARC32_NPC_REGNUM,
			     regs + gregset->r_npc_offset + 4);

      if (regnum == SPARC32_Y_REGNUM || regnum == -1)
	{
	  int offset = gregset->r_y_offset + 8 - gregset->r_y_size;
	  regcache_raw_supply (regcache, SPARC32_Y_REGNUM, regs + offset);
	}
    }
  else
    {
      if (regnum == SPARC64_STATE_REGNUM || regnum == -1)
	regcache_raw_supply (regcache, SPARC64_STATE_REGNUM,
			     regs + gregset->r_tstate_offset);

      if (regnum == SPARC64_PC_REGNUM || regnum == -1)
	regcache_raw_supply (regcache, SPARC64_PC_REGNUM,
			     regs + gregset->r_pc_offset);

      if (regnum == SPARC64_NPC_REGNUM || regnum == -1)
	regcache_raw_supply (regcache, SPARC64_NPC_REGNUM,
			     regs + gregset->r_npc_offset);

      if (regnum == SPARC64_Y_REGNUM || regnum == -1)
	{
	  char buf[8];

	  memset (buf, 0, 8);
	  memcpy (buf + 8 - gregset->r_y_size,
		  regs + gregset->r_y_offset, gregset->r_y_size);
	  regcache_raw_supply (regcache, SPARC64_Y_REGNUM, buf);
	}

      if ((regnum == SPARC64_FPRS_REGNUM || regnum == -1)
	  && gregset->r_fprs_offset != -1)
	regcache_raw_supply (regcache, SPARC64_FPRS_REGNUM,
			     regs + gregset->r_fprs_offset);
    }

  if (regnum == SPARC_G0_REGNUM || regnum == -1)
    regcache_raw_supply (regcache, SPARC_G0_REGNUM, NULL);

  if ((regnum >= SPARC_G1_REGNUM && regnum <= SPARC_O7_REGNUM) || regnum == -1)
    {
      int offset = gregset->r_g1_offset;

      if (sparc32)
	offset += 4;

      for (i = SPARC_G1_REGNUM; i <= SPARC_O7_REGNUM; i++)
	{
	  if (regnum == i || regnum == -1)
	    regcache_raw_supply (regcache, i, regs + offset);
	  offset += 8;
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

	  if (sparc32)
	    offset += 4;

	  for (i = SPARC_L0_REGNUM; i <= SPARC_I7_REGNUM; i++)
	    {
	      if (regnum == i || regnum == -1)
		regcache_raw_supply (regcache, i, regs + offset);
	      offset += 8;
	    }
	}
    }
}