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
struct knote {struct eventfd* kn_hook; } ;
struct TYPE_2__ {int /*<<< orphan*/  si_note; } ;
struct eventfd {int /*<<< orphan*/  efd_lock; TYPE_1__ efd_sel; } ;

/* Variables and functions */
 int /*<<< orphan*/  knlist_remove (int /*<<< orphan*/ *,struct knote*,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
filt_eventfddetach(struct knote *kn)
{
	struct eventfd *efd = kn->kn_hook;

	mtx_lock(&efd->efd_lock);
	knlist_remove(&efd->efd_sel.si_note, kn, 1);
	mtx_unlock(&efd->efd_lock);
}