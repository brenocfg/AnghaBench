#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* p_lio; } ;
struct knote {TYPE_2__ kn_ptr; } ;
struct knlist {int /*<<< orphan*/  kl_lockarg; int /*<<< orphan*/  (* kl_unlock ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* kl_lock ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {struct knlist klist; } ;

/* Variables and functions */
 int /*<<< orphan*/  knlist_empty (struct knlist*) ; 
 int /*<<< orphan*/  knlist_remove (struct knlist*,struct knote*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
filt_liodetach(struct knote *kn)
{
	struct knlist *knl;

	knl = &kn->kn_ptr.p_lio->klist;
	knl->kl_lock(knl->kl_lockarg);
	if (!knlist_empty(knl))
		knlist_remove(knl, kn, 1);
	knl->kl_unlock(knl->kl_lockarg);
}