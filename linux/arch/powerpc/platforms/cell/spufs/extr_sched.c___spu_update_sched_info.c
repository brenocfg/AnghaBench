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
struct spu_context {int /*<<< orphan*/  last_ran; int /*<<< orphan*/  cpus_allowed; int /*<<< orphan*/  policy; int /*<<< orphan*/  prio; int /*<<< orphan*/  tid; int /*<<< orphan*/  rq; } ;
struct TYPE_2__ {int /*<<< orphan*/  cpus_ptr; int /*<<< orphan*/  policy; int /*<<< orphan*/  static_prio; int /*<<< orphan*/  prio; int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  cpumask_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_smp_processor_id () ; 
 scalar_t__ rt_prio (int /*<<< orphan*/ ) ; 

void __spu_update_sched_info(struct spu_context *ctx)
{
	/*
	 * assert that the context is not on the runqueue, so it is safe
	 * to change its scheduling parameters.
	 */
	BUG_ON(!list_empty(&ctx->rq));

	/*
	 * 32-Bit assignments are atomic on powerpc, and we don't care about
	 * memory ordering here because retrieving the controlling thread is
	 * per definition racy.
	 */
	ctx->tid = current->pid;

	/*
	 * We do our own priority calculations, so we normally want
	 * ->static_prio to start with. Unfortunately this field
	 * contains junk for threads with a realtime scheduling
	 * policy so we have to look at ->prio in this case.
	 */
	if (rt_prio(current->prio))
		ctx->prio = current->prio;
	else
		ctx->prio = current->static_prio;
	ctx->policy = current->policy;

	/*
	 * TO DO: the context may be loaded, so we may need to activate
	 * it again on a different node. But it shouldn't hurt anything
	 * to update its parameters, because we know that the scheduler
	 * is not actively looking at this field, since it is not on the
	 * runqueue. The context will be rescheduled on the proper node
	 * if it is timesliced or preempted.
	 */
	cpumask_copy(&ctx->cpus_allowed, current->cpus_ptr);

	/* Save the current cpu id for spu interrupt routing. */
	ctx->last_ran = raw_smp_processor_id();
}