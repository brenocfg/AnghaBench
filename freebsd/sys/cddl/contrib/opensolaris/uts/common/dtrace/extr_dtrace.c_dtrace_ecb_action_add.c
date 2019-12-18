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

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  void* uint16_t ;
typedef  int /*<<< orphan*/  pc_t ;
struct TYPE_17__ {int* dts_options; int dts_destructive; int dts_speculates; } ;
typedef  TYPE_2__ dtrace_state_t ;
typedef  int /*<<< orphan*/  dtrace_rechdr_t ;
struct TYPE_18__ {int dtrd_size; int dtrd_action; int dtrd_arg; void* dtrd_format; void* dtrd_alignment; int /*<<< orphan*/  dtrd_uarg; } ;
typedef  TYPE_3__ dtrace_recdesc_t ;
typedef  int dtrace_optval_t ;
struct TYPE_19__ {int dte_size; TYPE_6__* dte_action_last; TYPE_6__* dte_action; TYPE_2__* dte_state; } ;
typedef  TYPE_4__ dtrace_ecb_t ;
struct TYPE_16__ {int dtdt_size; int dtdt_flags; int /*<<< orphan*/  dtdt_kind; } ;
struct TYPE_20__ {TYPE_1__ dtdo_rtype; scalar_t__ dtdo_destructive; } ;
typedef  TYPE_5__ dtrace_difo_t ;
struct TYPE_21__ {int dta_refcnt; scalar_t__ dta_kind; struct TYPE_21__* dta_next; struct TYPE_21__* dta_prev; TYPE_5__* dta_difo; TYPE_3__ dta_rec; } ;
typedef  TYPE_6__ dtrace_action_t ;
struct TYPE_22__ {int dtad_arg; int dtad_kind; int /*<<< orphan*/  dtad_uarg; TYPE_5__* dtad_difo; } ;
typedef  TYPE_7__ dtrace_actdesc_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int DIF_TF_BYREF ; 
 int /*<<< orphan*/  DIF_TYPE_STRING ; 
#define  DTRACEACT_BREAKPOINT 153 
#define  DTRACEACT_CHILL 152 
#define  DTRACEACT_COMMIT 151 
#define  DTRACEACT_DIFEXPR 150 
#define  DTRACEACT_DISCARD 149 
#define  DTRACEACT_EXIT 148 
#define  DTRACEACT_FREOPEN 147 
 scalar_t__ DTRACEACT_ISAGG (int) ; 
 scalar_t__ DTRACEACT_ISDESTRUCTIVE (int) ; 
