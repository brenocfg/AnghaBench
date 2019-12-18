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
typedef  int /*<<< orphan*/  PTRACE_ARG3_TYPE ;

/* Variables and functions */
 int PIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PTRACE_GETFPREGS ; 
 int /*<<< orphan*/  PTRACE_GETREGS ; 
 int SPARC_G0_REGNUM ; 
 int TIDGET (int /*<<< orphan*/ ) ; 
 struct regcache* current_regcache ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  perror_with_name (char*) ; 
 int ptrace (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regcache_raw_supply (struct regcache*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ sparc_fpregset_supplies_p (int) ; 
 int /*<<< orphan*/  sparc_gregset ; 
 scalar_t__ sparc_gregset_supplies_p (int) ; 
 int /*<<< orphan*/  sparc_supply_fpregset (struct regcache*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sparc_supply_gregset (int /*<<< orphan*/ ,struct regcache*,int,int /*<<< orphan*/ *) ; 

void
fetch_inferior_registers (int regnum)
{
  struct regcache *regcache = current_regcache;
  int pid;

  /* NOTE: cagney/2002-12-03: This code assumes that the currently
     selected light weight processes' registers can be written
     directly into the selected thread's register cache.  This works
     fine when given an 1:1 LWP:thread model (such as found on
     GNU/Linux) but will, likely, have problems when used on an N:1
     (userland threads) or N:M (userland multiple LWP) model.  In the
     case of the latter two, the LWP's registers do not necessarily
     belong to the selected thread (the LWP could be in the middle of
     executing the thread switch code).

     These functions should instead be paramaterized with an explicit
     object (struct regcache, struct thread_info?) into which the LWPs
     registers can be written.  */
  pid = TIDGET (inferior_ptid);
  if (pid == 0)
    pid = PIDGET (inferior_ptid);

  if (regnum == SPARC_G0_REGNUM)
    {
      regcache_raw_supply (regcache, SPARC_G0_REGNUM, NULL);
      return;
    }

  if (regnum == -1 || sparc_gregset_supplies_p (regnum))
    {
      gregset_t regs;

      if (ptrace (PTRACE_GETREGS, pid, (PTRACE_ARG3_TYPE) &regs, 0) == -1)
	perror_with_name ("Couldn't get registers");

      sparc_supply_gregset (sparc_gregset, regcache, -1, &regs);
      if (regnum != -1)
	return;
    }

  if (regnum == -1 || sparc_fpregset_supplies_p (regnum))
    {
      fpregset_t fpregs;

      if (ptrace (PTRACE_GETFPREGS, pid, (PTRACE_ARG3_TYPE) &fpregs, 0) == -1)
	perror_with_name ("Couldn't get floating point status");

      sparc_supply_fpregset (regcache, -1, &fpregs);
    }
}