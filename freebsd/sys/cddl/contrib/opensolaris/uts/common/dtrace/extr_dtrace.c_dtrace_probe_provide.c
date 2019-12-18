#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * mod_mp; scalar_t__ mod_busy; struct TYPE_9__* mod_next; } ;
typedef  TYPE_2__ modctl_t ;
struct TYPE_8__ {int /*<<< orphan*/  (* dtps_provide_module ) (int /*<<< orphan*/ ,TYPE_2__*) ;int /*<<< orphan*/  (* dtps_provide ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_10__ {int /*<<< orphan*/  dtpv_arg; TYPE_1__ dtpv_pops; struct TYPE_10__* dtpv_next; } ;
typedef  TYPE_3__ dtrace_provider_t ;
typedef  int /*<<< orphan*/  dtrace_probedesc_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 TYPE_3__* dtrace_provider ; 
 int /*<<< orphan*/  dtrace_provider_lock ; 
 int /*<<< orphan*/  mod_lock ; 
 TYPE_2__ modules ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static void
dtrace_probe_provide(dtrace_probedesc_t *desc, dtrace_provider_t *prv)
{
#ifdef illumos
	modctl_t *ctl;
#endif
	int all = 0;

	ASSERT(MUTEX_HELD(&dtrace_provider_lock));

	if (prv == NULL) {
		all = 1;
		prv = dtrace_provider;
	}

	do {
		/*
		 * First, call the blanket provide operation.
		 */
		prv->dtpv_pops.dtps_provide(prv->dtpv_arg, desc);

#ifdef illumos
		/*
		 * Now call the per-module provide operation.  We will grab
		 * mod_lock to prevent the list from being modified.  Note
		 * that this also prevents the mod_busy bits from changing.
		 * (mod_busy can only be changed with mod_lock held.)
		 */
		mutex_enter(&mod_lock);

		ctl = &modules;
		do {
			if (ctl->mod_busy || ctl->mod_mp == NULL)
				continue;

			prv->dtpv_pops.dtps_provide_module(prv->dtpv_arg, ctl);

		} while ((ctl = ctl->mod_next) != &modules);

		mutex_exit(&mod_lock);
#endif
	} while (all && (prv = prv->dtpv_next) != NULL);
}