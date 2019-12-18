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
typedef  int /*<<< orphan*/  gregset_t ;
typedef  int /*<<< orphan*/  fpregset_t ;
typedef  int /*<<< orphan*/  fpregs ;
typedef  int /*<<< orphan*/  ULONGEST ;
typedef  int /*<<< orphan*/  PTRACE_ARG3_TYPE ;

/* Variables and functions */
 int PIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PTRACE_GETFPREGS ; 
 int /*<<< orphan*/  PTRACE_GETREGS ; 
 int /*<<< orphan*/  PTRACE_SETFPREGS ; 
 int /*<<< orphan*/  PTRACE_SETREGS ; 
 int SPARC_I7_REGNUM ; 
 int SPARC_L0_REGNUM ; 
 int SPARC_SP_REGNUM ; 
 int TIDGET (int /*<<< orphan*/ ) ; 
 struct regcache* current_regcache ; 
 int /*<<< orphan*/  inferior_ptid ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  perror_with_name (char*) ; 
 int ptrace (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regcache_cooked_read_unsigned (struct regcache*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sparc_collect_fpregset (struct regcache*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sparc_collect_gregset (int /*<<< orphan*/ ,struct regcache*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sparc_collect_rwindow (struct regcache*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sparc_fpregset_supplies_p (int) ; 
 int /*<<< orphan*/  sparc_gregset ; 
 scalar_t__ sparc_gregset_supplies_p (int) ; 

void
store_inferior_registers (int regnum)
{
  struct regcache *regcache = current_regcache;
  int pid;

  /* NOTE: cagney/2002-12-02: See comment in fetch_inferior_registers
     about threaded assumptions.  */
  pid = TIDGET (inferior_ptid);
  if (pid == 0)
    pid = PIDGET (inferior_ptid);

  if (regnum == -1 || sparc_gregset_supplies_p (regnum))
    {
      gregset_t regs;

      if (ptrace (PTRACE_GETREGS, pid, (PTRACE_ARG3_TYPE) &regs, 0) == -1)
	perror_with_name ("Couldn't get registers");

      sparc_collect_gregset (sparc_gregset, regcache, regnum, &regs);

      if (ptrace (PTRACE_SETREGS, pid, (PTRACE_ARG3_TYPE) &regs, 0) == -1)
	perror_with_name ("Couldn't write registers");

      /* Deal with the stack regs.  */
      if (regnum == -1 || regnum == SPARC_SP_REGNUM
	  || (regnum >= SPARC_L0_REGNUM && regnum <= SPARC_I7_REGNUM))
	{
	  ULONGEST sp;

	  regcache_cooked_read_unsigned (regcache, SPARC_SP_REGNUM, &sp);
	  sparc_collect_rwindow (regcache, sp, regnum);
	}

      if (regnum != -1)
	return;
    }

  if (regnum == -1 || sparc_fpregset_supplies_p (regnum))
    {
      fpregset_t fpregs, saved_fpregs;

      if (ptrace (PTRACE_GETFPREGS, pid, (PTRACE_ARG3_TYPE) &fpregs, 0) == -1)
	perror_with_name ("Couldn't get floating-point registers");

      memcpy (&saved_fpregs, &fpregs, sizeof (fpregs));
      sparc_collect_fpregset (regcache, regnum, &fpregs);

      /* Writing the floating-point registers will fail on NetBSD with
	 EINVAL if the inferior process doesn't have an FPU state
	 (i.e. if it didn't use the FPU yet).  Therefore we don't try
	 to write the registers if nothing changed.  */
      if (memcmp (&saved_fpregs, &fpregs, sizeof (fpregs)) != 0)
	{
	  if (ptrace (PTRACE_SETFPREGS, pid,
		      (PTRACE_ARG3_TYPE) &fpregs, 0) == -1)
	    perror_with_name ("Couldn't write floating-point registers");
	}

      if (regnum != -1)
	return;
    }
}