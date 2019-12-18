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
 int /*<<< orphan*/  PT_WRITE_FPR ; 
 int /*<<< orphan*/  PT_WRITE_GPR ; 
 int SP_REGNUM ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exec_one_dummy_insn () ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gdb_stderr ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  memcpy (long long*,int*,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  regcache_collect (int,int*) ; 
 int regmap (int,int*) ; 
 int /*<<< orphan*/  rs6000_ptrace32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rs6000_ptrace64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void
store_register (int regno)
{
  int addr[MAX_REGISTER_SIZE];
  int nr, isfloat;

  /* Fetch the register's value from the register cache.  */
  regcache_collect (regno, addr);

  /* -1 can be a successful return value, so infer errors from errno. */
  errno = 0;

  nr = regmap (regno, &isfloat);

  /* Floating-point registers. */
  if (isfloat)
    rs6000_ptrace32 (PT_WRITE_FPR, PIDGET (inferior_ptid), addr, nr, 0);

  /* Bogus register number. */
  else if (nr < 0)
    {
      if (regno >= NUM_REGS)
	fprintf_unfiltered (gdb_stderr,
			    "gdb error: register no %d not implemented.\n",
			    regno);
    }

  /* Fixed-point registers. */
  else
    {
      if (regno == SP_REGNUM)
	/* Execute one dummy instruction (which is a breakpoint) in inferior
	   process to give kernel a chance to do internal housekeeping.
	   Otherwise the following ptrace(2) calls will mess up user stack
	   since kernel will get confused about the bottom of the stack
	   (%sp). */
	exec_one_dummy_insn ();

      /* The PT_WRITE_GPR operation is rather odd.  For 32-bit inferiors,
         the register's value is passed by value, but for 64-bit inferiors,
	 the address of a buffer containing the value is passed.  */
      if (!ARCH64 ())
	rs6000_ptrace32 (PT_WRITE_GPR, PIDGET (inferior_ptid), (int *)nr, *addr, 0);
      else
	{
	  /* PT_WRITE_GPR requires the buffer parameter to point to an 8-byte
	     area, even if the register is really only 32 bits. */
	  long long buf;
	  if (DEPRECATED_REGISTER_RAW_SIZE (regno) == 8)
	    memcpy (&buf, addr, 8);
	  else
	    buf = *addr;
	  rs6000_ptrace64 (PT_WRITE_GPR, PIDGET (inferior_ptid), nr, 0, (int *)&buf);
	}
    }

  if (errno)
    {
      perror ("ptrace write");
      errno = 0;
    }
}