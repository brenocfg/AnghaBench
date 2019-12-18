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
struct knote {TYPE_1__ kn_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  knlist_remove (int /*<<< orphan*/ ,struct knote*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
filt_sigdetach(struct knote *kn)
{
	struct proc *p = kn->kn_ptr.p_proc;

	knlist_remove(p->p_klist, kn, 0);
}