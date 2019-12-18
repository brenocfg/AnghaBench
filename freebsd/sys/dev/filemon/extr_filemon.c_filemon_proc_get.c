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
struct proc {int /*<<< orphan*/ * p_filemon; } ;
struct filemon {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 struct filemon* filemon_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct filemon *
filemon_proc_get(struct proc *p)
{
	struct filemon *filemon;

	if (p->p_filemon == NULL)
		return (NULL);
	PROC_LOCK(p);
	filemon = filemon_acquire(p->p_filemon);
	PROC_UNLOCK(p);

	if (filemon == NULL)
		return (NULL);
	/*
	 * The p->p_filemon may have changed by now.  That case is handled
	 * by the exit and fork hooks and filemon_attach_proc specially.
	 */
	sx_xlock(&filemon->lock);
	return (filemon);
}