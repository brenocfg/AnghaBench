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
typedef  int ULONGEST ;
typedef  int CORE_ADDR ;

/* Variables and functions */
 scalar_t__ BIAS ; 
 int SPARC_I7_REGNUM ; 
 int SPARC_L0_REGNUM ; 
 int /*<<< orphan*/  current_gdbarch ; 
 int extract_unsigned_integer (char*,int) ; 
 int gdbarch_ptr_bit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regcache_raw_supply (struct regcache*,int,char*) ; 
 int sparc_fetch_wcookie () ; 
 int /*<<< orphan*/  store_unsigned_integer (char*,int,int) ; 
 int /*<<< orphan*/  target_read_memory (int,char*,int) ; 

void
sparc_supply_rwindow (struct regcache *regcache, CORE_ADDR sp, int regnum)
{
  int offset = 0;
  char buf[8];
  int i;

  if (sp & 1)
    {
      /* Registers are 64-bit.  */
      sp += BIAS;

      for (i = SPARC_L0_REGNUM; i <= SPARC_I7_REGNUM; i++)
	{
	  if (regnum == i || regnum == -1)
	    {
	      target_read_memory (sp + ((i - SPARC_L0_REGNUM) * 8), buf, 8);
	      regcache_raw_supply (regcache, i, buf);
	    }
	}
    }
  else
    {
      /* Registers are 32-bit.  Toss any sign-extension of the stack
	 pointer.  */
      sp &= 0xffffffffUL;

      /* Clear out the top half of the temporary buffer, and put the
	 register value in the bottom half if we're in 64-bit mode.  */
      if (gdbarch_ptr_bit (current_gdbarch) == 64)
	{
	  memset (buf, 0, 4);
	  offset = 4;
	}

      for (i = SPARC_L0_REGNUM; i <= SPARC_I7_REGNUM; i++)
	{
	  if (regnum == i || regnum == -1)
	    {
	      target_read_memory (sp + ((i - SPARC_L0_REGNUM) * 4),
				  buf + offset, 4);

	      /* Handle StackGhost.  */
	      if (i == SPARC_I7_REGNUM)
		{
		  ULONGEST wcookie = sparc_fetch_wcookie ();
		  ULONGEST i7 = extract_unsigned_integer (buf + offset, 4);

		  store_unsigned_integer (buf + offset, 4, i7 ^ wcookie);
		}

	      regcache_raw_supply (regcache, i, buf);
	    }
	}
    }
}