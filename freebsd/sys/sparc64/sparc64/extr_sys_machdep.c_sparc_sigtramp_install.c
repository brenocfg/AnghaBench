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
struct sparc_sigtramp_install_args {scalar_t__ sia_new; int /*<<< orphan*/ * sia_old; } ;
struct TYPE_2__ {scalar_t__ md_sigtramp; } ;
struct proc {TYPE_1__ p_md; } ;
typedef  int /*<<< orphan*/  sia ;

/* Variables and functions */
 int EFAULT ; 
 int copyin (char*,struct sparc_sigtramp_install_args*,int) ; 
 scalar_t__ suword (int /*<<< orphan*/ *,long) ; 

__attribute__((used)) static int
sparc_sigtramp_install(struct thread *td, char *args)
{
	struct sparc_sigtramp_install_args sia;
	struct proc *p;
	int error;

	p = td->td_proc;
	if ((error = copyin(args, &sia, sizeof(sia))) != 0)
		return (error);
	if (sia.sia_old != NULL) {
		if (suword(sia.sia_old, (long)p->p_md.md_sigtramp) != 0)
			return (EFAULT);
	}
	p->p_md.md_sigtramp = sia.sia_new;
	return (0);
}