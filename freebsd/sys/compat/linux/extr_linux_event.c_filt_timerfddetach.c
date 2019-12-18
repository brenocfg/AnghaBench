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
struct TYPE_2__ {int /*<<< orphan*/  si_note; } ;
struct timerfd {int /*<<< orphan*/  tfd_lock; TYPE_1__ tfd_sel; } ;
struct knote {struct timerfd* kn_hook; } ;

/* Variables and functions */
 int /*<<< orphan*/  knlist_remove (int /*<<< orphan*/ *,struct knote*,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
filt_timerfddetach(struct knote *kn)
{
	struct timerfd *tfd = kn->kn_hook;

	mtx_lock(&tfd->tfd_lock);
	knlist_remove(&tfd->tfd_sel.si_note, kn, 1);
	mtx_unlock(&tfd->tfd_lock);
}