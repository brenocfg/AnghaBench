#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
typedef  int uint_t ;
typedef  int /*<<< orphan*/  t ;
struct trapframe {int dummy; } ;
struct rm_priotracker {int dummy; } ;
struct reg {uintptr_t pc; uintptr_t* fixreg; int lr; uintptr_t ctr; } ;
struct TYPE_17__ {scalar_t__ p_pid; } ;
typedef  TYPE_2__ proc_t ;
typedef  scalar_t__ pid_t ;
struct TYPE_18__ {scalar_t__ ftt_pid; uintptr_t ftt_pc; int ftt_type; int ftt_instr; uintptr_t ftt_dest; int /*<<< orphan*/ * ftt_retids; int /*<<< orphan*/  ftt_bi; int /*<<< orphan*/  ftt_bo; TYPE_5__* ftt_ids; TYPE_1__* ftt_proc; struct TYPE_18__* ftt_next; } ;
typedef  TYPE_3__ fasttrap_tracepoint_t ;
struct TYPE_19__ {int /*<<< orphan*/  ftp_id; int /*<<< orphan*/ * ftp_argmap; } ;
typedef  TYPE_4__ fasttrap_probe_t ;
struct TYPE_20__ {scalar_t__ fti_ptype; TYPE_4__* fti_probe; struct TYPE_20__* fti_next; } ;
typedef  TYPE_5__ fasttrap_id_t ;
struct TYPE_21__ {TYPE_3__* ftb_data; } ;
typedef  TYPE_6__ fasttrap_bucket_t ;
typedef  int /*<<< orphan*/  dtrace_icookie_t ;
struct TYPE_22__ {int t_dtrace_on; uintptr_t t_dtrace_pc; scalar_t__ t_dtrace_scrpc; uintptr_t t_dtrace_astpc; scalar_t__ t_dtrace_ret; scalar_t__ t_dtrace_npc; scalar_t__ t_dtrace_ft; scalar_t__ t_dtrace_step; } ;
struct TYPE_16__ {scalar_t__ ftpc_acount; } ;
struct TYPE_15__ {TYPE_6__* fth_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  CPU_DTRACE_ENTRY ; 
 scalar_t__ DTFTP_ENTRY ; 
 scalar_t__ DTFTP_IS_ENABLED ; 
 int /*<<< orphan*/  DTRACE_CPUFLAG_CLEAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DTRACE_CPUFLAG_SET (int /*<<< orphan*/ ) ; 
 size_t FASTTRAP_TPOINTS_INDEX (scalar_t__,uintptr_t) ; 
#define  FASTTRAP_T_B 133 
#define  FASTTRAP_T_BC 132 
#define  FASTTRAP_T_BCTR 131 
#define  FASTTRAP_T_BLR 130 
#define  FASTTRAP_T_COMMON 129 
#define  FASTTRAP_T_NOP 128 
 TYPE_2__* curproc ; 
 TYPE_7__* curthread ; 
 int /*<<< orphan*/  dtrace_interrupt_disable () ; 
 int /*<<< orphan*/  dtrace_interrupt_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtrace_probe (int /*<<< orphan*/ ,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t) ; 
 int /*<<< orphan*/  fasttrap_branch_taken (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct reg*) ; 
 int /*<<< orphan*/  fasttrap_return_common (struct reg*,uintptr_t,scalar_t__,uintptr_t) ; 
 int /*<<< orphan*/  fasttrap_sigtrap (TYPE_2__*,TYPE_7__*,uintptr_t) ; 
 int /*<<< orphan*/  fasttrap_tp_lock ; 
 TYPE_10__ fasttrap_tpoints ; 
 int /*<<< orphan*/  fasttrap_usdt_args (TYPE_4__*,struct reg*,int,uintptr_t*) ; 
 int /*<<< orphan*/  fill_regs (TYPE_7__*,struct reg*) ; 
 int /*<<< orphan*/  rm_rlock (int /*<<< orphan*/ *,struct rm_priotracker*) ; 
 int /*<<< orphan*/  rm_runlock (int /*<<< orphan*/ *,struct rm_priotracker*) ; 
 int /*<<< orphan*/  set_regs (TYPE_7__*,struct reg*) ; 

int
fasttrap_pid_probe(struct trapframe *frame)
{
	struct reg reg, *rp;
	struct rm_priotracker tracker;
	proc_t *p = curproc;
	uintptr_t pc;
	uintptr_t new_pc = 0;
	fasttrap_bucket_t *bucket;
	fasttrap_tracepoint_t *tp, tp_local;
	pid_t pid;
	dtrace_icookie_t cookie;
	uint_t is_enabled = 0;

	fill_regs(curthread, &reg);
	rp = &reg;
	pc = rp->pc;

	/*
	 * It's possible that a user (in a veritable orgy of bad planning)
	 * could redirect this thread's flow of control before it reached the
	 * return probe fasttrap. In this case we need to kill the process
	 * since it's in a unrecoverable state.
	 */
	if (curthread->t_dtrace_step) {
		ASSERT(curthread->t_dtrace_on);
		fasttrap_sigtrap(p, curthread, pc);
		return (0);
	}

	/*
	 * Clear all user tracing flags.
	 */
	curthread->t_dtrace_ft = 0;
	curthread->t_dtrace_pc = 0;
	curthread->t_dtrace_npc = 0;
	curthread->t_dtrace_scrpc = 0;
	curthread->t_dtrace_astpc = 0;

	rm_rlock(&fasttrap_tp_lock, &tracker);
	pid = p->p_pid;
	bucket = &fasttrap_tpoints.fth_table[FASTTRAP_TPOINTS_INDEX(pid, pc)];

	/*
	 * Lookup the tracepoint that the process just hit.
	 */
	for (tp = bucket->ftb_data; tp != NULL; tp = tp->ftt_next) {
		if (pid == tp->ftt_pid && pc == tp->ftt_pc &&
		    tp->ftt_proc->ftpc_acount != 0)
			break;
	}

	/*
	 * If we couldn't find a matching tracepoint, either a tracepoint has
	 * been inserted without using the pid<pid> ioctl interface (see
	 * fasttrap_ioctl), or somehow we have mislaid this tracepoint.
	 */
	if (tp == NULL) {
		rm_runlock(&fasttrap_tp_lock, &tracker);
		return (-1);
	}

	if (tp->ftt_ids != NULL) {
		fasttrap_id_t *id;

		for (id = tp->ftt_ids; id != NULL; id = id->fti_next) {
			fasttrap_probe_t *probe = id->fti_probe;

			if (id->fti_ptype == DTFTP_ENTRY) {
				/*
				 * We note that this was an entry
				 * probe to help ustack() find the
				 * first caller.
				 */
				cookie = dtrace_interrupt_disable();
				DTRACE_CPUFLAG_SET(CPU_DTRACE_ENTRY);
				dtrace_probe(probe->ftp_id, rp->fixreg[3],
						rp->fixreg[4], rp->fixreg[5], rp->fixreg[6],
						rp->fixreg[7]);
				DTRACE_CPUFLAG_CLEAR(CPU_DTRACE_ENTRY);
				dtrace_interrupt_enable(cookie);
			} else if (id->fti_ptype == DTFTP_IS_ENABLED) {
				/*
				 * Note that in this case, we don't
				 * call dtrace_probe() since it's only
				 * an artificial probe meant to change
				 * the flow of control so that it
				 * encounters the true probe.
				 */
				is_enabled = 1;
			} else if (probe->ftp_argmap == NULL) {
				dtrace_probe(probe->ftp_id, rp->fixreg[3],
				    rp->fixreg[4], rp->fixreg[5], rp->fixreg[6],
				    rp->fixreg[7]);
			} else {
				uintptr_t t[5];

				fasttrap_usdt_args(probe, rp,
				    sizeof (t) / sizeof (t[0]), t);

				dtrace_probe(probe->ftp_id, t[0], t[1],
				    t[2], t[3], t[4]);
			}
		}
	}

	/*
	 * We're about to do a bunch of work so we cache a local copy of
	 * the tracepoint to emulate the instruction, and then find the
	 * tracepoint again later if we need to light up any return probes.
	 */
	tp_local = *tp;
	rm_runlock(&fasttrap_tp_lock, &tracker);
	tp = &tp_local;

	/*
	 * If there's an is-enabled probe connected to this tracepoint it
	 * means that there was a 'xor r3, r3, r3'
	 * instruction that was placed there by DTrace when the binary was
	 * linked. As this probe is, in fact, enabled, we need to stuff 1
	 * into R3. Accordingly, we can bypass all the instruction
	 * emulation logic since we know the inevitable result. It's possible
	 * that a user could construct a scenario where the 'is-enabled'
	 * probe was on some other instruction, but that would be a rather
	 * exotic way to shoot oneself in the foot.
	 */
	if (is_enabled) {
		rp->fixreg[3] = 1;
		new_pc = rp->pc + 4;
		goto done;
	}


	switch (tp->ftt_type) {
	case FASTTRAP_T_NOP:
		new_pc = rp->pc + 4;
		break;
	case FASTTRAP_T_BC:
		if (!fasttrap_branch_taken(tp->ftt_bo, tp->ftt_bi, rp))
			break;
		/* FALLTHROUGH */
	case FASTTRAP_T_B:
		if (tp->ftt_instr & 0x01)
			rp->lr = rp->pc + 4;
		new_pc = tp->ftt_dest;
		break;
	case FASTTRAP_T_BLR:
	case FASTTRAP_T_BCTR:
		if (!fasttrap_branch_taken(tp->ftt_bo, tp->ftt_bi, rp))
			break;
		/* FALLTHROUGH */
		if (tp->ftt_type == FASTTRAP_T_BCTR)
			new_pc = rp->ctr;
		else
			new_pc = rp->lr;
		if (tp->ftt_instr & 0x01)
			rp->lr = rp->pc + 4;
		break;
	case FASTTRAP_T_COMMON:
		break;
	};
done:
	/*
	 * If there were no return probes when we first found the tracepoint,
	 * we should feel no obligation to honor any return probes that were
	 * subsequently enabled -- they'll just have to wait until the next
	 * time around.
	 */
	if (tp->ftt_retids != NULL) {
		/*
		 * We need to wait until the results of the instruction are
		 * apparent before invoking any return probes. If this
		 * instruction was emulated we can just call
		 * fasttrap_return_common(); if it needs to be executed, we
		 * need to wait until the user thread returns to the kernel.
		 */
		if (tp->ftt_type != FASTTRAP_T_COMMON) {
			fasttrap_return_common(rp, pc, pid, new_pc);
		} else {
			ASSERT(curthread->t_dtrace_ret != 0);
			ASSERT(curthread->t_dtrace_pc == pc);
			ASSERT(curthread->t_dtrace_scrpc != 0);
			ASSERT(new_pc == curthread->t_dtrace_astpc);
		}
	}

	rp->pc = new_pc;
	set_regs(curthread, rp);

	return (0);
}