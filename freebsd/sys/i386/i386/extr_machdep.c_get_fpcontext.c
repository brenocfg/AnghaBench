#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  union savefpu {int dummy; } savefpu ;
struct thread {int dummy; } ;
struct TYPE_3__ {char* mc_fpstate; size_t mc_xfpustate_len; int /*<<< orphan*/  mc_flags; int /*<<< orphan*/  mc_fpformat; int /*<<< orphan*/  mc_ownedfp; } ;
typedef  TYPE_1__ mcontext_t ;

/* Variables and functions */
 int /*<<< orphan*/  _MC_HASFPXSTATE ; 
 int /*<<< orphan*/  bcopy (scalar_t__,char*,size_t) ; 
 int /*<<< orphan*/  bzero (char*,size_t) ; 
 int cpu_max_ext_state_size ; 
 scalar_t__ get_pcb_user_save_td (struct thread*) ; 
 int /*<<< orphan*/  npxformat () ; 
 int /*<<< orphan*/  npxgetregs (struct thread*) ; 
 int /*<<< orphan*/  use_xsave ; 

__attribute__((used)) static void
get_fpcontext(struct thread *td, mcontext_t *mcp, char *xfpusave,
    size_t xfpusave_len)
{
	size_t max_len, len;

	mcp->mc_ownedfp = npxgetregs(td);
	bcopy(get_pcb_user_save_td(td), &mcp->mc_fpstate[0],
	    sizeof(mcp->mc_fpstate));
	mcp->mc_fpformat = npxformat();
	if (!use_xsave || xfpusave_len == 0)
		return;
	max_len = cpu_max_ext_state_size - sizeof(union savefpu);
	len = xfpusave_len;
	if (len > max_len) {
		len = max_len;
		bzero(xfpusave + max_len, len - max_len);
	}
	mcp->mc_flags |= _MC_HASFPXSTATE;
	mcp->mc_xfpustate_len = len;
	bcopy(get_pcb_user_save_td(td) + 1, xfpusave, len);
}