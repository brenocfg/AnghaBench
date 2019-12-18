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
struct proc {int /*<<< orphan*/  p_klist; } ;
struct TYPE_2__ {struct proc* p_proc; } ;
struct knote {int /*<<< orphan*/  kn_flags; TYPE_1__ kn_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_CLEAR ; 
 struct proc* curproc ; 
 int /*<<< orphan*/  knlist_add (int /*<<< orphan*/ ,struct knote*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
filt_sigattach(struct knote *kn)
{
	struct proc *p = curproc;

	kn->kn_ptr.p_proc = p;
	kn->kn_flags |= EV_CLEAR;		/* automatically set */

	knlist_add(p->p_klist, kn, 0);

	return (0);
}