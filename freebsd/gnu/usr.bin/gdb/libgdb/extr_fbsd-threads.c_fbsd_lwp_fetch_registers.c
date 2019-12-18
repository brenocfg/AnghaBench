#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lwpid_t ;
typedef  int /*<<< orphan*/  gregset_t ;
typedef  int /*<<< orphan*/  fpregset_t ;
typedef  char* caddr_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* to_fetch_registers ) (int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GET_PID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PT_GETFPREGS ; 
 int /*<<< orphan*/  PT_GETREGS ; 
 int /*<<< orphan*/  PT_GETXMMREGS ; 
 int /*<<< orphan*/  current_regcache ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  i387_supply_fxsave (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 TYPE_1__ orig_core_ops ; 
 int ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 char* safe_strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int) ; 
 int /*<<< orphan*/  supply_fpregset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  supply_gregset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  target_has_execution ; 

__attribute__((used)) static void
fbsd_lwp_fetch_registers (int regno)
{
  gregset_t gregs;
  fpregset_t fpregs;
  lwpid_t lwp;
#ifdef PT_GETXMMREGS
  char xmmregs[512];
#endif

  if (!target_has_execution)
    {
      orig_core_ops.to_fetch_registers (-1);
      return;
    }

  /* XXX: We've replaced the pid with the lwpid for GDB's benefit. */
  lwp = GET_PID (inferior_ptid);

  if (ptrace (PT_GETREGS, lwp, (caddr_t) &gregs, 0) == -1)
    error ("Cannot get lwp %d registers: %s\n", lwp, safe_strerror (errno));
  supply_gregset (&gregs);
  
#ifdef PT_GETXMMREGS
  if (ptrace (PT_GETXMMREGS, lwp, xmmregs, 0) == 0)
    {
      i387_supply_fxsave (current_regcache, -1, xmmregs);
    }
  else
    {
#endif
      if (ptrace (PT_GETFPREGS, lwp, (caddr_t) &fpregs, 0) == -1)
	error ("Cannot get lwp %d registers: %s\n ", lwp, safe_strerror (errno));
      supply_fpregset (&fpregs);
#ifdef PT_GETXMMREGS
    }
#endif
}