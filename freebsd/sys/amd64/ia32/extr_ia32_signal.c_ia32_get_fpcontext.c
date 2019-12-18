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
struct thread {int dummy; } ;
struct savefpu {int dummy; } ;
struct ia32_mcontext {char* mc_fpstate; size_t mc_xfpustate_len; int /*<<< orphan*/  mc_flags; int /*<<< orphan*/  mc_fpformat; int /*<<< orphan*/  mc_ownedfp; } ;

/* Variables and functions */
 int /*<<< orphan*/  _MC_IA32_HASFPXSTATE ; 
 int /*<<< orphan*/  bcopy (scalar_t__,char*,size_t) ; 
 int /*<<< orphan*/  bzero (char*,size_t) ; 
 int cpu_max_ext_state_size ; 
 int /*<<< orphan*/  fpuformat () ; 
 int /*<<< orphan*/  fpugetregs (struct thread*) ; 
 scalar_t__ get_pcb_user_save_td (struct thread*) ; 
 int /*<<< orphan*/  use_xsave ; 

__attribute__((used)) static void
ia32_get_fpcontext(struct thread *td, struct ia32_mcontext *mcp,
    char *xfpusave, size_t xfpusave_len)
{
	size_t max_len, len;

	/*
	 * XXX Format of 64bit and 32bit FXSAVE areas differs. FXSAVE
	 * in 32bit mode saves %cs and %ds, while on 64bit it saves
	 * 64bit instruction and data pointers. Ignore the difference
	 * for now, it should be irrelevant for most applications.
	 */
	mcp->mc_ownedfp = fpugetregs(td);
	bcopy(get_pcb_user_save_td(td), &mcp->mc_fpstate[0],
	    sizeof(mcp->mc_fpstate));
	mcp->mc_fpformat = fpuformat();
	if (!use_xsave || xfpusave_len == 0)
		return;
	max_len = cpu_max_ext_state_size - sizeof(struct savefpu);
	len = xfpusave_len;
	if (len > max_len) {
		len = max_len;
		bzero(xfpusave + max_len, len - max_len);
	}
	mcp->mc_flags |= _MC_IA32_HASFPXSTATE;
	mcp->mc_xfpustate_len = len;
	bcopy(get_pcb_user_save_td(td) + 1, xfpusave, len);
}