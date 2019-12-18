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
struct trapframe {int /*<<< orphan*/  tf_wstate; } ;
struct thread {struct trapframe* td_frame; } ;
struct reg {int /*<<< orphan*/  r_wstate; int /*<<< orphan*/  r_tstate; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  TSTATE_SECURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (struct reg*,struct trapframe*,int) ; 

int
set_regs(struct thread *td, struct reg *regs)
{
	struct trapframe *tf;

	if (!TSTATE_SECURE(regs->r_tstate))
		return (EINVAL);
	tf = td->td_frame;
	regs->r_wstate = tf->tf_wstate;
	bcopy(regs, tf, sizeof(*regs));
	return (0);
}