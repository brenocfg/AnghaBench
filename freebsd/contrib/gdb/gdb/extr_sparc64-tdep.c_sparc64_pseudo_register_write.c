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
struct gdbarch {int dummy; } ;
typedef  int ULONGEST ;

/* Variables and functions */
#define  SPARC64_ASI_REGNUM 131 
#define  SPARC64_CCR_REGNUM 130 
#define  SPARC64_CWP_REGNUM 129 
 int SPARC64_D0_REGNUM ; 
 int SPARC64_D30_REGNUM ; 
 int SPARC64_D32_REGNUM ; 
 int SPARC64_D62_REGNUM ; 
 int SPARC64_F32_REGNUM ; 
 int SPARC64_NUM_REGS ; 
#define  SPARC64_PSTATE_REGNUM 128 
 int SPARC64_Q0_REGNUM ; 
 int SPARC64_Q28_REGNUM ; 
 int SPARC64_Q32_REGNUM ; 
 int SPARC64_Q60_REGNUM ; 
 int /*<<< orphan*/  SPARC64_STATE_REGNUM ; 
 int SPARC_F0_REGNUM ; 
 int extract_unsigned_integer (void const*,int) ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 int /*<<< orphan*/  regcache_raw_read_unsigned (struct regcache*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regcache_raw_write (struct regcache*,int,char const*) ; 
 int /*<<< orphan*/  regcache_raw_write_unsigned (struct regcache*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
sparc64_pseudo_register_write (struct gdbarch *gdbarch,
			       struct regcache *regcache,
			       int regnum, const void *buf)
{
  gdb_assert (regnum >= SPARC64_NUM_REGS);

  if (regnum >= SPARC64_D0_REGNUM && regnum <= SPARC64_D30_REGNUM)
    {
      regnum = SPARC_F0_REGNUM + 2 * (regnum - SPARC64_D0_REGNUM);
      regcache_raw_write (regcache, regnum, buf);
      regcache_raw_write (regcache, regnum + 1, ((const char *)buf) + 4);
    }
  else if (regnum >= SPARC64_D32_REGNUM && regnum <= SPARC64_D62_REGNUM)
    {
      regnum = SPARC64_F32_REGNUM + (regnum - SPARC64_D32_REGNUM);
      regcache_raw_write (regcache, regnum, buf);
    }
  else if (regnum >= SPARC64_Q0_REGNUM && regnum <= SPARC64_Q28_REGNUM)
    {
      regnum = SPARC_F0_REGNUM + 4 * (regnum - SPARC64_Q0_REGNUM);
      regcache_raw_write (regcache, regnum, buf);
      regcache_raw_write (regcache, regnum + 1, ((const char *)buf) + 4);
      regcache_raw_write (regcache, regnum + 2, ((const char *)buf) + 8);
      regcache_raw_write (regcache, regnum + 3, ((const char *)buf) + 12);
    }
  else if (regnum >= SPARC64_Q32_REGNUM && regnum <= SPARC64_Q60_REGNUM)
    {
      regnum = SPARC64_F32_REGNUM + 2 * (regnum - SPARC64_Q32_REGNUM);
      regcache_raw_write (regcache, regnum, buf);
      regcache_raw_write (regcache, regnum + 1, ((const char *)buf) + 8);
    }
  else if (regnum == SPARC64_CWP_REGNUM
	   || regnum == SPARC64_PSTATE_REGNUM
	   || regnum == SPARC64_ASI_REGNUM
	   || regnum == SPARC64_CCR_REGNUM)
    {
      ULONGEST state, bits;

      regcache_raw_read_unsigned (regcache, SPARC64_STATE_REGNUM, &state);
      bits = extract_unsigned_integer (buf, 8);
      switch (regnum)
	{
	case SPARC64_CWP_REGNUM:
	  state |= ((bits & ((1 << 5) - 1)) << 0);
	  break;
	case SPARC64_PSTATE_REGNUM:
	  state |= ((bits & ((1 << 12) - 1)) << 8);
	  break;
	case SPARC64_ASI_REGNUM:
	  state |= ((bits & ((1 << 8) - 1)) << 24);
	  break;
	case SPARC64_CCR_REGNUM:
	  state |= ((bits & ((1 << 8) - 1)) << 32);
	  break;
	}
      regcache_raw_write_unsigned (regcache, SPARC64_STATE_REGNUM, state);
    }
}