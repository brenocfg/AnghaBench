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
typedef  int u_long ;
struct trapframe {int* tf_out; } ;
struct thread {TYPE_1__* td_proc; } ;
struct rwindow {int* rw_in; } ;
struct TYPE_2__ {int /*<<< orphan*/  p_comm; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTR1 (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  CTR3 (int /*<<< orphan*/ ,char*,struct thread*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  KTR_TRAP ; 
 int SIGILL ; 
 scalar_t__ SPOFF ; 
 int copyin (void*,struct rwindow*,int) ; 
 int rwindow_save (struct thread*) ; 

int
rwindow_load(struct thread *td, struct trapframe *tf, int n)
{
	struct rwindow rw;
	u_long usp;
	int error;
	int i;

	CTR3(KTR_TRAP, "rwindow_load: td=%p (%s) n=%d",
	    td, td->td_proc->p_comm, n);

	/*
	 * In case current window is still only on-chip, push it out;
	 * if it cannot get all the way out, we cannot continue either.
	 */
	if ((error = rwindow_save(td)) != 0)
		return (error);
	usp = tf->tf_out[6];
	for (i = 0; i < n; i++) {
		CTR1(KTR_TRAP, "rwindow_load: usp=%#lx", usp);
		usp += SPOFF;
		if ((error = (usp & 0x7)) != 0)
			break;
		error = copyin((void *)usp, &rw, sizeof rw);
		usp = rw.rw_in[6];
	}
	CTR1(KTR_TRAP, "rwindow_load: error=%d", error);
	return (error == 0 ? 0 : SIGILL);
}