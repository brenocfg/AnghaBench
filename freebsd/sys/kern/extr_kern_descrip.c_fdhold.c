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
struct proc {struct filedesc* p_fd; } ;
struct filedesc {int /*<<< orphan*/  fd_holdcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PROC_LOCK_ASSERT (struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_acquire (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct filedesc *
fdhold(struct proc *p)
{
	struct filedesc *fdp;

	PROC_LOCK_ASSERT(p, MA_OWNED);
	fdp = p->p_fd;
	if (fdp != NULL)
		refcount_acquire(&fdp->fd_holdcnt);
	return (fdp);
}