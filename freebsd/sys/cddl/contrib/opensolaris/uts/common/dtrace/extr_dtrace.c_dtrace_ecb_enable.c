#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  (* dtps_enable ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_9__ {int /*<<< orphan*/  dtpv_arg; TYPE_2__ dtpv_pops; } ;
typedef  TYPE_3__ dtrace_provider_t ;
struct TYPE_10__ {scalar_t__ dtpr_predcache; TYPE_5__* dtpr_ecb_last; int /*<<< orphan*/  dtpr_arg; int /*<<< orphan*/  dtpr_id; TYPE_5__* dtpr_ecb; TYPE_3__* dtpr_provider; } ;
typedef  TYPE_4__ dtrace_probe_t ;
struct TYPE_11__ {struct TYPE_11__* dte_next; TYPE_1__* dte_predicate; TYPE_4__* dte_probe; } ;
typedef  TYPE_5__ dtrace_ecb_t ;
struct TYPE_7__ {scalar_t__ dtp_cacheid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_lock ; 
 int /*<<< orphan*/  dtrace_lock ; 
 int /*<<< orphan*/  dtrace_sync () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dtrace_ecb_enable(dtrace_ecb_t *ecb)
{
	dtrace_probe_t *probe = ecb->dte_probe;

	ASSERT(MUTEX_HELD(&cpu_lock));
	ASSERT(MUTEX_HELD(&dtrace_lock));
	ASSERT(ecb->dte_next == NULL);

	if (probe == NULL) {
		/*
		 * This is the NULL probe -- there's nothing to do.
		 */
		return;
	}

	if (probe->dtpr_ecb == NULL) {
		dtrace_provider_t *prov = probe->dtpr_provider;

		/*
		 * We're the first ECB on this probe.
		 */
		probe->dtpr_ecb = probe->dtpr_ecb_last = ecb;

		if (ecb->dte_predicate != NULL)
			probe->dtpr_predcache = ecb->dte_predicate->dtp_cacheid;

		prov->dtpv_pops.dtps_enable(prov->dtpv_arg,
		    probe->dtpr_id, probe->dtpr_arg);
	} else {
		/*
		 * This probe is already active.  Swing the last pointer to
		 * point to the new ECB, and issue a dtrace_sync() to assure
		 * that all CPUs have seen the change.
		 */
		ASSERT(probe->dtpr_ecb_last != NULL);
		probe->dtpr_ecb_last->dte_next = ecb;
		probe->dtpr_ecb_last = ecb;
		probe->dtpr_predcache = 0;

		dtrace_sync();
	}
}