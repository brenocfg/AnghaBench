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
struct trapframe {int /*<<< orphan*/  tf_sstatus; int /*<<< orphan*/  tf_sepc; int /*<<< orphan*/  tf_tp; int /*<<< orphan*/  tf_gp; int /*<<< orphan*/  tf_sp; int /*<<< orphan*/  tf_ra; int /*<<< orphan*/  tf_a; int /*<<< orphan*/  tf_s; int /*<<< orphan*/  tf_t; } ;
struct thread {struct trapframe* td_frame; } ;
struct TYPE_4__ {int /*<<< orphan*/  gp_sstatus; int /*<<< orphan*/  gp_sepc; int /*<<< orphan*/  gp_tp; int /*<<< orphan*/  gp_gp; int /*<<< orphan*/  gp_sp; int /*<<< orphan*/  gp_ra; scalar_t__* gp_t; scalar_t__* gp_a; scalar_t__* gp_s; } ;
struct TYPE_5__ {TYPE_1__ mc_gpregs; } ;
typedef  TYPE_2__ mcontext_t ;

/* Variables and functions */
 int GET_MC_CLEAR_RET ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ ,int) ; 

int
get_mcontext(struct thread *td, mcontext_t *mcp, int clear_ret)
{
	struct trapframe *tf = td->td_frame;

	memcpy(mcp->mc_gpregs.gp_t, tf->tf_t, sizeof(mcp->mc_gpregs.gp_t));
	memcpy(mcp->mc_gpregs.gp_s, tf->tf_s, sizeof(mcp->mc_gpregs.gp_s));
	memcpy(mcp->mc_gpregs.gp_a, tf->tf_a, sizeof(mcp->mc_gpregs.gp_a));

	if (clear_ret & GET_MC_CLEAR_RET) {
		mcp->mc_gpregs.gp_a[0] = 0;
		mcp->mc_gpregs.gp_t[0] = 0; /* clear syscall error */
	}

	mcp->mc_gpregs.gp_ra = tf->tf_ra;
	mcp->mc_gpregs.gp_sp = tf->tf_sp;
	mcp->mc_gpregs.gp_gp = tf->tf_gp;
	mcp->mc_gpregs.gp_tp = tf->tf_tp;
	mcp->mc_gpregs.gp_sepc = tf->tf_sepc;
	mcp->mc_gpregs.gp_sstatus = tf->tf_sstatus;

	return (0);
}