#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
struct TYPE_19__ {int p_flag; } ;
typedef  TYPE_3__ proc_t ;
struct TYPE_17__ {TYPE_10__* dcr_cred; } ;
struct TYPE_20__ {TYPE_1__ dts_cred; } ;
typedef  TYPE_4__ dtrace_state_t ;
struct TYPE_23__ {int (* dtps_mode ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_21__ {int /*<<< orphan*/  dtpv_arg; TYPE_7__ dtpv_pops; } ;
typedef  TYPE_5__ dtrace_provider_t ;
struct TYPE_22__ {int /*<<< orphan*/  dtpr_arg; int /*<<< orphan*/  dtpr_id; TYPE_5__* dtpr_provider; } ;
typedef  TYPE_6__ dtrace_probe_t ;
typedef  TYPE_7__ dtrace_pops_t ;
struct TYPE_24__ {int dtms_access; } ;
typedef  TYPE_8__ dtrace_mstate_t ;
struct TYPE_25__ {int dte_cond; TYPE_6__* dte_probe; } ;
typedef  TYPE_9__ dtrace_ecb_t ;
struct TYPE_16__ {scalar_t__ cr_uid; scalar_t__ cr_ruid; scalar_t__ cr_suid; scalar_t__ cr_gid; scalar_t__ cr_rgid; scalar_t__ cr_sgid; TYPE_2__* cr_zone; } ;
typedef  TYPE_10__ cred_t ;
struct TYPE_18__ {scalar_t__ zone_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 TYPE_10__* CRED () ; 
 int DTRACE_ACCESS_ARGS ; 
 int DTRACE_ACCESS_PROC ; 
 int DTRACE_COND_OWNER ; 
 int DTRACE_COND_USERMODE ; 
 int DTRACE_COND_ZONEOWNER ; 
 int DTRACE_MODE_KERNEL ; 
 int DTRACE_MODE_NOPRIV_DROP ; 
 int DTRACE_MODE_NOPRIV_RESTRICT ; 
 int DTRACE_MODE_USER ; 
 int SNOCD ; 
 int /*<<< orphan*/  curthread ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* ttoproc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dtrace_priv_probe(dtrace_state_t *state, dtrace_mstate_t *mstate,
    dtrace_ecb_t *ecb)
{
	dtrace_probe_t *probe = ecb->dte_probe;
	dtrace_provider_t *prov = probe->dtpr_provider;
	dtrace_pops_t *pops = &prov->dtpv_pops;
	int mode = DTRACE_MODE_NOPRIV_DROP;

	ASSERT(ecb->dte_cond);

#ifdef illumos
	if (pops->dtps_mode != NULL) {
		mode = pops->dtps_mode(prov->dtpv_arg,
		    probe->dtpr_id, probe->dtpr_arg);

		ASSERT((mode & DTRACE_MODE_USER) ||
		    (mode & DTRACE_MODE_KERNEL));
		ASSERT((mode & DTRACE_MODE_NOPRIV_RESTRICT) ||
		    (mode & DTRACE_MODE_NOPRIV_DROP));
	}

	/*
	 * If the dte_cond bits indicate that this consumer is only allowed to
	 * see user-mode firings of this probe, call the provider's dtps_mode()
	 * entry point to check that the probe was fired while in a user
	 * context.  If that's not the case, use the policy specified by the
	 * provider to determine if we drop the probe or merely restrict
	 * operation.
	 */
	if (ecb->dte_cond & DTRACE_COND_USERMODE) {
		ASSERT(mode != DTRACE_MODE_NOPRIV_DROP);

		if (!(mode & DTRACE_MODE_USER)) {
			if (mode & DTRACE_MODE_NOPRIV_DROP)
				return (0);

			mstate->dtms_access &= ~DTRACE_ACCESS_ARGS;
		}
	}
#endif

	/*
	 * This is more subtle than it looks. We have to be absolutely certain
	 * that CRED() isn't going to change out from under us so it's only
	 * legit to examine that structure if we're in constrained situations.
	 * Currently, the only times we'll this check is if a non-super-user
	 * has enabled the profile or syscall providers -- providers that
	 * allow visibility of all processes. For the profile case, the check
	 * above will ensure that we're examining a user context.
	 */
	if (ecb->dte_cond & DTRACE_COND_OWNER) {
		cred_t *cr;
		cred_t *s_cr = state->dts_cred.dcr_cred;
		proc_t *proc;

		ASSERT(s_cr != NULL);

		if ((cr = CRED()) == NULL ||
		    s_cr->cr_uid != cr->cr_uid ||
		    s_cr->cr_uid != cr->cr_ruid ||
		    s_cr->cr_uid != cr->cr_suid ||
		    s_cr->cr_gid != cr->cr_gid ||
		    s_cr->cr_gid != cr->cr_rgid ||
		    s_cr->cr_gid != cr->cr_sgid ||
		    (proc = ttoproc(curthread)) == NULL ||
		    (proc->p_flag & SNOCD)) {
			if (mode & DTRACE_MODE_NOPRIV_DROP)
				return (0);

#ifdef illumos
			mstate->dtms_access &= ~DTRACE_ACCESS_PROC;
#endif
		}
	}

#ifdef illumos
	/*
	 * If our dte_cond is set to DTRACE_COND_ZONEOWNER and we are not
	 * in our zone, check to see if our mode policy is to restrict rather
	 * than to drop; if to restrict, strip away both DTRACE_ACCESS_PROC
	 * and DTRACE_ACCESS_ARGS
	 */
	if (ecb->dte_cond & DTRACE_COND_ZONEOWNER) {
		cred_t *cr;
		cred_t *s_cr = state->dts_cred.dcr_cred;

		ASSERT(s_cr != NULL);

		if ((cr = CRED()) == NULL ||
		    s_cr->cr_zone->zone_id != cr->cr_zone->zone_id) {
			if (mode & DTRACE_MODE_NOPRIV_DROP)
				return (0);

			mstate->dtms_access &=
			    ~(DTRACE_ACCESS_PROC | DTRACE_ACCESS_ARGS);
		}
	}
#endif

	return (1);
}