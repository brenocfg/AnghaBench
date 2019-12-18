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
struct thread {int dummy; } ;
struct proc {int p_flag2; int p_flag; TYPE_1__* p_pptr; int /*<<< orphan*/  p_pid; } ;
struct TYPE_2__ {int p_pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int P2_NOTRACE ; 
 int P_TRACED ; 

__attribute__((used)) static int
trace_status(struct thread *td, struct proc *p, int *data)
{

	if ((p->p_flag2 & P2_NOTRACE) != 0) {
		KASSERT((p->p_flag & P_TRACED) == 0,
		    ("%d traced but tracing disabled", p->p_pid));
		*data = -1;
	} else if ((p->p_flag & P_TRACED) != 0) {
		*data = p->p_pptr->p_pid;
	} else {
		*data = 0;
	}
	return (0);
}