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
struct trapframe {int tf_spsr; int /*<<< orphan*/  tf_elr; int /*<<< orphan*/  tf_lr; int /*<<< orphan*/  tf_sp; int /*<<< orphan*/ * tf_x; } ;
struct thread {struct trapframe* td_frame; } ;
struct TYPE_4__ {int gp_spsr; int /*<<< orphan*/  gp_elr; int /*<<< orphan*/  gp_lr; int /*<<< orphan*/  gp_sp; int /*<<< orphan*/ * gp_x; } ;
struct TYPE_5__ {TYPE_1__ mc_gpregs; } ;
typedef  TYPE_2__ mcontext_t ;

/* Variables and functions */
 int GET_MC_CLEAR_RET ; 
 int PSR_C ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int nitems (int /*<<< orphan*/ *) ; 

int
get_mcontext(struct thread *td, mcontext_t *mcp, int clear_ret)
{
	struct trapframe *tf = td->td_frame;

	if (clear_ret & GET_MC_CLEAR_RET) {
		mcp->mc_gpregs.gp_x[0] = 0;
		mcp->mc_gpregs.gp_spsr = tf->tf_spsr & ~PSR_C;
	} else {
		mcp->mc_gpregs.gp_x[0] = tf->tf_x[0];
		mcp->mc_gpregs.gp_spsr = tf->tf_spsr;
	}

	memcpy(&mcp->mc_gpregs.gp_x[1], &tf->tf_x[1],
	    sizeof(mcp->mc_gpregs.gp_x[1]) * (nitems(mcp->mc_gpregs.gp_x) - 1));

	mcp->mc_gpregs.gp_sp = tf->tf_sp;
	mcp->mc_gpregs.gp_lr = tf->tf_lr;
	mcp->mc_gpregs.gp_elr = tf->tf_elr;

	return (0);
}