#define  DTRACEACT_JSTACK 146 
#define  DTRACEACT_LIBACT 145 
#define  DTRACEACT_MOD 144 
#define  DTRACEACT_PANIC 143 
#define  DTRACEACT_PRINTA 142 
#define  DTRACEACT_PRINTF 141 
#define  DTRACEACT_PRINTM 140 
#define  DTRACEACT_RAISE 139 
#define  DTRACEACT_SPECULATE 138 
#define  DTRACEACT_STACK 137 
#define  DTRACEACT_STOP 136 
#define  DTRACEACT_SYM 135 
#define  DTRACEACT_SYSTEM 134 
#define  DTRACEACT_TRACEMEM 133 
#define  DTRACEACT_TRACEMEM_DYNSIZE 132 
#define  DTRACEACT_UADDR 131 
#define  DTRACEACT_UMOD 130 
#define  DTRACEACT_USTACK 129 
#define  DTRACEACT_USYM 128 
 size_t DTRACEOPT_JSTACKFRAMES ; 
 size_t DTRACEOPT_JSTACKSTRSIZE ; 
 size_t DTRACEOPT_STACKFRAMES ; 
 size_t DTRACEOPT_STRSIZE ; 
 size_t DTRACEOPT_USTACKFRAMES ; 
 int DTRACE_USTACK_ARG (int,int) ; 
 int DTRACE_USTACK_NFRAMES (int) ; 
 int DTRACE_USTACK_STRSIZE (int) ; 
 int EINVAL ; 
 int KERNELBASE ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int P2ROUNDUP (int,int) ; 
 int /*<<< orphan*/  dtrace_difo_hold (TYPE_5__*) ; 
 TYPE_6__* dtrace_ecb_aggregation_create (TYPE_4__*,TYPE_7__*) ; 
 void* dtrace_format_add (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  dtrace_lock ; 
 TYPE_6__* kmem_zalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dtrace_ecb_action_add(dtrace_ecb_t *ecb, dtrace_actdesc_t *desc)
{
	dtrace_action_t *action, *last;
	dtrace_difo_t *dp = desc->dtad_difo;
	uint32_t size = 0, align = sizeof (uint8_t), mask;
	uint16_t format = 0;
	dtrace_recdesc_t *rec;
	dtrace_state_t *state = ecb->dte_state;
	dtrace_optval_t *opt = state->dts_options, nframes = 0, strsize;
	uint64_t arg = desc->dtad_arg;

	ASSERT(MUTEX_HELD(&dtrace_lock));
	ASSERT(ecb->dte_action == NULL || ecb->dte_action->dta_refcnt == 1);

	if (DTRACEACT_ISAGG(desc->dtad_kind)) {
		/*
		 * If this is an aggregating action, there must be neither
		 * a speculate nor a commit on the action chain.
		 */
		dtrace_action_t *act;

		for (act = ecb->dte_action; act != NULL; act = act->dta_next) {
			if (act->dta_kind == DTRACEACT_COMMIT)
				return (EINVAL);

			if (act->dta_kind == DTRACEACT_SPECULATE)
				return (EINVAL);
		}

		action = dtrace_ecb_aggregation_create(ecb, desc);

		if (action == NULL)
			return (EINVAL);
	} else {
		if (DTRACEACT_ISDESTRUCTIVE(desc->dtad_kind) ||
		    (desc->dtad_kind == DTRACEACT_DIFEXPR &&
		    dp != NULL && dp->dtdo_destructive)) {
			state->dts_destructive = 1;
		}

		switch (desc->dtad_kind) {
		case DTRACEACT_PRINTF:
		case DTRACEACT_PRINTA:
		case DTRACEACT_SYSTEM:
		case DTRACEACT_FREOPEN:
		case DTRACEACT_DIFEXPR:
			/*
			 * We know that our arg is a string -- turn it into a
			 * format.
			 */
			if (arg == 0) {
				ASSERT(desc->dtad_kind == DTRACEACT_PRINTA ||
				    desc->dtad_kind == DTRACEACT_DIFEXPR);
				format = 0;
			} else {
				ASSERT(arg != 0);
#ifdef illumos
				ASSERT(arg > KERNELBASE);
#endif
				format = dtrace_format_add(state,
				    (char *)(uintptr_t)arg);
			}

			/*FALLTHROUGH*/
		case DTRACEACT_LIBACT:
		case DTRACEACT_TRACEMEM:
		case DTRACEACT_TRACEMEM_DYNSIZE:
			if (dp == NULL)
				return (EINVAL);

			if ((size = dp->dtdo_rtype.dtdt_size) != 0)
				break;

			if (dp->dtdo_rtype.dtdt_kind == DIF_TYPE_STRING) {
				if (!(dp->dtdo_rtype.dtdt_flags & DIF_TF_BYREF))
					return (EINVAL);

				size = opt[DTRACEOPT_STRSIZE];
			}

			break;

		case DTRACEACT_STACK:
			if ((nframes = arg) == 0) {
				nframes = opt[DTRACEOPT_STACKFRAMES];
				ASSERT(nframes > 0);
				arg = nframes;
			}

			size = nframes * sizeof (pc_t);
			break;

		case DTRACEACT_JSTACK:
			if ((strsize = DTRACE_USTACK_STRSIZE(arg)) == 0)
				strsize = opt[DTRACEOPT_JSTACKSTRSIZE];

			if ((nframes = DTRACE_USTACK_NFRAMES(arg)) == 0)
				nframes = opt[DTRACEOPT_JSTACKFRAMES];

			arg = DTRACE_USTACK_ARG(nframes, strsize);

			/*FALLTHROUGH*/
		case DTRACEACT_USTACK:
			if (desc->dtad_kind != DTRACEACT_JSTACK &&
			    (nframes = DTRACE_USTACK_NFRAMES(arg)) == 0) {
				strsize = DTRACE_USTACK_STRSIZE(arg);
				nframes = opt[DTRACEOPT_USTACKFRAMES];
				ASSERT(nframes > 0);
				arg = DTRACE_USTACK_ARG(nframes, strsize);
			}

			/*
			 * Save a slot for the pid.
			 */
			size = (nframes + 1) * sizeof (uint64_t);
			size += DTRACE_USTACK_STRSIZE(arg);
			size = P2ROUNDUP(size, (uint32_t)(sizeof (uintptr_t)));

			break;

		case DTRACEACT_SYM:
		case DTRACEACT_MOD:
			if (dp == NULL || ((size = dp->dtdo_rtype.dtdt_size) !=
			    sizeof (uint64_t)) ||
			    (dp->dtdo_rtype.dtdt_flags & DIF_TF_BYREF))
				return (EINVAL);
			break;

		case DTRACEACT_USYM:
		case DTRACEACT_UMOD:
		case DTRACEACT_UADDR:
			if (dp == NULL ||
			    (dp->dtdo_rtype.dtdt_size != sizeof (uint64_t)) ||
			    (dp->dtdo_rtype.dtdt_flags & DIF_TF_BYREF))
				return (EINVAL);

			/*
			 * We have a slot for the pid, plus a slot for the
			 * argument.  To keep things simple (aligned with
			 * bitness-neutral sizing), we store each as a 64-bit
			 * quantity.
			 */
			size = 2 * sizeof (uint64_t);
			break;

		case DTRACEACT_STOP:
		case DTRACEACT_BREAKPOINT:
		case DTRACEACT_PANIC:
			break;

		case DTRACEACT_CHILL:
		case DTRACEACT_DISCARD:
		case DTRACEACT_RAISE:
			if (dp == NULL)
				return (EINVAL);
			break;

		case DTRACEACT_EXIT:
			if (dp == NULL ||
			    (size = dp->dtdo_rtype.dtdt_size) != sizeof (int) ||
			    (dp->dtdo_rtype.dtdt_flags & DIF_TF_BYREF))
				return (EINVAL);
			break;

		case DTRACEACT_SPECULATE:
			if (ecb->dte_size > sizeof (dtrace_rechdr_t))
				return (EINVAL);

			if (dp == NULL)
				return (EINVAL);

			state->dts_speculates = 1;
			break;

		case DTRACEACT_PRINTM:
		    	size = dp->dtdo_rtype.dtdt_size;
			break;

		case DTRACEACT_COMMIT: {
			dtrace_action_t *act = ecb->dte_action;

			for (; act != NULL; act = act->dta_next) {
				if (act->dta_kind == DTRACEACT_COMMIT)
					return (EINVAL);
			}

			if (dp == NULL)
				return (EINVAL);
			break;
		}

		default:
			return (EINVAL);
		}

		if (size != 0 || desc->dtad_kind == DTRACEACT_SPECULATE) {
			/*
			 * If this is a data-storing action or a speculate,
			 * we must be sure that there isn't a commit on the
			 * action chain.
			 */
			dtrace_action_t *act = ecb->dte_action;

			for (; act != NULL; act = act->dta_next) {
				if (act->dta_kind == DTRACEACT_COMMIT)
					return (EINVAL);
			}
		}

		action = kmem_zalloc(sizeof (dtrace_action_t), KM_SLEEP);
		action->dta_rec.dtrd_size = size;
	}

	action->dta_refcnt = 1;
	rec = &action->dta_rec;
	size = rec->dtrd_size;

	for (mask = sizeof (uint64_t) - 1; size != 0 && mask > 0; mask >>= 1) {
		if (!(size & mask)) {
			align = mask + 1;
			break;
		}
	}

	action->dta_kind = desc->dtad_kind;

	if ((action->dta_difo = dp) != NULL)
		dtrace_difo_hold(dp);

	rec->dtrd_action = action->dta_kind;
	rec->dtrd_arg = arg;
	rec->dtrd_uarg = desc->dtad_uarg;
	rec->dtrd_alignment = (uint16_t)align;
	rec->dtrd_format = format;

	if ((last = ecb->dte_action_last) != NULL) {
		ASSERT(ecb->dte_action != NULL);
		action->dta_prev = last;
		last->dta_next = action;
	} else {
		ASSERT(ecb->dte_action == NULL);
		ecb->dte_action = action;
	}

	ecb->dte_action_last = action;

	return (0);
}