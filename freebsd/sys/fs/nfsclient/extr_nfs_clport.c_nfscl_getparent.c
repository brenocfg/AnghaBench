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
struct thread {struct proc* td_proc; } ;
struct proc {scalar_t__ p_pid; int /*<<< orphan*/  p_threads; struct proc* p_pptr; } ;
typedef  struct thread NFSPROC_T ;

/* Variables and functions */
 struct thread* TAILQ_FIRST (int /*<<< orphan*/ *) ; 

NFSPROC_T *
nfscl_getparent(struct thread *td)
{
	struct proc *p;
	struct thread *ptd;

	if (td == NULL)
		return (NULL);
	p = td->td_proc;
	if (p->p_pid == 0)
		return (NULL);
	p = p->p_pptr;
	if (p == NULL)
		return (NULL);
	ptd = TAILQ_FIRST(&p->p_threads);
	return (ptd);
}