#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct trapframe {int tf_spsr; int /*<<< orphan*/  tf_elr; int /*<<< orphan*/  tf_lr; int /*<<< orphan*/  tf_sp; int /*<<< orphan*/  tf_x; } ;
struct thread {struct trapframe* td_frame; } ;
struct TYPE_4__ {int gp_spsr; int /*<<< orphan*/  gp_elr; int /*<<< orphan*/  gp_lr; int /*<<< orphan*/  gp_sp; int /*<<< orphan*/  gp_x; } ;
struct TYPE_5__ {TYPE_1__ mc_gpregs; } ;
typedef  TYPE_2__ mcontext_t ;

/* Variables and functions */
 int EINVAL ; 
 int PSR_AARCH32 ; 
 int PSR_DAIF ; 
 int PSR_M_EL0t ; 
 int PSR_M_MASK ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
set_mcontext(struct thread *td, mcontext_t *mcp)
{
	struct trapframe *tf = td->td_frame;
	uint32_t spsr;

	spsr = mcp->mc_gpregs.gp_spsr;
	if ((spsr & PSR_M_MASK) != PSR_M_EL0t ||
	    (spsr & PSR_AARCH32) != 0 ||
	    (spsr & PSR_DAIF) != (td->td_frame->tf_spsr & PSR_DAIF))
		return (EINVAL); 

	memcpy(tf->tf_x, mcp->mc_gpregs.gp_x, sizeof(tf->tf_x));

	tf->tf_sp = mcp->mc_gpregs.gp_sp;
	tf->tf_lr = mcp->mc_gpregs.gp_lr;
	tf->tf_elr = mcp->mc_gpregs.gp_elr;
	tf->tf_spsr = mcp->mc_gpregs.gp_spsr;

	return (0);
}