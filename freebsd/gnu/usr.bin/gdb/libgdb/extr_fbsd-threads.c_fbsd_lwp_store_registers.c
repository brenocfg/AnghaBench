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
struct TYPE_2__ {int /*<<< orphan*/  (* to_store_registers ) (int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GET_LWP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_LWP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PT_GETFPREGS ; 
 int /*<<< orphan*/  PT_GETREGS ; 
 int /*<<< orphan*/  PT_GETXMMREGS ; 
 int /*<<< orphan*/  PT_SETFPREGS ; 
 int /*<<< orphan*/  PT_SETREGS ; 
 int /*<<< orphan*/  PT_SETXMMREGS ; 
 TYPE_1__ child_ops ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fill_fpregset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fill_gregset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  i387_fill_fxsave (char*,int) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 char* safe_strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int) ; 

__attribute__((used)) static void
fbsd_lwp_store_registers (int regno)
{
  gregset_t gregs;
  fpregset_t fpregs;
  lwpid_t lwp;
#ifdef PT_GETXMMREGS
  char xmmregs[512];
#endif

  /* FIXME, is it possible ? */
  if (!IS_LWP (inferior_ptid))
    {
      child_ops.to_store_registers (regno);
      return ;
    }

  lwp = GET_LWP (inferior_ptid);
  if (regno != -1)
    if (ptrace (PT_GETREGS, lwp, (caddr_t) &gregs, 0) == -1)
      error ("Cannot get lwp %d registers: %s\n", lwp, safe_strerror (errno));

  fill_gregset (&gregs, regno);
  if (ptrace (PT_SETREGS, lwp, (caddr_t) &gregs, 0) == -1)
      error ("Cannot set lwp %d registers: %s\n", lwp, safe_strerror (errno));

#ifdef PT_GETXMMREGS
  if (regno != -1)
    if (ptrace (PT_GETXMMREGS, lwp, xmmregs, 0) == -1)
      goto noxmm;

  i387_fill_fxsave (xmmregs, regno);
  if (ptrace (PT_SETXMMREGS, lwp, xmmregs, 0) == -1)
    goto noxmm;

  return;

noxmm:
#endif

  if (regno != -1)
    if (ptrace (PT_GETFPREGS, lwp, (caddr_t) &fpregs, 0) == -1)
      error ("Cannot get lwp %d float registers: %s\n", lwp,
             safe_strerror (errno));

  fill_fpregset (&fpregs, regno);
  if (ptrace (PT_SETFPREGS, lwp, (caddr_t) &fpregs, 0) == -1)
     error ("Cannot set lwp %d float registers: %s\n", lwp,
            safe_strerror (errno));
}