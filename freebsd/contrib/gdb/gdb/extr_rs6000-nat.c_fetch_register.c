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

/* Variables and functions */
 int /*<<< orphan*/  ARCH64 () ; 
 int DEPRECATED_REGISTER_RAW_SIZE (int) ; 
 int MAX_REGISTER_SIZE ; 
 int NUM_REGS ; 
 int /*<<< orphan*/  PIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PT_READ_FPR ; 
 int /*<<< orphan*/  PT_READ_GPR ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gdb_stderr ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  memcpy (int*,long long*,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int regmap (int,int*) ; 
 int rs6000_ptrace32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rs6000_ptrace64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  supply_register (int,char*) ; 

__attribute__((used)) static void
fetch_register (int regno)
{
  int addr[MAX_REGISTER_SIZE];
  int nr, isfloat;

  /* Retrieved values may be -1, so infer errors from errno. */
  errno = 0;

  nr = regmap (regno, &isfloat);

  /* Floating-point registers. */
  if (isfloat)
    rs6000_ptrace32 (PT_READ_FPR, PIDGET (inferior_ptid), addr, nr, 0);

  /* Bogus register number. */
  else if (nr < 0)
    {
      if (regno >= NUM_REGS)
	fprintf_unfiltered (gdb_stderr,
			    "gdb error: register no %d not implemented.\n",
			    regno);
      return;
    }

  /* Fixed-point registers. */
  else
    {
      if (!ARCH64 ())
	*addr = rs6000_ptrace32 (PT_READ_GPR, PIDGET (inferior_ptid), (int *)nr, 0, 0);
      else
	{
	  /* PT_READ_GPR requires the buffer parameter to point to long long,
	     even if the register is really only 32 bits. */
	  long long buf;
	  rs6000_ptrace64 (PT_READ_GPR, PIDGET (inferior_ptid), nr, 0, (int *)&buf);
	  if (DEPRECATED_REGISTER_RAW_SIZE (regno) == 8)
	    memcpy (addr, &buf, 8);
	  else
	    *addr = buf;
	}
    }

  if (!errno)
    supply_register (regno, (char *) addr);
  else
    {
#if 0
      /* FIXME: this happens 3 times at the start of each 64-bit program. */
      perror ("ptrace read");
#endif
      errno = 0;
    }
}