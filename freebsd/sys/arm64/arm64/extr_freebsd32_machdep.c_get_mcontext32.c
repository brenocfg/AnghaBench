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
struct trapframe {int tf_spsr; int* tf_x; int tf_elr; } ;
struct thread {struct trapframe* td_frame; struct pcb* td_pcb; } ;
struct pcb {int dummy; } ;
struct TYPE_3__ {int* mc_gregset; int /*<<< orphan*/  mc_spare; scalar_t__ mc_vfp_ptr; scalar_t__ mc_vfp_size; } ;
typedef  TYPE_1__ mcontext32_t ;

/* Variables and functions */
 int GET_MC_CLEAR_RET ; 
 int PSR_C ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
get_mcontext32(struct thread *td, mcontext32_t *mcp, int flags)
{
	struct pcb *pcb;
	struct trapframe *tf;
	int i;

	pcb = td->td_pcb;
	tf = td->td_frame;

	if ((flags & GET_MC_CLEAR_RET) != 0) {
		mcp->mc_gregset[0] = 0;
		mcp->mc_gregset[16] = tf->tf_spsr & ~PSR_C;
	} else {
		mcp->mc_gregset[0] = tf->tf_x[0];
		mcp->mc_gregset[16] = tf->tf_spsr;
	}
	for (i = 1; i < 15; i++)
		mcp->mc_gregset[i] = tf->tf_x[i];
	mcp->mc_gregset[15] = tf->tf_elr;

	mcp->mc_vfp_size = 0;
	mcp->mc_vfp_ptr = 0;

	memset(mcp->mc_spare, 0, sizeof(mcp->mc_spare));
}