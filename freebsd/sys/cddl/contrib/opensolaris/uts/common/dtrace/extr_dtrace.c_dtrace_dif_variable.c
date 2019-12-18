#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_49__   TYPE_9__ ;
typedef  struct TYPE_48__   TYPE_8__ ;
typedef  struct TYPE_47__   TYPE_7__ ;
typedef  struct TYPE_46__   TYPE_6__ ;
typedef  struct TYPE_45__   TYPE_5__ ;
typedef  struct TYPE_44__   TYPE_4__ ;
typedef  struct TYPE_43__   TYPE_3__ ;
typedef  struct TYPE_42__   TYPE_2__ ;
typedef  struct TYPE_41__   TYPE_26__ ;
typedef  struct TYPE_40__   TYPE_25__ ;
typedef  struct TYPE_39__   TYPE_24__ ;
typedef  struct TYPE_38__   TYPE_23__ ;
typedef  struct TYPE_37__   TYPE_1__ ;
typedef  struct TYPE_36__   TYPE_19__ ;
typedef  struct TYPE_35__   TYPE_18__ ;
typedef  struct TYPE_34__   TYPE_17__ ;
typedef  struct TYPE_33__   TYPE_16__ ;
typedef  struct TYPE_32__   TYPE_15__ ;
typedef  struct TYPE_31__   TYPE_14__ ;
typedef  struct TYPE_30__   TYPE_13__ ;
typedef  struct TYPE_29__   TYPE_12__ ;
typedef  struct TYPE_28__   TYPE_11__ ;
typedef  struct TYPE_27__   TYPE_10__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct trapframe {int dummy; } ;
struct pargs {int /*<<< orphan*/  ar_length; int /*<<< orphan*/  ar_args; } ;
typedef  void* pc_t ;
struct TYPE_31__ {int /*<<< orphan*/  lwp_errno; struct trapframe* lwp_regs; } ;
typedef  TYPE_14__ klwp_t ;
typedef  int /*<<< orphan*/  dtrace_state_t ;
struct TYPE_30__ {int (* dtps_getargval ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ;} ;
struct TYPE_32__ {int /*<<< orphan*/  dtpv_name; int /*<<< orphan*/  dtpv_arg; TYPE_13__ dtpv_pops; } ;
typedef  TYPE_15__ dtrace_provider_t ;
struct TYPE_33__ {int dtms_present; int* dtms_arg; int dtms_timestamp; int dtms_walltimestamp; int dtms_ipl; int dtms_epid; int dtms_stackdepth; int dtms_ustackdepth; int dtms_caller; int dtms_ucaller; TYPE_26__* dtms_probe; } ;
typedef  TYPE_16__ dtrace_mstate_t ;
struct TYPE_49__ {int /*<<< orphan*/  cr_gid; int /*<<< orphan*/  cr_uid; } ;
struct TYPE_48__ {int /*<<< orphan*/  pr_id; int /*<<< orphan*/  pr_name; } ;
struct TYPE_47__ {int /*<<< orphan*/  zone_name; } ;
struct TYPE_46__ {int /*<<< orphan*/  zone_name; } ;
struct TYPE_45__ {int /*<<< orphan*/  p_comm; struct pargs* p_args; } ;
struct TYPE_44__ {int /*<<< orphan*/  u_comm; } ;
struct TYPE_43__ {int /*<<< orphan*/  u_comm; } ;
struct TYPE_42__ {int p_pid; } ;
struct TYPE_41__ {int dtpr_id; int /*<<< orphan*/  dtpr_name; int /*<<< orphan*/  dtpr_func; int /*<<< orphan*/  dtpr_mod; TYPE_15__* dtpr_provider; int /*<<< orphan*/  dtpr_aframes; int /*<<< orphan*/  dtpr_arg; } ;
struct TYPE_40__ {int /*<<< orphan*/ * cpuc_dtrace_illval; } ;
struct TYPE_39__ {int p_pid; TYPE_2__* p_pptr; } ;
struct TYPE_38__ {int t_dtrace_vtime; int td_errno; TYPE_14__* t_lwp; TYPE_12__* td_ucred; TYPE_11__* t_procp; TYPE_5__* td_proc; int /*<<< orphan*/  t_tid; struct trapframe* td_frame; } ;
struct TYPE_37__ {int /*<<< orphan*/  pid_id; } ;
struct TYPE_36__ {TYPE_9__* p_cred; TYPE_6__* p_zone; TYPE_3__ p_user; } ;
struct TYPE_35__ {int pid_id; } ;
struct TYPE_34__ {int p_pid; } ;
struct TYPE_29__ {int /*<<< orphan*/  cr_gid; int /*<<< orphan*/  cr_uid; TYPE_8__* cr_prison; } ;
struct TYPE_28__ {TYPE_10__* p_cred; TYPE_7__* p_zone; TYPE_4__ p_user; int /*<<< orphan*/  p_ppid; TYPE_1__* p_pidp; } ;
struct TYPE_27__ {int /*<<< orphan*/  cr_gid; int /*<<< orphan*/  cr_uid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  CPU ; 
 int /*<<< orphan*/  CPU_DTRACE_BADADDR ; 
 int /*<<< orphan*/  CPU_DTRACE_ILLOP ; 
 int /*<<< orphan*/  CPU_DTRACE_NOFAULT ; 
 int /*<<< orphan*/  CPU_ON_INTR (int /*<<< orphan*/ ) ; 
 int DIF_VAR_ARG0 ; 
 int DIF_VAR_ARG9 ; 
#define  DIF_VAR_ARGS 156 
#define  DIF_VAR_CALLER 155 
#define  DIF_VAR_CPU 154 
#define  DIF_VAR_CURTHREAD 153 
#define  DIF_VAR_EPID 152 
#define  DIF_VAR_ERRNO 151 
#define  DIF_VAR_EXECARGS 150 
#define  DIF_VAR_EXECNAME 149 
#define  DIF_VAR_GID 148 
#define  DIF_VAR_ID 147 
#define  DIF_VAR_IPL 146 
#define  DIF_VAR_JAILNAME 145 
#define  DIF_VAR_JID 144 
#define  DIF_VAR_PID 143 
#define  DIF_VAR_PPID 142 
#define  DIF_VAR_PROBEFUNC 141 
#define  DIF_VAR_PROBEMOD 140 
#define  DIF_VAR_PROBENAME 139 
#define  DIF_VAR_PROBEPROV 138 
#define  DIF_VAR_STACKDEPTH 137 
#define  DIF_VAR_TID 136 
#define  DIF_VAR_TIMESTAMP 135 
#define  DIF_VAR_UCALLER 134 
#define  DIF_VAR_UID 133 
#define  DIF_VAR_UREGS 132 
#define  DIF_VAR_USTACKDEPTH 131 
#define  DIF_VAR_VTIMESTAMP 130 
#define  DIF_VAR_WALLTIMESTAMP 129 
#define  DIF_VAR_ZONENAME 128 
 int /*<<< orphan*/  DTRACE_ANCHORED (TYPE_26__*) ; 
 int /*<<< orphan*/  DTRACE_CPUFLAG_CLEAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DTRACE_CPUFLAG_SET (int /*<<< orphan*/ ) ; 
 int DTRACE_MSTATE_ARGS ; 
 int DTRACE_MSTATE_CALLER ; 
 int DTRACE_MSTATE_EPID ; 
 int DTRACE_MSTATE_IPL ; 
 int DTRACE_MSTATE_PROBE ; 
 int DTRACE_MSTATE_STACKDEPTH ; 
 int DTRACE_MSTATE_TIMESTAMP ; 
 int DTRACE_MSTATE_UCALLER ; 
 int DTRACE_MSTATE_USTACKDEPTH ; 
 int DTRACE_MSTATE_WALLTIMESTAMP ; 
 TYPE_25__* cpu_core ; 
 size_t curcpu ; 
 TYPE_24__* curproc ; 
 TYPE_23__* curthread ; 
 int dtrace_caller (int) ; 
 int dtrace_dif_varstr (uintptr_t,int /*<<< orphan*/ *,TYPE_16__*) ; 
 int dtrace_dif_varstrz (uintptr_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_16__*) ; 
 int dtrace_getarg (int,int) ; 
 int dtrace_gethrestime () ; 
 int dtrace_gethrtime () ; 
 int dtrace_getipl () ; 
 int /*<<< orphan*/  dtrace_getpcstack (void**,int,int,int /*<<< orphan*/ *) ; 
 int dtrace_getreg (struct trapframe*,int) ; 
 int dtrace_getstackdepth (int) ; 
 int /*<<< orphan*/  dtrace_getupcstack (int*,int) ; 
 int dtrace_getustackdepth () ; 
 int /*<<< orphan*/  dtrace_priv_kernel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dtrace_priv_proc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dtrace_vtime_references ; 
 TYPE_19__ p0 ; 
 TYPE_18__ pid0 ; 
 TYPE_17__ proc0 ; 
 int stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static uint64_t
dtrace_dif_variable(dtrace_mstate_t *mstate, dtrace_state_t *state, uint64_t v,
    uint64_t ndx)
{
	/*
	 * If we're accessing one of the uncached arguments, we'll turn this
	 * into a reference in the args array.
	 */
	if (v >= DIF_VAR_ARG0 && v <= DIF_VAR_ARG9) {
		ndx = v - DIF_VAR_ARG0;
		v = DIF_VAR_ARGS;
	}

	switch (v) {
	case DIF_VAR_ARGS:
		ASSERT(mstate->dtms_present & DTRACE_MSTATE_ARGS);
		if (ndx >= sizeof (mstate->dtms_arg) /
		    sizeof (mstate->dtms_arg[0])) {
			int aframes = mstate->dtms_probe->dtpr_aframes + 2;
			dtrace_provider_t *pv;
			uint64_t val;

			pv = mstate->dtms_probe->dtpr_provider;
			if (pv->dtpv_pops.dtps_getargval != NULL)
				val = pv->dtpv_pops.dtps_getargval(pv->dtpv_arg,
				    mstate->dtms_probe->dtpr_id,
				    mstate->dtms_probe->dtpr_arg, ndx, aframes);
			else
				val = dtrace_getarg(ndx, aframes);

			/*
			 * This is regrettably required to keep the compiler
			 * from tail-optimizing the call to dtrace_getarg().
			 * The condition always evaluates to true, but the
			 * compiler has no way of figuring that out a priori.
			 * (None of this would be necessary if the compiler
			 * could be relied upon to _always_ tail-optimize
			 * the call to dtrace_getarg() -- but it can't.)
			 */
			if (mstate->dtms_probe != NULL)
				return (val);

			ASSERT(0);
		}

		return (mstate->dtms_arg[ndx]);

#ifdef illumos
	case DIF_VAR_UREGS: {
		klwp_t *lwp;

		if (!dtrace_priv_proc(state))
			return (0);

		if ((lwp = curthread->t_lwp) == NULL) {
			DTRACE_CPUFLAG_SET(CPU_DTRACE_BADADDR);
			cpu_core[curcpu].cpuc_dtrace_illval = NULL;
			return (0);
		}

		return (dtrace_getreg(lwp->lwp_regs, ndx));
		return (0);
	}
#else
	case DIF_VAR_UREGS: {
		struct trapframe *tframe;

		if (!dtrace_priv_proc(state))
			return (0);

		if ((tframe = curthread->td_frame) == NULL) {
			DTRACE_CPUFLAG_SET(CPU_DTRACE_BADADDR);
			cpu_core[curcpu].cpuc_dtrace_illval = 0;
			return (0);
		}

		return (dtrace_getreg(tframe, ndx));
	}
#endif

	case DIF_VAR_CURTHREAD:
		if (!dtrace_priv_proc(state))
			return (0);
		return ((uint64_t)(uintptr_t)curthread);

	case DIF_VAR_TIMESTAMP:
		if (!(mstate->dtms_present & DTRACE_MSTATE_TIMESTAMP)) {
			mstate->dtms_timestamp = dtrace_gethrtime();
			mstate->dtms_present |= DTRACE_MSTATE_TIMESTAMP;
		}
		return (mstate->dtms_timestamp);

	case DIF_VAR_VTIMESTAMP:
		ASSERT(dtrace_vtime_references != 0);
		return (curthread->t_dtrace_vtime);

	case DIF_VAR_WALLTIMESTAMP:
		if (!(mstate->dtms_present & DTRACE_MSTATE_WALLTIMESTAMP)) {
			mstate->dtms_walltimestamp = dtrace_gethrestime();
			mstate->dtms_present |= DTRACE_MSTATE_WALLTIMESTAMP;
		}
		return (mstate->dtms_walltimestamp);

#ifdef illumos
	case DIF_VAR_IPL:
		if (!dtrace_priv_kernel(state))
			return (0);
		if (!(mstate->dtms_present & DTRACE_MSTATE_IPL)) {
			mstate->dtms_ipl = dtrace_getipl();
			mstate->dtms_present |= DTRACE_MSTATE_IPL;
		}
		return (mstate->dtms_ipl);
#endif

	case DIF_VAR_EPID:
		ASSERT(mstate->dtms_present & DTRACE_MSTATE_EPID);
		return (mstate->dtms_epid);

	case DIF_VAR_ID:
		ASSERT(mstate->dtms_present & DTRACE_MSTATE_PROBE);
		return (mstate->dtms_probe->dtpr_id);

	case DIF_VAR_STACKDEPTH:
		if (!dtrace_priv_kernel(state))
			return (0);
		if (!(mstate->dtms_present & DTRACE_MSTATE_STACKDEPTH)) {
			int aframes = mstate->dtms_probe->dtpr_aframes + 2;

			mstate->dtms_stackdepth = dtrace_getstackdepth(aframes);
			mstate->dtms_present |= DTRACE_MSTATE_STACKDEPTH;
		}
		return (mstate->dtms_stackdepth);

	case DIF_VAR_USTACKDEPTH:
		if (!dtrace_priv_proc(state))
			return (0);
		if (!(mstate->dtms_present & DTRACE_MSTATE_USTACKDEPTH)) {
			/*
			 * See comment in DIF_VAR_PID.
			 */
			if (DTRACE_ANCHORED(mstate->dtms_probe) &&
			    CPU_ON_INTR(CPU)) {
				mstate->dtms_ustackdepth = 0;
			} else {
				DTRACE_CPUFLAG_SET(CPU_DTRACE_NOFAULT);
				mstate->dtms_ustackdepth =
				    dtrace_getustackdepth();
				DTRACE_CPUFLAG_CLEAR(CPU_DTRACE_NOFAULT);
			}
			mstate->dtms_present |= DTRACE_MSTATE_USTACKDEPTH;
		}
		return (mstate->dtms_ustackdepth);

	case DIF_VAR_CALLER:
		if (!dtrace_priv_kernel(state))
			return (0);
		if (!(mstate->dtms_present & DTRACE_MSTATE_CALLER)) {
			int aframes = mstate->dtms_probe->dtpr_aframes + 2;

			if (!DTRACE_ANCHORED(mstate->dtms_probe)) {
				/*
				 * If this is an unanchored probe, we are
				 * required to go through the slow path:
				 * dtrace_caller() only guarantees correct
				 * results for anchored probes.
				 */
				pc_t caller[2] = {0, 0};

				dtrace_getpcstack(caller, 2, aframes,
				    (uint32_t *)(uintptr_t)mstate->dtms_arg[0]);
				mstate->dtms_caller = caller[1];
			} else if ((mstate->dtms_caller =
			    dtrace_caller(aframes)) == -1) {
				/*
				 * We have failed to do this the quick way;
				 * we must resort to the slower approach of
				 * calling dtrace_getpcstack().
				 */
				pc_t caller = 0;

				dtrace_getpcstack(&caller, 1, aframes, NULL);
				mstate->dtms_caller = caller;
			}

			mstate->dtms_present |= DTRACE_MSTATE_CALLER;
		}
		return (mstate->dtms_caller);

	case DIF_VAR_UCALLER:
		if (!dtrace_priv_proc(state))
			return (0);

		if (!(mstate->dtms_present & DTRACE_MSTATE_UCALLER)) {
			uint64_t ustack[3];

			/*
			 * dtrace_getupcstack() fills in the first uint64_t
			 * with the current PID.  The second uint64_t will
			 * be the program counter at user-level.  The third
			 * uint64_t will contain the caller, which is what
			 * we're after.
			 */
			ustack[2] = 0;
			DTRACE_CPUFLAG_SET(CPU_DTRACE_NOFAULT);
			dtrace_getupcstack(ustack, 3);
			DTRACE_CPUFLAG_CLEAR(CPU_DTRACE_NOFAULT);
			mstate->dtms_ucaller = ustack[2];
			mstate->dtms_present |= DTRACE_MSTATE_UCALLER;
		}

		return (mstate->dtms_ucaller);

	case DIF_VAR_PROBEPROV:
		ASSERT(mstate->dtms_present & DTRACE_MSTATE_PROBE);
		return (dtrace_dif_varstr(
		    (uintptr_t)mstate->dtms_probe->dtpr_provider->dtpv_name,
		    state, mstate));

	case DIF_VAR_PROBEMOD:
		ASSERT(mstate->dtms_present & DTRACE_MSTATE_PROBE);
		return (dtrace_dif_varstr(
		    (uintptr_t)mstate->dtms_probe->dtpr_mod,
		    state, mstate));

	case DIF_VAR_PROBEFUNC:
		ASSERT(mstate->dtms_present & DTRACE_MSTATE_PROBE);
		return (dtrace_dif_varstr(
		    (uintptr_t)mstate->dtms_probe->dtpr_func,
		    state, mstate));

	case DIF_VAR_PROBENAME:
		ASSERT(mstate->dtms_present & DTRACE_MSTATE_PROBE);
		return (dtrace_dif_varstr(
		    (uintptr_t)mstate->dtms_probe->dtpr_name,
		    state, mstate));

	case DIF_VAR_PID:
		if (!dtrace_priv_proc(state))
			return (0);

#ifdef illumos
		/*
		 * Note that we are assuming that an unanchored probe is
		 * always due to a high-level interrupt.  (And we're assuming
		 * that there is only a single high level interrupt.)
		 */
		if (DTRACE_ANCHORED(mstate->dtms_probe) && CPU_ON_INTR(CPU))
			return (pid0.pid_id);

		/*
		 * It is always safe to dereference one's own t_procp pointer:
		 * it always points to a valid, allocated proc structure.
		 * Further, it is always safe to dereference the p_pidp member
		 * of one's own proc structure.  (These are truisms becuase
		 * threads and processes don't clean up their own state --
		 * they leave that task to whomever reaps them.)
		 */
		return ((uint64_t)curthread->t_procp->p_pidp->pid_id);
#else
		return ((uint64_t)curproc->p_pid);
#endif

	case DIF_VAR_PPID:
		if (!dtrace_priv_proc(state))
			return (0);

#ifdef illumos
		/*
		 * See comment in DIF_VAR_PID.
		 */
		if (DTRACE_ANCHORED(mstate->dtms_probe) && CPU_ON_INTR(CPU))
			return (pid0.pid_id);

		/*
		 * It is always safe to dereference one's own t_procp pointer:
		 * it always points to a valid, allocated proc structure.
		 * (This is true because threads don't clean up their own
		 * state -- they leave that task to whomever reaps them.)
		 */
		return ((uint64_t)curthread->t_procp->p_ppid);
#else
		if (curproc->p_pid == proc0.p_pid)
			return (curproc->p_pid);
		else
			return (curproc->p_pptr->p_pid);
#endif

	case DIF_VAR_TID:
#ifdef illumos
		/*
		 * See comment in DIF_VAR_PID.
		 */
		if (DTRACE_ANCHORED(mstate->dtms_probe) && CPU_ON_INTR(CPU))
			return (0);
#endif

		return ((uint64_t)curthread->t_tid);

	case DIF_VAR_EXECARGS: {
		struct pargs *p_args = curthread->td_proc->p_args;

		if (p_args == NULL)
			return(0);

		return (dtrace_dif_varstrz(
		    (uintptr_t) p_args->ar_args, p_args->ar_length, state, mstate));
	}

	case DIF_VAR_EXECNAME:
#ifdef illumos
		if (!dtrace_priv_proc(state))
			return (0);

		/*
		 * See comment in DIF_VAR_PID.
		 */
		if (DTRACE_ANCHORED(mstate->dtms_probe) && CPU_ON_INTR(CPU))
			return ((uint64_t)(uintptr_t)p0.p_user.u_comm);

		/*
		 * It is always safe to dereference one's own t_procp pointer:
		 * it always points to a valid, allocated proc structure.
		 * (This is true because threads don't clean up their own
		 * state -- they leave that task to whomever reaps them.)
		 */
		return (dtrace_dif_varstr(
		    (uintptr_t)curthread->t_procp->p_user.u_comm,
		    state, mstate));
#else
		return (dtrace_dif_varstr(
		    (uintptr_t) curthread->td_proc->p_comm, state, mstate));
#endif

	case DIF_VAR_ZONENAME:
#ifdef illumos
		if (!dtrace_priv_proc(state))
			return (0);

		/*
		 * See comment in DIF_VAR_PID.
		 */
		if (DTRACE_ANCHORED(mstate->dtms_probe) && CPU_ON_INTR(CPU))
			return ((uint64_t)(uintptr_t)p0.p_zone->zone_name);

		/*
		 * It is always safe to dereference one's own t_procp pointer:
		 * it always points to a valid, allocated proc structure.
		 * (This is true because threads don't clean up their own
		 * state -- they leave that task to whomever reaps them.)
		 */
		return (dtrace_dif_varstr(
		    (uintptr_t)curthread->t_procp->p_zone->zone_name,
		    state, mstate));
#elif defined(__FreeBSD__)
	/*
	 * On FreeBSD, we introduce compatibility to zonename by falling through
	 * into jailname.
	 */
	case DIF_VAR_JAILNAME:
		if (!dtrace_priv_kernel(state))
			return (0);

		return (dtrace_dif_varstr(
		    (uintptr_t)curthread->td_ucred->cr_prison->pr_name,
		    state, mstate));

	case DIF_VAR_JID:
		if (!dtrace_priv_kernel(state))
			return (0);

		return ((uint64_t)curthread->td_ucred->cr_prison->pr_id);
#else
		return (0);
#endif

	case DIF_VAR_UID:
		if (!dtrace_priv_proc(state))
			return (0);

#ifdef illumos
		/*
		 * See comment in DIF_VAR_PID.
		 */
		if (DTRACE_ANCHORED(mstate->dtms_probe) && CPU_ON_INTR(CPU))
			return ((uint64_t)p0.p_cred->cr_uid);

		/*
		 * It is always safe to dereference one's own t_procp pointer:
		 * it always points to a valid, allocated proc structure.
		 * (This is true because threads don't clean up their own
		 * state -- they leave that task to whomever reaps them.)
		 *
		 * Additionally, it is safe to dereference one's own process
		 * credential, since this is never NULL after process birth.
		 */
		return ((uint64_t)curthread->t_procp->p_cred->cr_uid);
#else
		return ((uint64_t)curthread->td_ucred->cr_uid);
#endif

	case DIF_VAR_GID:
		if (!dtrace_priv_proc(state))
			return (0);

#ifdef illumos
		/*
		 * See comment in DIF_VAR_PID.
		 */
		if (DTRACE_ANCHORED(mstate->dtms_probe) && CPU_ON_INTR(CPU))
			return ((uint64_t)p0.p_cred->cr_gid);

		/*
		 * It is always safe to dereference one's own t_procp pointer:
		 * it always points to a valid, allocated proc structure.
		 * (This is true because threads don't clean up their own
		 * state -- they leave that task to whomever reaps them.)
		 *
		 * Additionally, it is safe to dereference one's own process
		 * credential, since this is never NULL after process birth.
		 */
		return ((uint64_t)curthread->t_procp->p_cred->cr_gid);
#else
		return ((uint64_t)curthread->td_ucred->cr_gid);
#endif

	case DIF_VAR_ERRNO: {
#ifdef illumos
		klwp_t *lwp;
		if (!dtrace_priv_proc(state))
			return (0);

		/*
		 * See comment in DIF_VAR_PID.
		 */
		if (DTRACE_ANCHORED(mstate->dtms_probe) && CPU_ON_INTR(CPU))
			return (0);

		/*
		 * It is always safe to dereference one's own t_lwp pointer in
		 * the event that this pointer is non-NULL.  (This is true
		 * because threads and lwps don't clean up their own state --
		 * they leave that task to whomever reaps them.)
		 */
		if ((lwp = curthread->t_lwp) == NULL)
			return (0);

		return ((uint64_t)lwp->lwp_errno);
#else
		return (curthread->td_errno);
#endif
	}
#ifndef illumos
	case DIF_VAR_CPU: {
		return curcpu;
	}
#endif
	default:
		DTRACE_CPUFLAG_SET(CPU_DTRACE_ILLOP);
		return (0);
	}
}