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
struct trapframe {int /*<<< orphan*/  tf_spsr; int /*<<< orphan*/  tf_elr; int /*<<< orphan*/ * tf_x; } ;
struct thread {struct trapframe* td_frame; } ;
typedef  int /*<<< orphan*/  mcontext32_vfp_t ;
struct TYPE_3__ {int mc_vfp_size; scalar_t__ mc_vfp_ptr; int /*<<< orphan*/ * mc_gregset; } ;
typedef  TYPE_1__ mcontext32_t ;
typedef  int /*<<< orphan*/  mc_vfp ;

/* Variables and functions */
 int EFAULT ; 
 scalar_t__ copyin (void*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_fpcontext32 (struct thread*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
set_mcontext32(struct thread *td, mcontext32_t *mcp)
{
	struct trapframe *tf;
	mcontext32_vfp_t mc_vfp;
	int i;

	tf = td->td_frame;

	for (i = 0; i < 15; i++)
		tf->tf_x[i] = mcp->mc_gregset[i];
	tf->tf_elr = mcp->mc_gregset[15];
	tf->tf_spsr = mcp->mc_gregset[16];
#ifdef VFP
	if (mcp->mc_vfp_size == sizeof(mc_vfp) && mcp->mc_vfp_ptr != 0) {
		if (copyin((void *)(uintptr_t)mcp->mc_vfp_ptr, &mc_vfp,
					sizeof(mc_vfp)) != 0)
			return (EFAULT);
		set_fpcontext32(td, &mc_vfp);
	}
#endif

	return (0);
}