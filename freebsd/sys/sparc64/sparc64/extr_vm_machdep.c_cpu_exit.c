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
struct thread {struct proc* td_proc; } ;
struct TYPE_2__ {int /*<<< orphan*/ * md_utrap; int /*<<< orphan*/ * md_sigtramp; } ;
struct proc {TYPE_1__ p_md; } ;

/* Variables and functions */
 int /*<<< orphan*/  utrap_free (int /*<<< orphan*/ *) ; 

void
cpu_exit(struct thread *td)
{
	struct proc *p;

	p = td->td_proc;
	p->p_md.md_sigtramp = NULL;
	if (p->p_md.md_utrap != NULL) {
		utrap_free(p->p_md.md_utrap);
		p->p_md.md_utrap = NULL;
	}
}