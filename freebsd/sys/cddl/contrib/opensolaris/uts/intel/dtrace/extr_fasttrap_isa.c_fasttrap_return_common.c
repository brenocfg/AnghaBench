#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct rm_priotracker {int dummy; } ;
struct reg {int /*<<< orphan*/  r_rbx; int /*<<< orphan*/  r_rax; } ;
typedef  scalar_t__ pid_t ;
struct TYPE_9__ {scalar_t__ ftt_pid; uintptr_t ftt_pc; scalar_t__ ftt_type; TYPE_4__* ftt_retids; TYPE_1__* ftt_proc; struct TYPE_9__* ftt_next; } ;
typedef  TYPE_3__ fasttrap_tracepoint_t ;
struct TYPE_10__ {TYPE_2__* fti_probe; struct TYPE_10__* fti_next; } ;
typedef  TYPE_4__ fasttrap_id_t ;
struct TYPE_11__ {TYPE_3__* ftb_data; } ;
typedef  TYPE_5__ fasttrap_bucket_t ;
struct TYPE_12__ {TYPE_5__* fth_table; } ;
struct TYPE_8__ {uintptr_t ftp_faddr; uintptr_t ftp_fsize; int /*<<< orphan*/  ftp_id; } ;
struct TYPE_7__ {scalar_t__ ftpc_acount; } ;

/* Variables and functions */
 size_t FASTTRAP_TPOINTS_INDEX (scalar_t__,uintptr_t) ; 
 scalar_t__ FASTTRAP_T_RET ; 
 scalar_t__ FASTTRAP_T_RET16 ; 
 int /*<<< orphan*/  dtrace_probe (int /*<<< orphan*/ ,uintptr_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fasttrap_tp_lock ; 
 TYPE_6__ fasttrap_tpoints ; 
 int /*<<< orphan*/  rm_rlock (int /*<<< orphan*/ *,struct rm_priotracker*) ; 
 int /*<<< orphan*/  rm_runlock (int /*<<< orphan*/ *,struct rm_priotracker*) ; 

__attribute__((used)) static void
fasttrap_return_common(struct reg *rp, uintptr_t pc, pid_t pid,
    uintptr_t new_pc)
{
	fasttrap_tracepoint_t *tp;
	fasttrap_bucket_t *bucket;
	fasttrap_id_t *id;
	struct rm_priotracker tracker;

	rm_rlock(&fasttrap_tp_lock, &tracker);
	bucket = &fasttrap_tpoints.fth_table[FASTTRAP_TPOINTS_INDEX(pid, pc)];

	for (tp = bucket->ftb_data; tp != NULL; tp = tp->ftt_next) {
		if (pid == tp->ftt_pid && pc == tp->ftt_pc &&
		    tp->ftt_proc->ftpc_acount != 0)
			break;
	}

	/*
	 * Don't sweat it if we can't find the tracepoint again; unlike
	 * when we're in fasttrap_pid_probe(), finding the tracepoint here
	 * is not essential to the correct execution of the process.
	 */
	if (tp == NULL) {
		rm_runlock(&fasttrap_tp_lock, &tracker);
		return;
	}

	for (id = tp->ftt_retids; id != NULL; id = id->fti_next) {
		/*
		 * If there's a branch that could act as a return site, we
		 * need to trace it, and check here if the program counter is
		 * external to the function.
		 */
		if (tp->ftt_type != FASTTRAP_T_RET &&
		    tp->ftt_type != FASTTRAP_T_RET16 &&
		    new_pc - id->fti_probe->ftp_faddr <
		    id->fti_probe->ftp_fsize)
			continue;

		dtrace_probe(id->fti_probe->ftp_id,
		    pc - id->fti_probe->ftp_faddr,
		    rp->r_rax, rp->r_rbx, 0, 0);
	}

	rm_runlock(&fasttrap_tp_lock, &tracker);
}