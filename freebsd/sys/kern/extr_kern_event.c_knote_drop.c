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
struct knote {int kn_status; TYPE_1__* kn_fop; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* f_detach ) (struct knote*) ;} ;

/* Variables and functions */
 int KN_DETACHED ; 
 int /*<<< orphan*/  knote_drop_detached (struct knote*,struct thread*) ; 
 int /*<<< orphan*/  stub1 (struct knote*) ; 

__attribute__((used)) static void
knote_drop(struct knote *kn, struct thread *td)
{

	if ((kn->kn_status & KN_DETACHED) == 0)
		kn->kn_fop->f_detach(kn);
	knote_drop_detached(kn, td);
}